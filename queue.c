#include "queue.h"


void initQueue(PieceQueue *q, PieceBag *bag)
{
    for (int i = 0; i < QUEUE_SIZE; i++)
    {
        q->data[i] = getNextPiece(bag);
    }
}

BlocksId popQueue(PieceQueue *q, PieceBag *bag)
{
    // take the first piece
    BlocksId next = q->data[0];

    // shift everything left
    for (int i = 0; i < QUEUE_SIZE - 1; i++)
    {
        q->data[i] = q->data[i + 1];
    }

    // refill last slot from bag
    q->data[QUEUE_SIZE - 1] = getNextPiece(bag);

    return next;
}