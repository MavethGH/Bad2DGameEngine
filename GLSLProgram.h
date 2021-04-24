#pragma once

#include <string>
#include <gl/glew.h>

class GLSLProgram
{
    public:
        GLSLProgram();
        ~GLSLProgram();
        void compileShaders(const std::string& vertPath, const std::string& fragPath);
        void linkShaders();
        void use();
        void unuse();
        GLuint getUniformLocation(const std::string& uniformName);
    private:
        void compileShader(GLuint shaderID, const std::string& filePath);
        std::string readShaderFile(const std::string& filePath);
        GLuint _shaderProgramID;
        GLuint _vertShaderID;
        GLuint _fragShaderID;
};