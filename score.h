#if !defined(SCORE_H)
#define SCORE_H
#include <stdint.h>
#include "settings.h"

typedef struct Score
{
    uint32_t score;
    char date[11];
}Score;

typedef struct ScoreList
{
    FILE *f;
    Score list[MAX_SCORES];
    int count;
    int is_loaded;
}ScoreList;

void initScoreList(ScoreList *list);

uint32_t getHighScore(ScoreList *list);

void addScore(ScoreList *list, uint32_t score);

void sortScoreList(ScoreList *list);

void getCurrentDate(char *buffer, size_t size);

void closeScoreList(ScoreList *list);

void saveScoreList(ScoreList *list);



#endif // SCORE_H
