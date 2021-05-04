#include "Texture.h"
#include <SDL2/SDL_image.h>

Texture::Texture(const std::string& imageFilePath)
{
    SDL_Surface* image = IMG_Load(imageFilePath.c_str());
    init(image);
}

Texture::Texture(SDL_Surface* image)
{
    init(image);
}

void Texture::init(SDL_Surface* image)
{
    // Allow direct reading of the image pixels
    SDL_LockSurface(image);

    // Convert to a format that OpenGL can use
    // There's plenty of formats that would work here, but ABGR is not one of them
    SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    SDL_Surface* tex = SDL_ConvertSurface(image, format, 0);
    SDL_FreeFormat(format);

    // For convenience
    w = tex->w;
    h = tex->h;

    // Create the OpenGL texture from the loaded image
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, 
                 GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels);

    // Texture Params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // Mipmaps!
    glGenerateMipmap(GL_TEXTURE_2D);

    // Cleanup
    SDL_UnlockSurface(image);
}



Texture::~Texture()
{

}