#if !defined(GAME_H)
#define GAME_H
#include "settings.h"
#include "grid.h"
#include "bag.h"
#include "queue.h"
#include "block.h"
#include <stdint.h>


typedef struct 
{
    GameGrid grid;

    PieceBag pb;

    PieceQueue queue;
  
    // current block
    Block block;

    float down_timer;
    float time;

    Font font;

    uint32_t score;
    uint32_t level;
    uint32_t lines_cleared;

    GameState state;

    int isFullScreen;

}Game;
void initGame(Game *game);
void gameLoop(Game *game);
void handleInput(Game *game);
int blockTimer(Game *game);
int moveBlockDown(Game *game);
void drawHUDLeft(Game *game);
void drawHUDRight(Game *game);
int getScore(Game *game, int lines_cleared);
void drawGameOver(Game *game);
void showControls(Game *game);
void handleInputGame(Game *game);

#endif // GAME_H
