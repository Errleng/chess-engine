#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>

enum SIDE {
    WHITE,
    BLACK,
    BOTH
};

enum PIECES {
    EMPTY,
    WP,
    WN,
    WB,
    WR,
    WQ,
    WK,
    BP,
    BN,
    BB,
    BR,
    BQ,
    BK
};

enum FILES {
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H,
    FILE_NONE
};

enum RANKS {
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_NONE
};

enum SQUARES {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    NONE, OFFBOARD
};

enum CASTLING {
    WKCA = 1,
    WQCA = 2,
    BKCA = 4,
    BQCA = 8
};

const int NUM_SQUARES = 64;
const int NUM_POSSIBLE_SQUARES = 120;
const int MAX_MOVES = 2048;
const int MAX_MOVES_POS = 256;

const int NUM_PIECES = 13;
const int NUM_PIECE_TYPES = 2;
const int NUM_KING_SQUARES = 2;
const int NUM_MATERIAL = 2;
const int NUM_BITBOARD_PAWNS = 3;
const int MAX_NUM_PIECE_TYPE = 10;

// flags
const int FLAG_EN_PASSANT = 0x40000;
const int FLAG_PAWN_START = 0x80000;
const int FLAG_CASTLE = 0x1000000;
const int FLAG_CAPTURE = 0x7C000;
const int FLAG_PROMOTION = 0xF00000;

// arrays (for speed too)
const std::array<char, 14> PIECE_CHAR = {".PNBRQKpnbrqk"};
const std::array<char, 4> SIDE_CHAR = {"wb-"};
const std::array<char, 9> RANK_CHAR = {"12345678"};
const std::array<char, 9> FILE_CHAR = {"abcdefgh"};
const std::array<int, NUM_PIECES> PIECE_COLOUR = {SIDE::BOTH, SIDE::WHITE, SIDE::WHITE, SIDE::WHITE, SIDE::WHITE, SIDE::WHITE, SIDE::WHITE, SIDE::BLACK, SIDE::BLACK, SIDE::BLACK, SIDE::BLACK, SIDE::BLACK, SIDE::BLACK};
const std::array<bool, NUM_PIECES> IS_PIECE_BIG = {false, false, true, true, true, true, true, false, true, true, true, true, true};
const std::array<bool, NUM_PIECES> IS_PIECE_MAJOR = {false, false, false, false, true, true, true, false, false, false, true, true};
const std::array<bool, NUM_PIECES> IS_PIECE_MINOR = {false, false, true, true, false, false, false, false, true, true, false, false, false};
const std::array<int, NUM_PIECES> PIECE_VALUES = {0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000};
const std::array<int, NUM_SQUARES> BIT_TABLE = {63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2, 51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52, 26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28, 58, 20, 37, 17, 36, 8};

const std::array<std::array<int, 8>, NUM_PIECES> PIECE_DIRS = {{
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 }
}};
const std::array<int, NUM_PIECES> NUM_DIRS = {0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8};
const std::array<int, 8> KNIGHT_DIRECTIONS = {-8, -19, -21, -12, 8, 19, 21, 12};
const std::array<int, 4> ROOK_DIRECTIONS = {-1, -10, 1, 10};
const std::array<int, 4> BISHOP_DIRECTIONS = {-9, -11, 11, 9};
const std::array<int, 8> KING_DIRECTIONS = {-1, -10, 1, 10, -9, -11, 11, 9};

const std::array<int, NUM_PIECES> IS_PAWN = {false, true, false, false, false, false, false, true, false, false, false, false, false};	
const std::array<int, NUM_PIECES> IS_KNIGHT = {false, false, true, false, false, false, false, false, true, false, false, false, false};
const std::array<int, NUM_PIECES> IS_KING = {false, false, false, false, false, false, true, false, false, false, false, false, true};
const std::array<int, NUM_PIECES> IS_ROOK_QUEEN = {false, false, false, false, true, true, false, false, false, false, true, true, false};
const std::array<int, NUM_PIECES> IS_BISHOP_QUEEN = {false, false, false, true, false, true, false, false, false, true, false, true, false};
const std::array<int, NUM_PIECES> IS_SLIDER = {false, false, false, true, true, true, false, false, false, true, true, true, false};

const std::array<int, 8> LOOP_SLIDERS = {PIECES::WB, PIECES::WR, PIECES::WQ, 0, PIECES::BB, PIECES::BR, PIECES::BQ, 0};
const std::array<int, 6> LOOP_NON_SLIDERS = {PIECES::WN, PIECES::WK, 0, PIECES::BN, PIECES::BK, 0};
const std::array<int, 2> LOOP_SLIDER_INDEX = {0, 4};
const std::array<int, 2> LOOP_NON_SLIDER_INDEX = {0, 3};

#endif // CONSTANTS_H
