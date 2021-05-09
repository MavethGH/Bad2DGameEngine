#include "TextureCache.h"

Texture* TextureCache::getTexture(const std::string& key)
{
    if (!cache.count(key)) {
        cache[key] = new Texture(key);
    }

    return cache[key];
}