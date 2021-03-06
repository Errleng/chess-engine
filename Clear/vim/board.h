#pragma once

#include <iostream>
#include <iomanip>
#include "types.h"
#include "bitboard.h"

class Board {
public:
    int side;
    int enPassant;
    int fiftyMove;
    int ply;
    int histPly;
    int castlePerm;

    unsigned long long posKey;

    std::array<int, NUM_POSSIBLE_SQUARES> pieces;
    std::array<int, NUM_PIECES> pieceNums;
    std::array<int, NUM_PIECE_TYPES> bigPieces;
    std::array<int, NUM_PIECE_TYPES> majorPieces;
    std::array<int, NUM_PIECE_TYPES> minorPieces;
    std::array<int, NUM_MATERIAL> material;
    std::array<int, NUM_KING_SQUARES> kingSq;
    std::array<Bitboard, NUM_BITBOARD_PAWNS> pawns;
    std::array<Record, MAX_MOVES> history;
    std::array<std::array<int, MAX_NUM_PIECE_TYPE>, NUM_PIECES> pieceList;

    MoveList moveList;

    unsigned long long genPosKey();
    bool isSqAttacked(const int square, const int sideToCheck);
    bool check();
    bool parseFen(const std::string& fen);
    void updateMaterial();
//    void addQuietMove(const int move, const MoveList& moveList);
//    void addCaptureMove(const int move, const MoveList& moveList);
//    void addEnPassantMove(const int move, const MoveList& moveList);
//    void addPawnCaptureMove(const int side, const int fromSq, const int toSq, const int capture, const MoveList& moveList);
    void generateAllMoves();
    void reset();
    void print();
};

