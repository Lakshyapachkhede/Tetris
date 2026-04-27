#include "grid.h"
#include "block.h"

int getGridScreenX(int j)
{
    return (CELL_START_X + CELL_SIZE * j);
}
int getGridScreenY(int i)
{
    return (CELL_START_Y + CELL_SIZE * i);
}


void drawGrid(GameGrid *grid)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            Rectangle rect = {getGridScreenX(j), getGridScreenY(i), CELL_SIZE, CELL_SIZE};

            if (grid->cells[i][j] != EMPTY)
            {
                DrawRectangleRec(rect, g_colors[grid->cells[i][j]]);
            }
            
            DrawRectangleLinesEx(rect, 1, GRID_COLOR);

            // DrawText(TextFormat("(%d, %d)", i, j), getGridScreenX(j), getGridScreenY(i), 10, RED);
        }
    }
}


void resetGrid(GameGrid *grid)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            grid->cells[i][j] = EMPTY;
        }
    }
}




int removeFilledRows(GameGrid *grid)
{   
    int filled_lines = 0;
    for (int i = ROWS - 1; i >= 0; i--)
    {
        int all_fill = 1;
        for (int j = 0; j < COLS; j++)
        {
            if (grid->cells[i][j] == EMPTY)
            {
                all_fill = 0;
                break;
            }
        }

        if (all_fill)
        {
            filled_lines++;
            for (int k = i; k > 0; k--)
            {
                for (int j = 0; j < COLS; j++)
                {
                    grid->cells[k][j] = grid->cells[k - 1][j];
                }
            }

            for (int j = 0; j < COLS; j++)
                grid->cells[0][j] = EMPTY;

            i++;
        }
    }

    return filled_lines;
}


int isValidPosition(Block *block, GameGrid *grid)
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

                if (y >= 0 && grid->cells[y][x] != EMPTY)
                    return 0;
            }
        }
    }
    return 1;
}

void addtoGrid(Block *block, GameGrid *grid)
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
                    grid->cells[newY][newX] = block->type;
            }
        }
    }
}