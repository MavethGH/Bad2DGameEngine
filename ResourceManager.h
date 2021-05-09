#pragma once

#include "TextureCache.h"
#include <gl/glew.h>

class ResourceManager 
{
public:
    static TextureCache* texCache;
    static GLuint boundTexture;  
};