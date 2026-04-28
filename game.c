#include "game.h"
#include "grid.h"
#include <stdio.h>


void changeState(Game *game, GameState new)
{
    printf("state changed to %d\n", new);
    game->state = new;
}


void initGame(Game *game)
{

    resetGrid(&game->grid);
    initBag(&game->pb);
    initQueue(&game->queue, &game->pb);
    resetBlock(&game->block, &game->queue, &game->pb);

    game->down_timer = 0;
    game->time = 0;
    game->font = LoadFont(FONT_PATH);

    game->score = 0;
    game->level = 0;
    game->lines_cleared = 0;

    changeState(game, GAME_RUN);

    game->isFullScreen = 0;

    game->showGrid = 1;

    initScoreList(&game->score_list);

}

void gameLoop(Game *game)
{

    while (!WindowShouldClose())
    {

        handleInput(game);

        BeginDrawing();
        
        ClearBackground(BG_COLOR);

        drawGame(game);
        
        if(game->state == GAME_RUN)
        {
            handleInputGame(game);

            if(blockTimer(game))
            {
                moveBlockDown(game);
            }

        }

        else if(game->state == GAME_OVER)
        {
            drawGameOver(game);
        }

        else if(game->state == CONTROLS)
        {
            showControls(game);
        }

        else if(game->state == PAUSE)
        {
            drawPause(game);
        }



        EndDrawing();
    }
}

void drawGame(Game *game)
{
    drawBlock(&game->block, getGridScreenX(game->block.x), getGridScreenY(game->block.y));

    drawBoard(&game->grid, game->showGrid);

    drawGhostBlock(&game->block, &game->grid);

    drawHUDLeft(game);

    drawHUDRight(game);

}

void drawTextCenterLarge(Game*game, const char *text, Color color)
{
    Vector2 text_size = MeasureTextEx(
        game->font,
        text,
        FONT_SIZE_LARGE,
        HUD_FONT_SPACE
    );

    DrawTextEx(
        game->font,
        text,
        (Vector2){(WIDTH - text_size.x) / 2, (HEIGHT - text_size.y)/2},
        FONT_SIZE_LARGE,      
        HUD_FONT_SPACE,       
        color
    );

}

Vector2 getHUDTextSize(Game *game, const char*text)
{
    return MeasureTextEx(
        game->font,
        text,
        HUD_FONT_SIZE,
        HUD_FONT_SPACE
    );
}

void showText(Game*game, const char *text, int x, int y)
{
    DrawTextEx(
        game->font,
        text,
        (Vector2){x, y},
        HUD_FONT_SIZE,      
        HUD_FONT_SPACE,       
        HUD_FONT_COLOR
    );

}


void drawGameOver(Game *game)
{
    char *text = "Game Over!";
    drawTextCenterLarge(game, text, RED);
}

void drawPause(Game *game)
{
    char *text = "Pause";
    drawTextCenterLarge(game, text, WHITE);
}


void showControls(Game *game)
{
    char controls_text[256];
    snprintf(controls_text, sizeof(controls_text),
    "Controls\n"
    "Rotate      -> up\n"
    "Move        -> arrow keys\n"
    "Drop        -> left ctrl \n"
    "Full Screen -> F11\n"
    "Restart     -> R\n"
    "Quit        -> Esc\n"
    "Pause       -> P\n"  
    "%s Grid   -> G\n"
    "Highscore   -> %d\n"
    "\n\n"
    "Back        -> C\n"
    , game->showGrid ? "Hide" : "Show"
    ,game->highscore
);
    
    Vector2 text_size = getHUDTextSize(game, controls_text);
    showText(game, controls_text, (WIDTH - text_size.x)/2, (HEIGHT - text_size.y)/2);
}


void drawHUDLeft(Game *game)
{   
    char *text = "Next Blocks";

    Vector2 text_size = getHUDTextSize(game, text);

    showText(
        game,
        text,
       (CELL_START_X - text_size.x) / 2,
        HUD_TEXT_PAD_Y
    );

    for (int i = 0; i < NEXT_BLOCKS_TO_SHOW; i++)
    {
        Block block;
        block.type = game->queue.data[i];
        block.rotation = R_UP;
        block.mat = TETROMINOES[block.type][block.rotation];

        int x = (CELL_START_X - CELL_SIZE * BLOCK_MATRIX_SIZE) / 2;
        int text_y_offset = text_size.y + HUD_TEXT_PAD_Y * 2;
        int y = CELL_SIZE * BLOCK_MATRIX_SIZE * i + text_y_offset;

        drawBlock(&block, x, y);
    }
}


void drawHUDRight(Game *game)
{   

    int startX = (CELL_START_X + COLS * CELL_SIZE);
    int right_width = WIDTH - startX;
    

    char buffer[64];
    int num_texts = 0;


    char *score_text = "Score: ";
    snprintf(buffer, sizeof(buffer), "%s%d", score_text, game->score);
    Vector2 text_size = getHUDTextSize(game, buffer);
    num_texts++;
    showText(game, buffer, startX + (right_width - text_size.x) / 2, HUD_TEXT_PAD_Y * num_texts);


    
    char *level_text = "Level: ";
    snprintf(buffer, sizeof(buffer), "%s%d", level_text, game->level);
    text_size = getHUDTextSize(game, buffer);
    num_texts++;
    showText(game, buffer, startX + (right_width - text_size.x) / 2, HUD_TEXT_PAD_Y * num_texts);



    char *lines_text = "Lines: ";
    snprintf(buffer, sizeof(buffer), "%s%d", lines_text, game->lines_cleared);
    text_size = getHUDTextSize(game, buffer);
    num_texts++;
    showText(game, buffer, startX + (right_width - text_size.x) / 2, HUD_TEXT_PAD_Y * num_texts);



    char *control_text = "Controls: C";
    text_size = getHUDTextSize(game, control_text);
    num_texts++;
    showText(game, control_text, startX + (right_width - text_size.x) / 2, HUD_TEXT_PAD_Y * num_texts);

}

int getScore(Game *game, int lines_cleared)
{
    int base;

    switch (lines_cleared)
    {
        case 1: base = 100; break;
        case 2: base = 300; break;
        case 3: base = 500; break;
        case 4: base = 800; break;
        default: base = 0; break;

    }

    return base * (game->level + 1);
}

int moveBlockDown(Game *game)
{   
    if (game->state != GAME_RUN)
    {
        return 0;
    }
    

    Block temp = game->block;
    temp.y += 1;
    if (isValidPosition(&temp, &game->grid))
    {
        game->block.y += 1;
    
        return 1;
    }
    else
    {
        addtoGrid(&game->block, &game->grid);

        int lines_cleared = removeFilledRows(&game->grid);

        game->lines_cleared += lines_cleared;
        game->level = game->lines_cleared / 10;
        game->score += getScore(game, lines_cleared);

        resetBlock(&game->block, &game->queue, &game->pb);

        if(!isValidPosition(&game->block, &game->grid))
        {   
            changeState(game, GAME_OVER);
        }

        return 0;
    }
}

int blockTimer(Game *game)
{
    game->down_timer += GetFrameTime();
    game->time += GetFrameTime();

    float fallDelay = BASE_DELAY - (game->time * SPEED_UP);

    if (fallDelay < 0.1f)
        fallDelay = 0.1f;

    if (game->down_timer > fallDelay)
    {
        game->down_timer = 0;
        return 1;
    }
    return 0;
}


void handleInputGame(Game *game)
{

    if (IsKeyPressed(KEY_RIGHT))
    {
        Block temp = game->block;
        temp.x += 1;
        if (isValidPosition(&temp, &game->grid))
        {
            game->block.x += 1;
        }
    }

    if (IsKeyPressed(KEY_LEFT))
    {
        Block temp = game->block;
        temp.x -= 1;
        if (isValidPosition(&temp, &game->grid))
        {
            game->block.x -= 1;
        }
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        moveBlockDown(game);
    }
    if (IsKeyPressed(KEY_RIGHT_CONTROL))
    {
        while (moveBlockDown(game))
            ;
    }

    if (IsKeyPressed(KEY_UP))
    {
        RotationId oldRot = game->block.rotation;
        int oldX = game->block.x;
        int oldY = game->block.y;

        RotationId newRot = (game->block.rotation + 1) % NUM_ROTATION;
        changeBlockRotation(&game->block, newRot);

        int success = 0;

        for (int k = 0; k < sizeof(kicks) / sizeof(kicks[0]); k++)
        {
            game->block.x = oldX + kicks[k][0];
            game->block.y = oldY + kicks[k][1];

            if (isValidPosition(&game->block, &game->grid))
            {
                success = 1;
                break;
            }
        }

        if (!success)
        {
            // revert
            game->block.x = oldX;
            game->block.y = oldY;
            changeBlockRotation(&game->block, oldRot);
        }
    }



}


void handleInput(Game *game)
{

    if (IsKeyPressed(KEY_R))
    {
        initGame(game);

    }

    if (IsKeyPressed(KEY_P))
    {   
        if(game->state == GAME_OVER)
            ;
        else if(game->state == PAUSE)
            changeState(game, GAME_RUN);
        else       
            changeState(game, PAUSE);
    }


    if (IsKeyPressed(KEY_C))
    {   
        if(game->state == GAME_OVER)
            ;
        else if(game->state == CONTROLS)
            changeState(game, GAME_RUN);
        else       
            changeState(game, CONTROLS);
    }

    if (IsKeyPressed(KEY_F11))
    {   
        game->isFullScreen = !game->isFullScreen;

        if (game->isFullScreen)
        {
            int monitor = GetCurrentMonitor();
            WIDTH = GetMonitorWidth(monitor);
            HEIGHT = GetMonitorHeight(monitor);
            SetWindowSize(WIDTH, HEIGHT);
            ToggleFullscreen();
        }
        else 
        {
            WIDTH = INIT_WIDTH;
            HEIGHT = INIT_HEIGHT;
            ToggleFullscreen();
            SetWindowSize(WIDTH, HEIGHT);

        }

    }

    if (IsKeyPressed(KEY_G))
    {
        game->showGrid = !game->showGrid;
    }


    

}



