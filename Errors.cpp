#include "Errors.h"

#include <iostream>
#include <SDL.h>

void fatalError(std::string errorMessage)
{
    std::cout << "Fatal Error:  " << errorMessage << std::endl;
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void errorCallback(GLenum source, GLenum type, GLuint id,
                   GLenum severity, GLsizei length,
                   const GLchar* message, const void* userParam)
{
    std::cout << "Error Message - " << message << std::endl;
}