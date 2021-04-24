#include "MainGame.h"

int main(int argc, char* args[])
{
    MainGame mainGame = MainGame();
    mainGame.run();

    // Execution should never get this far
    return 1;
}