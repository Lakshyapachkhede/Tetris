#include "settings.h"

Color g_colors[NUM_BLOCKS] = {
    [I_BLOCK] = (Color){0, 255, 255, 255},
    [O_BLOCK] = (Color){255, 255, 0, 255},
    [T_BLOCK] = (Color){160, 0, 240, 255},
    [S_BLOCK] = (Color){0, 255, 0, 255},
    [Z_BLOCK] = (Color){255, 0, 0, 255},
    [J_BLOCK] = (Color){0, 0, 255, 255},
    [L_BLOCK] = (Color){255, 140, 0, 255}
};

Matrix4x4 TETROMINOES[NUM_BLOCKS][NUM_ROTATION] =
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


int kicks[6][2] = {
    {0, 0},   // no move
    {-1, 0},  // left
    {1, 0},   // right
    {-2, 0},  // bigger left
    {2, 0},   // bigger right
    {0, -1}   // up (important near floor)
};