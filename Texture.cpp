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

void Texture::init(SDL_Surface* tex)
{
    // Allow direct reading of the image pixels
    SDL_LockSurface(tex);

    // For convenience
    w = tex->w;
    h = tex->h;
    
    // Flip image so OpenGL doesn't diplay it upside-down
    flipSDLSurface(tex);

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
    SDL_UnlockSurface(tex);
}

// Note: surf is already locked when this is called
void Texture::flipSDLSurface(SDL_Surface* surf)
{
    int pitch = surf->pitch;
    char* temp = new char[pitch];
    char* pixels = (char*)surf->pixels;

    // Switch rows
    for (int i = 0; i < h / 2; ++i)
    {
        char* top = pixels + i * pitch;
        char* bot = pixels + (h - i - 1) * pitch;

        // Top row to temp
        memcpy(temp, top, pitch);
        // Bottom row to top
        memcpy(top, bot, pitch);
        // Temp (top row) to bottom
        memcpy(bot, temp, pitch);


    }
    // Don't leak!
    delete[] temp;
}

Texture::~Texture()
{

}