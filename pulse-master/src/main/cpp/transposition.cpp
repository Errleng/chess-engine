//
// Created by Recursor on 8/9/2018.
//

#include "transposition.h"

Transposition globalTT;

Transposition::Transposition() {
    this->setSize(0x4000000);
}

int Transposition::setSize(size_t size) {
    free(this->tt);
    if (size & (size - 1)) {
        size--;
        for (int i = 1; i < 32; i *= 2) {
            size |= size >> i;
        }
        size++;
        size >>= 1;
    }

    if (size < 16) {
        this->size = 0;
        return 0;
    }
    this->size = (size / sizeof(ttEntry)) - 1;
    this->tt = (ttEntry *) malloc(size);
    return 0;
}

int Transposition::probe(uint64_t ZKey, int depth, int alpha, int beta) {
    if (!this->size)
        return Transposition::INVALID;
    uint64_t index = ZKey % this->size;
    ttEntry *entry = &this->tt[index];
    if (ZKey == entry->zobristKey) {
        if (entry->depth >= depth) {
            if (entry->flags == TT_EXACT)
                return entry->score;
            if (entry->flags == TT_BETA && (entry->score >= beta))
                return beta;
            if (entry->flags == TT_ALPHA && (entry->score <= alpha))
                return alpha;
        }
    }
    return Transposition::INVALID;
}

void Transposition::save(uint64_t ZKey, int depth, int score, uint8_t flags) {
    if (!this->size)
        return;
    uint64_t index = ZKey % this->size;
    ttEntry *entry = &this->tt[index];
    if ( (entry->zobristKey == ZKey) && (entry->depth >= depth) )
        return;
    entry->zobristKey = ZKey;
    entry->depth = depth;
    entry->score = score;
    entry->flags = flags;
}

