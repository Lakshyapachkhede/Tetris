#include "raylib.h"
#include "settings.h"
#include "game.h"


int main()
{
    InitWindow(WIDTH, HEIGHT, GAME_NAME);
    SetTargetFPS(FPS);

    Game game;

    initGame(&game);
    gameLoop(&game);


    CloseWindow();

    return 0;
}

