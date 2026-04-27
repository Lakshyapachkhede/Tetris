#include "block.h"
#include "grid.h"
#include <stdio.h>

void resetBlock(Block *block, PieceQueue *queue, PieceBag *pb)
{
    block->type = popQueue(queue, pb);
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

void drawGhostBlock(Block *block, GameGrid *grid)
{
    Block temp = *block;
    while (isValidPosition(&temp, grid))
    {
        temp.y++;
    }
    temp.y--;

    for (int i = 0; i < BLOCK_MATRIX_SIZE; i++)
    {
        for (int j = 0; j < BLOCK_MATRIX_SIZE; j++)
        {
            if (block->mat[i][j] == FILLED)
            {
                DrawRectangleLinesEx(
                    (Rectangle){
                        getGridScreenX(block->x + j),
                        getGridScreenY(temp.y + i),
                        CELL_SIZE,
                        CELL_SIZE},
                    2,
                    g_colors[block->type]);
            }
        }
    }
}



void drawBlockOnGrid(Block *block)
{
    for (int i = 0; i < BLOCK_MATRIX_SIZE; i++)
    {
        for (int j = 0; j < BLOCK_MATRIX_SIZE; j++)
        {
            if (block->mat[i][j] == FILLED)
                DrawRectangle(getGridScreenX(block->x + j), getGridScreenY(block->y + i), CELL_SIZE, CELL_SIZE, g_colors[block->type]);
        }
    }
}


void drawBlock(Block *block, int x, int y)
{
    for (int i = 0; i < BLOCK_MATRIX_SIZE; i++)
    {
        for (int j = 0; j < BLOCK_MATRIX_SIZE; j++)
        {
            if (block->mat[i][j] == FILLED)
            {
                Rectangle rect = {(x + j * CELL_SIZE), (y + i * CELL_SIZE), CELL_SIZE, CELL_SIZE};
                DrawRectangleRec(rect, g_colors[block->type]);
                DrawRectangleLinesEx(rect, 1, GRID_COLOR);
            }
        }
    }
}