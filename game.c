#include "game.h"
#include "grid.h"



void initGame(Game *game)
{
        // full game grid

    resetGrid(&game->grid);


    initBag(&game->pb);


    initQueue(&game->queue, &game->pb);

    resetBlock(&game->block, &game->queue, &game->pb);

    game->down_timer = 0;
    game->time = 0;
}

void gameLoop(Game *game)
{
    while (!WindowShouldClose())
    {

        handleInput(game);

        if(blockTimer(game))
        {
            moveBlockDown(game);
        }

        BeginDrawing();
        ClearBackground(BG_COLOR);

        drawBlock(&game->block);

        drawGrid(&game->grid);

        drawGhostBlock(&game->block, &game->grid);

        EndDrawing();
    }
}


int moveBlockDown(Game *game)
{
    Block temp = game->block;
    temp.y += 1;
    if (isValidPosition(&temp, &game->grid))
    {
        game->block.y += 1;
        return 1;
    }
    else
    {
        addtoGrid(&game->block, &game->grid);
        removeFilledRows(&game->grid);
        resetBlock(&game->block, &game->queue, &game->pb);
        return 0;
    }
}

int blockTimer(Game *game)
{
    game->down_timer += GetFrameTime();
    game->time += GetFrameTime();

    float fallDelay = BASE_DELAY - (game->time * SPEED_UP);

    if (fallDelay < 0.1f)
        fallDelay = 0.1f;

    if (game->down_timer > fallDelay)
    {
        game->down_timer = 0;
        return 1;
    }
    return 0;
}


void handleInput(Game *game)
{
    if (IsKeyPressed(KEY_RIGHT))
    {
        Block temp = game->block;
        temp.x += 1;
        if (isValidPosition(&temp, &game->grid))
        {
            game->block.x += 1;
        }
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        Block temp = game->block;
        temp.x -= 1;
        if (isValidPosition(&temp, &game->grid))
        {
            game->block.x -= 1;
        }
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        moveBlockDown(game);
    }
    if (IsKeyPressed(KEY_RIGHT_CONTROL))
    {
        while (moveBlockDown(game))
            ;
    }

    if (IsKeyPressed(KEY_UP))
    {
        RotationId oldRot = game->block.rotation;
        int oldX = game->block.x;
        int oldY = game->block.y;

        RotationId newRot = (game->block.rotation + 1) % NUM_ROTATION;
        changeBlockRotation(&game->block, newRot);

        int success = 0;

        for (int k = 0; k < sizeof(kicks) / sizeof(kicks[0]); k++)
        {
            game->block.x = oldX + kicks[k][0];
            game->block.y = oldY + kicks[k][1];

            if (isValidPosition(&game->block, &game->grid))
            {
                success = 1;
                break;
            }
        }

        if (!success)
        {
            // revert
            game->block.x = oldX;
            game->block.y = oldY;
            changeBlockRotation(&game->block, oldRot);
        }
    }
}



