#if !defined(QUEUE_H)
#define QUEUE_H
#include "settings.h"
#include "bag.h"

#define QUEUE_SIZE 5

typedef struct {
    BlocksId data[QUEUE_SIZE];
} PieceQueue;

void initQueue(PieceQueue *q, PieceBag *bag);
BlocksId popQueue(PieceQueue *q, PieceBag *bag);

#endif // QUEUE_H
