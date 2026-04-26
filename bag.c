#include "bag.h"
#include <time.h>
#include <stdlib.h>


void shuffleBag(BlocksId *bag)
{
    for (int i = BAG_SIZE - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        BlocksId temp = bag[i];
        bag[i] = bag[j];
        bag[j] = temp;
    }
}

void initBag(PieceBag *pb)
{
    srand(time(NULL));
    for (int i = 0; i < BAG_SIZE; i++)
    {
        pb->bag[i] = i;
    }

    shuffleBag(pb->bag);
    pb->index = 0;
}

BlocksId getNextPiece(PieceBag *pb)
{
    if (pb->index >= BAG_SIZE)
    {
        shuffleBag(pb->bag);
        pb->index = 0;
    }

    return pb->bag[pb->index++];
}