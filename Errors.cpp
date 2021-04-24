#include "Errors.h"

#include <iostream>
#include <SDL.h>

void fatalError(std::string errorMessage)
{
    std::cout << "Fatal Error:  " << errorMessage << std::endl;
    SDL_Quit();
    exit(EXIT_FAILURE);
}