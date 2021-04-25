#include "MainGame.h"
#include "Errors.h"

// For debugging
#include <iostream>

MainGame::MainGame() : 
    _window(nullptr),
    _screenWidth(1024),
    _screenHeight(768),
    _gameState(GameState::PLAY),
    _time(0.0f),
    _timestep(0.01f),
    _vao(0)
{

}

MainGame::~MainGame()
{

}

void MainGame::run()
{
    initSystems();

    // Temporary test code
    _testSprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

    // When this returns game is ready to quit
    gameLoop();

    // Cleanup and exit program
    SDL_DestroyWindow(_window);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

void MainGame::initSystems()
{
    // Initialize all SDL capabilities
    // May eventually only use a subset of them for performance reasons
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow("GameEngine",
                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    _screenWidth, _screenHeight,
                    SDL_WINDOW_OPENGL);

    if (_window == nullptr)
    {
        fatalError("Could not create SDL Window.");
    }

    SDL_GLContext glCtx = SDL_GL_CreateContext(_window);
    if (!glCtx)
    {
        fatalError("Could not create OpenGL Context.");
    }

    // Fixes some weird issues
    glewExperimental = true;

    GLenum glError = glewInit();
    if (glError)
    {
        fatalError("Could not initialize GLEW.");
    }

    // Needed for indexed draw calls to work, among other things
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Having 2 frame buffers helps prevent flickering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Set background color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Compile and link shaders
    initShaders();
}

void MainGame::initShaders()
{
    _colorProgram.compileShaders("../../Shaders/colorShader.vert",
                                 "../../Shaders/colorShader.frag");

    _colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
    while (_gameState != GameState::EXIT)
    {
        processInput();

        _time += _timestep;

        drawGame();
    }
}

int MainGame::processInput()
{
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt))
    {
        switch (evnt.type)
        {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                return 0;
        }
    }
    // This makes MSVC shut up about control paths
    return 0;
}

void MainGame::drawGame()
{
    // Clear stuff
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use color shaders
    _colorProgram.use();

    // Set Uniform values on the GPU
    setUniforms();

    // Temporary test code
    _testSprite.draw();

    // Unbind shaders
    _colorProgram.unuse();

    // Show stuff on the screen
    SDL_GL_SwapWindow(_window);
}

void MainGame::setUniforms()
{
    GLuint timeLocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, _time);

    GLuint resLocation = _colorProgram.getUniformLocation("res");
    glUniform2ui(resLocation, _screenWidth, _screenHeight);
}