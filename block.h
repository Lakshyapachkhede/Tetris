#if !defined(BLOCK_H)
#define BLOCK_H
#include "settings.h"
#include "queue.h"
#include "bag.h"


typedef struct Block
{
    BlocksId type;
    RotationId rotation;
    const int (*mat)[BLOCK_MATRIX_SIZE];
    // these are top left location on grid not actual screen coordinates
    int x;
    int y;
} Block;


typedef struct GameGrid GameGrid;

// gives a new block for game
void resetBlock(Block *block, PieceQueue *queue, PieceBag *pb);

void changeBlockRotation(Block *block, RotationId r);

// draws ghost block on game grid

void drawGhostBlock(Block *block, GameGrid *grid);

// draws block on game grid

void drawBlockOnGrid(Block *block);

// function to draw block on desired screen cooordinates
void drawBlock(Block *block, int x, int y);



#endif // BLOCK_H
