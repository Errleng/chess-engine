#include "bitboard.h"
#include <iostream>

bool Bitboard::isEmpty() {
    return value != 0;
}

void Bitboard::setBit(int square) {
    value |= Utils::setMask[square];
}

void Bitboard::clearBit(int square) {
    value &= Utils::clearMask[square];
}

int Bitboard::popBit() {
    unsigned long long b = value ^ (value - 1);
    unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
    value &= (value - 1);
    return BIT_TABLE[(fold * 0x783a9b23) >> 26];
}

int Bitboard::getBitCount() {
    int count = 0;
    unsigned long long tempValue = value;
    while (tempValue != 0) {
        tempValue &= (tempValue - 1);
        ++count;
    }
    return count;
}

