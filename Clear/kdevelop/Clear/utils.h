#ifndef UTILS_H
#define UTILS_H

// #define NDEBUG

#include <random>
#include <cassert>
#include "constants.h"

namespace Utils
{
    extern unsigned long long sideKey;
    extern std::array<int, NUM_SQUARES> sq64to120;
    extern std::array<int, NUM_POSSIBLE_SQUARES> sq120to64;
    extern std::array<int, NUM_POSSIBLE_SQUARES> filesBoard;
    extern std::array<int, NUM_POSSIBLE_SQUARES> ranksBoard;
    extern std::array<unsigned long long, NUM_SQUARES> setMask;
    extern std::array<unsigned long long, NUM_SQUARES> clearMask;
    extern std::array<unsigned long long, 16> castleKeys;
    extern std::array<std::array<unsigned long long, NUM_POSSIBLE_SQUARES>, 13> pieceKeys;
    extern std::random_device rd;
    extern std::mt19937_64 gen;
    extern std::uniform_int_distribution<unsigned long long> randDistr;

    extern bool isSqOnBoard(const int square);
    extern bool isValidSide (const int side);
    extern bool isFileOrRankValid(const int fileOrRank);
    extern bool isValidPiece(const int piece);
    extern bool isPieceValidOrEmpty(const int piece);
    extern int getFromSq(const int move);
    extern int getToSq(const int move);
    extern int getCapture(const int move);
    extern int getPromotion(const int move);
    extern int fileRankToSq(const int file, const int rank);
    extern int createMoveInt(const int fromSq, const int toSq, const int capture, const int promotion, const int flag);

    extern void initSqArrs();
    extern void initFilesRanks();
    extern void initBitmasks();
    extern void initHashKeys();
    extern void initUtils();
};

#endif // UTILS_H
