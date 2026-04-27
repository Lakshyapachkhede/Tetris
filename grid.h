#if !defined(GRID_H)
#define GRID_H
#include "settings.h"

typedef struct GameGrid
{
    int cells[ROWS][COLS];
} GameGrid;

// forward declaration
typedef struct Block Block;

int removeFilledRows(GameGrid *grid);
void resetGrid(GameGrid *grid);
void drawGrid(GameGrid *grid);
int getGridScreenY(int i);
int getGridScreenX(int j);
int isValidPosition(Block *block, GameGrid *grid);
void addtoGrid(Block *block, GameGrid *grid);



#endif // GRID_H
