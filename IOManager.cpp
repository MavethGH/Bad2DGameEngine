#include "IOManager.h"
#include <fstream>

bool IOManager::readFile(const std::string& filePath, std::vector<char>& buffer)
{
    std::ifstream fileStream(filePath, std::ios::binary);
    if (fileStream.fail())
    {
        perror(filePath.c_str());
        return false;
    }

    // Get file size
    fileStream.seekg(0, std::ios::end);
    int fileSize = fileStream.tellg();
    fileStream.seekg(0, std::ios::beg);

    // Account for header bytes
    fileSize -= fileStream.tellg();

    buffer.resize(fileSize);
    fileStream.read(&buffer[0], fileSize);
    
    fileStream.close();
    return true;
}