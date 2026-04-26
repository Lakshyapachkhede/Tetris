// gcc main.c -I..\include -L..\lib -lraylib -lopengl32 -lgdi32 -lwinmm -std=c11 -Wall -O2 -o tetris.exe; if ($?) { ./tetris.exe }
#include "raylib.h"
#include "main.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void shuffleBag(BlocksId *bag)
{
    for (int i = BAG_SIZE - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        BlocksId temp = bag[i];
        bag[i] = bag[j];
        bag[j] = temp;
    }
}

void initBag(PieceBag *pb)
{
    srand(time(NULL));
    for (int i = 0; i < BAG_SIZE; i++)
    {
        pb->bag[i] = i;
    }

    shuffleBag(pb->bag);
    pb->index = 0;
}

BlocksId getNextPiece(PieceBag *pb)
{
    if (pb->index >= BAG_SIZE)
    {
        shuffleBag(pb->bag);
        pb->index = 0;
    }

    return pb->bag[pb->index++];
}

int getScreenX(int j)
{
    return (CELL_START_X + CELL_SIZE * j);
}
int getScreenY(int i)
{
    return (CELL_START_Y + CELL_SIZE * i);
}

void resetBlock(Block *block, PieceBag *pb)
{
    block->type = getNextPiece(pb);
    block->rotation = R_UP;
    block->mat = TETROMINOES[block->type][block->rotation];
    block->y = 0;
    block->x = (COLS - BLOCK_MATRIX_SIZE) / 2;
}

void changeBlockRotation(Block *block, RotationId r)
{
    block->rotation = r;
    block->mat = TETROMINOES[block->type][block->rotation];
}

void addtoBoard(Block *block, int game_grid[ROWS][COLS])
{
    for (int i = 0; i < BLOCK_MATRIX_SIZE; i++)
    {
        for (int j = 0; j < BLOCK_MATRIX_SIZE; j++)
        {
            if (block->mat[i][j] == FILLED)
            {
                int newY = block->y + i;
                int newX = block->x + j;

                if (newY < 0 || newY >= ROWS || newX < 0 || newX >= COLS)
                    continue;
                else
                    game_grid[newY][newX] = block->type;
            }
        }
    }
}

void resetGrid(int game_grid[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            game_grid[i][j] = EMPTY;
        }
    }
}

void removeFilledRows(int game_grid[ROWS][COLS])
{
    for (int i = ROWS - 1; i >= 0; i--)
    {
        int all_fill = 1;
        for (int j = 0; j < COLS; j++)
        {
            if (game_grid[i][j] == EMPTY)
            {
                all_fill = 0;
                break;
            }
        }

        if (all_fill)
        {

            for (int k = i; k > 0; k--)
            {
                for (int j = 0; j < COLS; j++)
                {
                    game_grid[k][j] = game_grid[k - 1][j];
                }
            }

            for (int j = 0; j < COLS; j++)
                game_grid[0][j] = EMPTY;

            i++;
        }
    }
}

int isValidPosition(Block *block, int grid[ROWS][COLS])
{
    for (int i = 0; i < BLOCK_MATRIX_SIZE; i++)
    {
        for (int j = 0; j < BLOCK_MATRIX_SIZE; j++)
        {
            if (block->mat[i][j] == FILLED)
            {
                int y = block->y + i;
                int x = block->x + j;

                if (x < 0 || x >= COLS || y >= ROWS)
                    return 0;

                if (y >= 0 && grid[y][x] != EMPTY)
                    return 0;
            }
        }
    }
    return 1;
}

int moveBlockDown(Block *block, int game_grid[ROWS][COLS], PieceBag *pb)
{
    Block temp = *block;
    temp.y += 1;
    if (isValidPosition(&temp, game_grid))
    {
        block->y += 1;
        return 1;
    }
    else
    {
        addtoBoard(block, game_grid);
        removeFilledRows(game_grid);
        resetBlock(block, pb);
        return 0;
    }
}

int main()
{

    InitWindow(WIDTH, HEIGHT, GAME_NAME);
    SetTargetFPS(FPS);

    // full game grid
    int game_grid[ROWS][COLS];
    resetGrid(game_grid);

    PieceBag pb;
    initBag(&pb);

    // current block
    Block block;
    resetBlock(&block, &pb);

    float timer = 0;
    float time = 0;

    float baseDelay = 0.5f;
    float speedUp = 0.001f;

    while (!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_RIGHT))
        {
            Block temp = block;
            temp.x += 1;
            if (isValidPosition(&temp, game_grid))
            {
                block.x += 1;
            }
        }

        if (IsKeyPressed(KEY_LEFT))
        {
            Block temp = block;
            temp.x -= 1;
            if (isValidPosition(&temp, game_grid))
            {
                block.x -= 1;
            }
        }

        if (IsKeyPressed(KEY_DOWN))
        {
            moveBlockDown(&block, game_grid, &pb);
        }
        if (IsKeyPressed(KEY_RIGHT_CONTROL))
        {
            while(moveBlockDown(&block, game_grid, &pb));
          
        }

        if (IsKeyPressed(KEY_UP))
        {
            RotationId oldRot = block.rotation;
            int oldX = block.x;
            int oldY = block.y;

            RotationId newRot = (block.rotation + 1) % NUM_ROTATION;
            changeBlockRotation(&block, newRot);

            int success = 0;

            for (int k = 0; k < sizeof(kicks) / sizeof(kicks[0]); k++)
            {
                block.x = oldX + kicks[k][0];
                block.y = oldY + kicks[k][1];

                if (isValidPosition(&block, game_grid))
                {
                    success = 1;
                    break;
                }
            }

            if (!success)
            {
                // revert
                block.x = oldX;
                block.y = oldY;
                changeBlockRotation(&block, oldRot);
            }
        }



        timer += GetFrameTime();
        time += GetFrameTime();

        float fallDelay = baseDelay - (time * speedUp);

        if (fallDelay < 0.1f)
            fallDelay = 0.1f;

        if (timer > fallDelay)
        {
            moveBlockDown(&block, game_grid, &pb);
            timer = 0;
        }

        BeginDrawing();
        ClearBackground(BG_COLOR);

        for (int i = 0; i < BLOCK_MATRIX_SIZE; i++)
        {
            for (int j = 0; j < BLOCK_MATRIX_SIZE; j++)
            {
                if (block.mat[i][j] == FILLED)
                    DrawRectangle(getScreenX(block.x + j), getScreenY(block.y + i), CELL_SIZE, CELL_SIZE, g_colors[block.type]);
            }
        }

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {

                if (game_grid[i][j] != EMPTY)
                {
                    DrawRectangle(getScreenX(j), getScreenY(i), CELL_SIZE, CELL_SIZE, g_colors[game_grid[i][j]]);
                }

                Rectangle rect = {getScreenX(j), getScreenY(i), CELL_SIZE, CELL_SIZE};
                DrawRectangleLinesEx(rect, 1, GRID_COLOR);

                // DrawText(TextFormat("(%d, %d)", i, j), getScreenX(j), getScreenY(i), 10, RED);
            }
        }

        Block temp = block;
        while (isValidPosition(&temp, game_grid))
        {

            temp.y++;
        }
        temp.y--;

        for (int i = 0; i < BLOCK_MATRIX_SIZE; i++)
        {
            for (int j = 0; j < BLOCK_MATRIX_SIZE; j++)
            {
                if (block.mat[i][j] == FILLED)
                {
                    DrawRectangleLinesEx(
                        (Rectangle){
                            getScreenX(block.x + j),
                            getScreenY(temp.y + i),
                            CELL_SIZE,
                            CELL_SIZE},
                        2,
                        g_colors[block.type]);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}