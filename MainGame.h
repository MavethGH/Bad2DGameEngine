#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include "Sprite.h"
#include "GLSLProgram.h"

enum class GameState 
{
    PLAY, EXIT
};

class MainGame
{
    public:
        MainGame();
        ~MainGame();
        void run();

    private:
        void initSystems();
        void initShaders();
        void gameLoop();
        int processInput();
        void drawGame();
        void setUniforms();

        SDL_Window* _window;
        int _screenWidth;
        int _screenHeight;
        GameState _gameState;
        Sprite _testSprite;
        GLSLProgram _colorProgram;
        float _time;
        float _timestep;
        GLuint _vao;
};