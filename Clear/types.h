#pragma once

#include "constants.h"

struct Record {
    int move;
    int castlePerm;
    int enPassant;
    int fiftyMove;
    unsigned long long posKey;
};

struct Move {
    int move;
    int score;

    Move(const int moveInt, const int moveScore) {
        move = moveInt;
        score = moveScore;
    }
};

struct MoveList {
    int count;
    Move moves[MAX_MOVES];

    void addMove(const int move, const int score) {
        moves[count] = Move(move, score);
        ++count;
    }

    void addMove(const Move& move) {
        moves[count] = move;
        ++count;
    }
};

