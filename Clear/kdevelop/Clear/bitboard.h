#ifndef BITBOARD_H
#define BITBOARD_H

#include "utils.h"

class Bitboard
{
public:
    unsigned long long value;

    bool isEmpty();
    void setBit(int square);
    void clearBit(int square);
    int popBit();
    int getBitCount();
    void print();
};

#endif // BITBOARD_H
