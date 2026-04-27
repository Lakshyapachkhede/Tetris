#ifndef SETTINGS_H

#define SETTINGS_H

#include "raylib.h"

#define GAME_NAME "Tetris - Lakshya Pachkhede 23/4/26"

#define INIT_WIDTH 800
#define INIT_HEIGHT 600

extern int WIDTH;
extern int HEIGHT;


#define FPS 60
#define ROWS 20
#define COLS 10

#define CELL_SIZE (HEIGHT / ROWS)
#define CELL_START_X ((WIDTH - (CELL_SIZE * COLS)) / 2)
#define CELL_START_Y 0

#define BLOCK_MATRIX_SIZE 4

#define EMPTY -1
#define FILLED 1


#define BG_COLOR (Color){0, 0, 0, 255}
#define GRID_COLOR (Color){150, 140, 150, 255}

typedef enum RotationId
{
    R_UP,
    R_RIGHT,
    R_DOWN,
    R_LEFT,
    NUM_ROTATION
}RotationId;

typedef int Matrix4x4[BLOCK_MATRIX_SIZE][BLOCK_MATRIX_SIZE];



typedef enum BlocksId 
{
    I_BLOCK,
    O_BLOCK,
    T_BLOCK,
    S_BLOCK,
    Z_BLOCK,
    J_BLOCK,
    L_BLOCK,
    NUM_BLOCKS
}BlocksId;

extern Color g_colors[NUM_BLOCKS];
extern Matrix4x4 TETROMINOES[NUM_BLOCKS][NUM_ROTATION];

extern int kicks[6][2];



#define BASE_DELAY 0.5f
#define SPEED_UP 0.001f


#define NEXT_BLOCKS_TO_SHOW 3



#define HUD_FONT_COLOR WHITE
#define HUD_FONT_SIZE 16
#define HUD_FONT_SPACE 1
#define HUD_TEXT_PAD_Y 40
#define GAME_OVER_FONT_SIZE 40


typedef enum GameState {GAME_RUN, GAME_OVER, CONTROLS, HIGHSCORE} GameState;


#define MAX_SCORES 10
#define SCORES_FILE "scores.txt"

#endif // SETTINGS_H
