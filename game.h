#if !defined(GAME_H)
#define GAME_H
#include "settings.h"
#include "grid.h"
#include "bag.h"
#include "queue.h"
#include "block.h"


typedef struct 
{
    GameGrid grid;

    PieceBag pb;

    PieceQueue queue;
  
    // current block
    Block block;

    float down_timer;
    float time;
}Game;
void initGame(Game *game);
void gameLoop(Game *game);
void handleInput(Game *game);
int blockTimer(Game *game);
int moveBlockDown(Game *game);



#endif // GAME_H
