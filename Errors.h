#pragma once

#include <string>
#include <GL/glew.h>

extern void fatalError(std::string errorMessage);
extern void errorCallback(GLenum source, GLenum type, GLuint id,
                          GLenum severity, GLsizei length, const GLchar* message, const void* userParam);