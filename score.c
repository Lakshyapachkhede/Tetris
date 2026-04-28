#include "score.h"
#include <time.h>
#include <stdio.h>
#include <string.h>


void initScoreList(ScoreList *list)
{

    list->count = 0;
    list->is_loaded = 0;

    list->f = fopen(SCORES_FILE, "r+");

    if(list->f == NULL)
    {
        list->f = fopen(SCORES_FILE, "w+");

        if (!list->f) {
            perror("Failed to create score file");
            list->is_loaded = 0;

        }

        for (int i = 0; i < MAX_SCORES; i++)
        {
            fprintf(list->f, "%u %s\n", 0, "00-00-0000");
        }
        fflush(list->f);
    }

    rewind(list->f);

    Score s;
    while (list->count < MAX_SCORES && fscanf(list->f, "%u %10s", &s.score, s.date) == 2)
    {
        list->list[list->count++] = s;
    }

    while (list->count < MAX_SCORES)
    {
        list->list[list->count].score = 0;
        snprintf(list->list[list->count].date, 11, "00-00-0000");
        list->count++;
    }

    sortScoreList(list);

    list->is_loaded = 1;
    
}

uint32_t getHighScore(ScoreList *list)
{
    if (list->count == 0)
    {
        return -1;
    }
    
    return list->list[0].score;
}

int addScore(ScoreList *list, uint32_t score)
{

    if(score <= list->list[MAX_SCORES-1].score)
    {
        return 0;
    }

    char buffer[11];
    getCurrentDate(buffer, sizeof(buffer));

    list->list[MAX_SCORES-1].score = score;
    strncpy(list->list[MAX_SCORES-1].date, buffer, sizeof(buffer));

    sortScoreList(list);
    saveScoreList(list);


    return 1;

}

void sortScoreList(ScoreList *list)
{
    for (int i = 0; i < MAX_SCORES - 1; i++) {
        int swapped = 0;

        for (int j = 0; j < MAX_SCORES - i - 1; j++) {
            if (list->list[j].score < list->list[j + 1].score) {
                Score temp = list->list[j];
                list->list[j] = list->list[j + 1];
                list->list[j + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }

}



void getCurrentDate(char *buffer, size_t size)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    if (tm_info != NULL)
    {
        strftime(buffer, size, "%d-%m-%Y", tm_info);
    }
    else
    {
        snprintf(buffer, size, "00-00-0000");
    }
}

void closeScoreList(ScoreList *list)
{
    fclose(list->f);
}

void saveScoreList(ScoreList *list)
{
    rewind(list->f);

    freopen(NULL, "w+", list->f);

    for (int i = 0; i < list->count; i++)
    {
        fprintf(list->f, "%u %s\n",
                list->list[i].score,
                list->list[i].date);
    }

    fflush(list->f);
}