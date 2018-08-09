//
// Created by Recursor on 8/8/2018.
//

#include "board.h"
#include "util.h"

namespace Superior {
    template<typename E>
    constexpr auto E
    e) -> typename std::underlying_type<E>::type {
    return static_cast
    <typename std::underlying_type<E>::type>(e);
}

struct ColorEnum {
    enum Color : uint8_t {
        White, Black, Size, None
    };
};
typedef ColorEnum::Color Color;

Color opp_color(const Color c) {
    return (Color) !static_cast<int>(c);
}

Color charToColor(const char c) {
    string colors = "wb";
    size_t idx = colors.find(c);
    if (idx == -1)
        idx = (size_t) Color::Size;
    return static_cast<Color>(idx);
}

struct PieceEnum {
    enum Piece : uint8_t {
        None, Pawn, Knight, Bishop, Rook, Queen, King, Size
    };
};
typedef PieceEnum::Piece Piece;

Piece charToPiece(char c) {
    string pieces = ".pnbrqk";
    c = static_cast<char>(tolower(c));
    size_t idx = pieces.find(c);
    if (idx == -1)
        idx = 0;
    return static_cast<Piece>(idx);
}

char pieceToChar(const Piece p) {
    return ".PNBRQK?"[static_cast<int>(p)];
}

struct CPieceEnum {
    enum CPiece : uint8_t {
        None, WPawn, BPawn, WKnight, BKnight, WBishop, BBishop, WRook, BRook, WQueen, BQueen, WKing, BKing, Size
    };
};
typedef CPieceEnum::CPiece CPiece;

CPiece pieceToCPiece(const Piece p, const Color c) {
    return static_cast<CPiece>(2 * (static_cast<int>(p)) + (static_cast<int>(c)) - 1);
}

Color pieceToColor(const CPiece cp) {
    Color c[CPiece::Size] =
            {Color::None,
             Color::White, Color::Black, Color::White, Color::Black, Color::White, Color::Black,
             Color::White, Color::Black, Color::White, Color::Black, Color::White, Color::Black};
    return c[cp];
}

Piece cpieceToPiece(const CPiece p) {
    return static_cast<Piece>((p + 1) / 2);
}

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

Square forward(const Square x, const Color c) {
    return static_cast<Square>(x ^ (56 * c)));
}

int rank(const Square x) {
    return x >> 3;
}

int file(const Square x) {
    return x & 7;
}

Square fileRankToSquare(const int f, const int r) {
    if (0 <= f && f < 8 && 0 <= r && r < 8) {
        return static_cast<Square>((r << 3) + f);
    } else {
        return Square::None;
    }
}

Square stringToSquare(string s) {
    if (s.length() > 1) {
        return fileRankToSquare(s[0] - 'a', s[1] - '1');
    } else {
        return Square::None;
    }
}

Square popSquareBitboard(uint64_t &b) {
    return static_cast<Square>(popBit(b));
}

Square firstSquareBitboard(const uint64_t b) {
    return static_cast<Square>(firstBit(b));
}

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

struct CastlingEnum {
    enum Castling : uint8_t {
        None = 0, K = 1, Q = 2, k = 4, q = 8, Size = 16
    };
};
typedef CastlingEnum::Castling Castling;

int charToCastling(const char c) {
    string kingQueen = "KQkq";
    size_t i = kingQueen.find(c);
    if (i == -1)
        return 0;
    else
        return 1 << i;
}

class Board {

};

struct Key {
    uint64_t zobrist;
    static uint64_t square[Square::Size][CPiece::Size];
    static uint64_t castling[Castling::Size];
    static uint64_t enpassant[Square::None + 1];
    static uint64_t color[Color::Size];
    static uint64_t play;

    Key() {
        mt19937 r;
        r.seed(19937);
        uniform_int_distribution<uint64_t> dis(numeric_limits<uint64_t>::min(), numeric_limits<uint64_t>::max());
        for (int p = CPiece::WPawn; p < CPiece::Size; ++p)
            for (int x = Square::a1; x < Square::Size; ++x) square[p][x] = dis(r);
        for (int c = Castling::K; c < Castling::Size; ++c) castling[c] = dis(r);
        for (int x = Square::a4; x < Square::a6; ++x) enpassant[x] = dis(r);
        for (int c = Castling::K; c < Castling::Size; ++c) color[c] = dis(r);
        play = color[Color::White] ^ color[Color::Black];
    }

    void set(const Board board) {
        const Board.Stack *s = &board.stack[board.ply];
        zobrist = color[board.player];
        for (int x = Square::a1; x < Square::Size; ++x) {
            zobrist ^= square[board[x]][x];
        }
    }

    void update(const Board board, Move move) {
        Square x = Square::None;
        const Color player = board.player;
        const Color enemy = opp_color(player);
        const CPiece p = board[move.from];
        const Board.Stack *s = &board.stack[board.ply];

        zobrist = s.key.zobrist;
        zobrist ^= play;
        if (move != 0) {
            zobrist ^= square[p][move.from] ^ square[p][move.to];
            zobrist ^= square[board[move.to]][move.to];
            if (cpieceToPiece(p) == Piece::Pawn) {
                if (move.promotion)
                    zobrist ^= square[p][move.to] ^ square[toCPiece(move.promotion, player)][move.to];
                else if (s.enpassant == move.to)
                    zobrist ^= square[toCPiece(Piece::Pawn, enemy)][toSquare(file(move.to), rank(move.from))];
                else if (abs(move.to - move.from) == 16 &&
                         (board.mask[move.to].enpassant & (board.color[enemy] & board.piece[Piece::Pawn]))) {
                    x = static_cast<Square>((move.from + move.to) / 2);
                }
            } else if (cpieceToPiece(p) == Piece::King) {
                CPiece r = pieceToCPIece(Piece::Rook, board.player);
                if (move.to == move.from + 2) zobrist ^= square[r][move.from + 3] ^ square[r][move.from + 1];
                else if (move.to == move.from - 2) zobrist ^= square[r][move.from - 4] ^ square[r][move.from - 1];
            }
            zobrist ^= enpassant[s.enpassant] ^ enpassant[x];
            zobrist ^= castling[s.castling] ^
                       castling[s.castling & board.mask[move.from].castling & board.mask[move.to].castling];
        }
    }
};

void test() {
    cout << "BOARD TEST" << endl;
    cout << "Color::White = " << (int) Color::White << endl;
    cout << "Opponent White = " << (int) opp_color(Color::White) << endl;
    cout << "'b' Color = " << (int) charToColor('b') << endl;
    cout << "Piece Knight to char = " << pieceToChar(Piece::Knight) << endl;
    cout << "'p' to Piece = " << (int) charToPiece('p') << endl;
    cout << "Piece Knight and Black to CPiece = " << (int) pieceToCPiece(Piece::Knight, Color::Black) << endl;
    cout << "Color of BKing = " << (int) pieceToColor(CPiece::BKing) << endl;
    cout << "BQueen to Piece = " << (int) cpieceToPiece(CPiece::BQueen) << endl;
};
}







