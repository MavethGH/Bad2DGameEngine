#pragma once

#include <vector>
#include <string>

class IOManager
{
    public:
        static bool readFile(std::string& filePath, std::vector<char>& buffer);
};