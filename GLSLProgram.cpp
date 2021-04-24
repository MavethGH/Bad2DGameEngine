#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() :
    _shaderProgramID(0),
    _vertShaderID(0),
    _fragShaderID(0)
{

}

GLSLProgram::~GLSLProgram()
{

}

void GLSLProgram::compileShaders(const std::string& vertPath, const std::string& fragPath)
{
    _vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (!_vertShaderID)
    {
        fatalError("Could not create vertex shader.");
    }

    _fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (!_fragShaderID)
    {
        fatalError("Could not create fragment shader.");
    }

    compileShader(_vertShaderID, vertPath);
    compileShader(_fragShaderID, fragPath);
}

std::string GLSLProgram::readShaderFile(const std::string& filePath)
{
    std::ifstream fileStream(filePath);
    if (fileStream.fail())
    {
        perror(filePath.c_str());
        fatalError("Failed to open" + filePath + ".");
    }

    std::string fileContents = "";
    std::string line;

    while (std::getline(fileStream, line))
    {
        fileContents += line + "\n";
    }

    fileStream.close();

    return fileContents;
}

void GLSLProgram::compileShader(GLuint shaderID, const std::string& filePath)
{
    // Read contents of shader file
    std::string shaderData = readShaderFile(filePath);

    // OpenGL needs the file contents in this format
    const char * shaderDataPtr = shaderData.c_str();
    glShaderSource(shaderID, 1, &shaderDataPtr, nullptr);

    // Moment of truth
    glCompileShader(shaderID);

    // Error checking
    GLint isCompiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        // Get size of error log
        GLint maxLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLogLength);

        // Read error log
        std::vector<GLchar> compileErrorLog(maxLogLength);
        glGetShaderInfoLog(shaderID, maxLogLength, &maxLogLength, &compileErrorLog[0]);

        // Avoid leaking the shader
        glDeleteShader(shaderID);

        // Fail
        perror(&compileErrorLog[0]);
        fatalError("Could not compile shader " + filePath + ".");
    }
}

void GLSLProgram::linkShaders()
{
    // Program object represents fully executable code
    _shaderProgramID = glCreateProgram();

    // Attach shaders
    glAttachShader(_shaderProgramID, _vertShaderID);
    glAttachShader(_shaderProgramID, _fragShaderID);

    // Moment of truth
    glLinkProgram(_shaderProgramID);

    // Error handling
    GLint isLinked = 0;
    glGetProgramiv(_shaderProgramID, GL_LINK_STATUS, &isLinked);
    if (!isLinked)
    {
        // Get size of error log
        GLint maxLogLength;
        glGetProgramiv(_shaderProgramID, GL_INFO_LOG_LENGTH, &maxLogLength);

        // Read error log
        std::vector<GLchar> linkErrorLog(maxLogLength);
        glGetProgramInfoLog(_shaderProgramID, maxLogLength, &maxLogLength, &linkErrorLog[0]);

        // Avoid leaking the program and shaders
        glDeleteProgram(_shaderProgramID);
        glDeleteShader(_vertShaderID);
        glDeleteShader(_fragShaderID);

        // Fail
        perror(&linkErrorLog[0]);
        fatalError("Could not link shaders.");
    }

    // Clean up leaks after successful link
    glDetachShader(_shaderProgramID, _vertShaderID);
    glDetachShader(_shaderProgramID, _fragShaderID);
    glDeleteShader(_vertShaderID);
    glDeleteShader(_fragShaderID);
}

void GLSLProgram::use()
{
    glUseProgram(_shaderProgramID);
}

void GLSLProgram::unuse()
{
    glUseProgram(0);
}

GLuint GLSLProgram::getUniformLocation(const std::string& uniformName)
{
    GLuint location = glGetUniformLocation(_shaderProgramID, uniformName.c_str());
    if (location == GL_INVALID_INDEX)
    {
        return 0;
    }
    return location;
}