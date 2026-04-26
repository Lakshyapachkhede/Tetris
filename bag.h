#if !defined(BAG_H)
#define BAG_H
#include "settings.h"

#define BAG_SIZE 7

typedef struct {
    BlocksId bag[BAG_SIZE];
    int index;
} PieceBag;

BlocksId getNextPiece(PieceBag *pb);
void initBag(PieceBag *pb);
void shuffleBag(BlocksId *bag);

#endif // BAG_H
