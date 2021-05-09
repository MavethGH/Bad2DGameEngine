#pragma once

#include <unordered_map>
#include "Texture.h"

class TextureCache
{
    public:
        typedef std::unordered_map<std::string, Texture*> TexCacheMap;
        Texture* getTexture(const std::string& key);
    private:
        TexCacheMap cache;
};
