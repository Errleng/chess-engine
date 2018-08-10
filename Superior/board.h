//
// Created by Recursor on 8/8/2018.
//

#ifndef SUPERIOR_BOARD_H
#define SUPERIOR_BOARD_H

#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

namespace Superior {

    struct ColorEnum {
        enum Color : uint8_t {
            White, Black, Size, None
        };
    };
    typedef ColorEnum::Color Color;

    struct PieceEnum {
        enum Piece : uint8_t {
            None, Pawn, Knight, Bishop, Rook, Queen, King, Size
        };
    };
    typedef PieceEnum::Piece Piece;

    struct CPieceEnum {
        enum CPiece : uint8_t {
            None, WPawn, BPawn, WKnight, BKnight, WBishop, BBishop, WRook, BRook, WQueen, BQueen, WKing, BKing, Size
        };
    };
    typedef CPieceEnum::CPiece CPiece;

    struct CastlingEnum {
        enum Castling : uint8_t {
            None = 0, K = 1, Q = 2, k = 4, q = 8, Size = 16
        };
    };
    typedef CastlingEnum::Castling Castling;

    struct SquareEnum {
        enum Square : uint8_t {
            None = 65,
            a1 = 0, b1, c1, d1, e1, f1, g1, h1,
            a2, b2, c2, d2, e2, f2, g2, h2,
            a3, b3, c3, d3, e3, f3, g3, h3,
            a4, b4, c4, d4, e4, f4, g4, h4,
            a5, b5, c5, d5, e5, f5, g5, h5,
            a6, b6, c6, d6, e6, f6, g6, h6,
            a7, b7, c7, d7, e7, f7, g7, h7,
            a8, b8, c8, d8, e8, f8, g8, h8,
            Size,
        };
    };
    typedef SquareEnum::Square Square;

    enum File {
        A = 0x0101010101010101,
        B = 0x0202020202020202,
        C = 0x0404040404040404,
        D = 0x0808080808080808,
        E = 0x1010101010101010,
        F = 0x2020202020202020,
        G = 0x4040404040404040,
        H = 0x8080808080808080
    };

    enum Rank {
        r1 = 0x00000000000000ffUL,
        r2 = 0x000000000000ff00UL,
        r3 = 0x0000000000ff0000UL,
        r4 = 0x00000000ff000000UL,
        r5 = 0x000000ff00000000UL,
        r6 = 0x0000ff0000000000UL,
        r7 = 0x00ff000000000000UL,
        r8 = 0xff00000000000000UL
    };

    struct Key {
    public:
        uint64_t zobrist;
        static uint64_t square[Square::Size][CPiece::Size];
        static uint64_t castling[Castling::Size];
        static uint64_t enpassant[Square::None + 1];
        static uint64_t color[Color::Size];
        static uint64_t play;

        Key();

        void set(const Board board);

        void update(const Board board, Move move);

        size_t index(const size_t mask) const;

        uint32_t code() const;
    };

    struct PawnKey {
    public:
        uint64_t code;

        void set(const Board board);

        void update(const Board board, Move move);
    };

    struct Mask {
        uint64_t bit;                           // bit of square x
        uint64_t diagonal;                      // diagonal thru square x
        uint64_t antidiagonal;                  // antidiagonal thru square x
        uint64_t file;                          // file thru square x
        uint64_t pawnAttack[Color::Size];       // pawn attack from x
        uint64_t pawnPush[Color::Size];         // pawn push from x
        uint64_t openFile[Color::Size];         // open file from x
        uint64_t passedPawn[Color::Size];       // passed pawn from x
        uint64_t backwardPawn[Color::Size];     // backward pawn from x
        uint64_t isolatedPawn;                  // isolated pawn from x
        uint64_t enpassant;                     // enpassant
        uint64_t knight;                        // knight moves from x
        uint64_t king;                          // king moves from x
        uint64_t between[Square::Size];         // squares between x & y
        uint8_t direction[Square::Size];       // direction between x & y
        uint8_t castling;                      // castling right
    };

    struct ResultEnum {
        enum Result {None = 0, Draw, RepetitionDraw, InsufficientMaterialDraw, StalemateDraw, WhiteWin, BlackWin, Size};
    };

    class Board {
    public:
        struct Stack {
            uint64_t pins;
            uint64_t checkers;
            Key key;
            PawnKey pawnKey;
            Square enpassant = Square::None;
            Piece victim;
            int8_t fifty;
            Castling castling;
        };
    };


    void test();
}


#endif //SUPERIOR_BOARD_H
