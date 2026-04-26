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
    int x;
    int y;
} Block;


typedef struct GameGrid GameGrid;

void resetBlock(Block *block, PieceQueue *queue, PieceBag *pb);
void changeBlockRotation(Block *block, RotationId r);

void drawGhostBlock(Block *block, GameGrid *grid);
void drawBlock(Block *block);

#endif // BLOCK_H
