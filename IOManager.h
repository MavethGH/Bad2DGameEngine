#pragma once

#include <vector>
#include <string>
#include <SDL_rwops.h>

class IOManager
{
    public:
        static bool readFile(const std::string& filePath, std::vector<char>& buffer);
        static SDL_RWops* loadImage(const std::string& filePath);
};