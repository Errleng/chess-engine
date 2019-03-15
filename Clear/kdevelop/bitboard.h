#pragma once

#include "utils.h"

class Bitboard {
public:
    unsigned long long value;

    bool isEmpty();
    void setBit(int square);
    void clearBit(int square);
    int popBit();
    int getBitCount();
    void print();
};

