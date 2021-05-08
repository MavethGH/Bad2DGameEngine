#pragma once

#include <gl/glew.h>
#include <string>
#include <SDL2/SDL.h>

class Texture
{
    public:
        Texture(const std::string& imageFilePath);
        Texture(SDL_Surface* image);
        ~Texture();
        GLuint id;
        int w;
        int h;
    private:
        void init(SDL_Surface* image);
        void flipSDLSurface(SDL_Surface* surf);
};