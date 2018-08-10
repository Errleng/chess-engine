//
// Created by Recursor on 8/9/2018.
//

#ifndef MAIN_TRANSPOSITION_H
#define MAIN_TRANSPOSITION_H

#include <iostream>
#include "position.h"

struct ttEntry {
    uint64_t zobristKey;
    int depth;
    int score;
    uint8_t flags;
};

enum ttFlags {
    TT_EXACT,
    TT_ALPHA,
    TT_BETA,
};

class Transposition {
public:
    Transposition();
    static const int INVALID = 32767;
    size_t size;
    ttEntry* tt;

    int setSize(size_t size);
    int probe(uint64_t ZKey, int depth, int alpha, int beta);
    void save(uint64_t ZKey, int depth, int score, uint8_t flags);
};

extern Transposition globalTT;

#endif //MAIN_TRANSPOSITION_H
