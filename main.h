#ifndef SETTINGS_H

#define SETTINGS_H

#include "raylib.h"

#define GAME_NAME "Tetris - Lakshya Pachkhede 23/4/26"

#define WIDTH 800
#define HEIGHT 600

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

const Color g_colors[NUM_BLOCKS] = {
    [I_BLOCK] = (Color){0, 255, 255, 255},
    [O_BLOCK] = (Color){255, 255, 0, 255},
    [T_BLOCK] = (Color){160, 0, 240, 255},
    [S_BLOCK] = (Color){0, 255, 0, 255},
    [Z_BLOCK] = (Color){255, 0, 0, 255},
    [J_BLOCK] = (Color){0, 0, 255, 255},
    [L_BLOCK] = (Color){255, 140, 0, 255}
};

const Matrix4x4 TETROMINOES[NUM_BLOCKS][NUM_ROTATION] =
{
    // I_BLOCK
    [I_BLOCK] = {
        [R_UP] = {
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {FILLED, FILLED, FILLED, FILLED},
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_RIGHT] = {
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY}
        },
        [R_DOWN] = {
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {FILLED, FILLED, FILLED, FILLED},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_LEFT] = {
            {EMPTY, EMPTY, FILLED, EMPTY},
            {EMPTY, EMPTY, FILLED, EMPTY},
            {EMPTY, EMPTY, FILLED, EMPTY},
            {EMPTY, EMPTY, FILLED, EMPTY}
        }
    },

    // O_BLOCK
    [O_BLOCK] = {
        [R_UP] = {
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_RIGHT] = {
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_DOWN] = {
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_LEFT] = {
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        }
    },

    // T_BLOCK
    [T_BLOCK] = {
        [R_UP] = {
            {EMPTY, FILLED, EMPTY, EMPTY},
            {FILLED, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_RIGHT] = {
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_DOWN] = {
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {FILLED, FILLED, FILLED, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_LEFT] = {
            {EMPTY, FILLED, EMPTY, EMPTY},
            {FILLED, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        }
    },

    // S_BLOCK
    [S_BLOCK] = {
        [R_UP] = {
            {EMPTY, FILLED, FILLED, EMPTY},
            {FILLED, FILLED, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_RIGHT] = {
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_DOWN] = {
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, FILLED, FILLED, EMPTY},
            {FILLED, FILLED, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_LEFT] = {
            {FILLED, EMPTY, EMPTY, EMPTY},
            {FILLED, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        }
    },

    // Z_BLOCK
    [Z_BLOCK] = {
        [R_UP] = {
            {FILLED, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_RIGHT] = {
            {EMPTY, EMPTY, FILLED, EMPTY},
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_DOWN] = {
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {FILLED, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_LEFT] = {
            {EMPTY, FILLED, EMPTY, EMPTY},
            {FILLED, FILLED, EMPTY, EMPTY},
            {FILLED, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        }
    },

    // J_BLOCK
    [J_BLOCK] = {
        [R_UP] = {
            {FILLED, EMPTY, EMPTY, EMPTY},
            {FILLED, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_RIGHT] = {
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_DOWN] = {
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {FILLED, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_LEFT] = {
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {FILLED, FILLED, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        }
    },

    // L_BLOCK
    [L_BLOCK] = {
        [R_UP] = {
            {EMPTY, EMPTY, FILLED, EMPTY},
            {FILLED, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_RIGHT] = {
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, FILLED, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_DOWN] = {
            {EMPTY, EMPTY, EMPTY, EMPTY},
            {FILLED, FILLED, FILLED, EMPTY},
            {FILLED, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        },
        [R_LEFT] = {
            {FILLED, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, FILLED, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY}
        }
    }
};


const int kicks[][2] = {
    {0, 0},   // no move
    {-1, 0},  // left
    {1, 0},   // right
    {-2, 0},  // bigger left
    {2, 0},   // bigger right
    {0, -1}   // up (important near floor)
};

#define BAG_SIZE 7

typedef struct {
    BlocksId bag[BAG_SIZE];
    int index;
} PieceBag;

BlocksId getNextPiece(PieceBag *pb);
void initBag(PieceBag *pb);
void shuffleBag(BlocksId *bag);

typedef struct
{
    BlocksId type;
    RotationId rotation;
    const int (*mat)[BLOCK_MATRIX_SIZE];
    int x;
    int y;
} Block;



#endif // SETTINGS_H
