//
// Created by Recursor on 8/8/2018.
//

#include "board.h"
#include "util.h"

namespace Superior {

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

    CPiece opp_CPiece(const CPiece p) {
        return static_cast<CPiece>(((p - 1) ^ 1) + 1);
    }

    Square forward(const Square x, const Color c) {
        return static_cast<Square>(x ^ (56 * c));
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

    int charToCastling(const char c) {
        string kingQueen = "KQkq";
        size_t i = kingQueen.find(c);
        if (i == -1)
            return 0;
        else
            return 1 << i;
    }

    Key::Key() {
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

    void Key::set(const Board board) {
        const Board::Stack *s = &board.stack[board.ply];
        zobrist = color[board.player];
        for (int x = Square::a1; x < Square::Size; ++x) {
            zobrist ^= square[board[x]][x];
        }
    }

    void Key::update(const Board board, Move move) {
        Square x = Square::None;
        const Color player = board.player;
        const Color enemy = opp_color(player);
        const CPiece p = board[move.from];
        const Board::Stack *s = &board.stack[board.ply];

        zobrist = s->key.zobrist;
        zobrist ^= play;
        if (move != 0) {
            zobrist ^= square[p][move.from] ^ square[p][move.to];
            zobrist ^= square[board[move.to]][move.to];
            if (cpieceToPiece(p) == Piece::Pawn) {
                if (move.promotion)
                    zobrist ^= square[p][move.to] ^ square[toCPiece(move.promotion, player)][move.to];
                else if (s.enpassant == move.to)
                    zobrist ^= square[pieceToCPiece(Piece::Pawn, enemy)][toSquare(file(move.to), rank(move.from))];
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

    size_t Key::index(const size_t mask) const {
        return static_cast<size_t>(zobrist & mask);
    }

    uint32_t Key::code() const {
        return static_cast<uint32_t>(zobrist >> 32);
    }

    void PawnKey::set(const Board board) {
        uint64_t b = board.piece[Piece::Pawn] | board.piece[Piece::King];
        while (b) {
            auto x = popSquareBitboard(b);
            code ^= Key::square[board[x]][x];
        }
    }

    void PawnKey::update(const Board board, Move move) {
        const CPiece p = board[move.from];
        const Board::Stack *s = &board.stack[board.ply];

        code = s->pawnKey.code;
        if (cpieceToPiece(p) == Piece::Pawn) {
            code ^= Key::square[p][move.from];
            if (!move.promotion) code ^= Key::square[p][move.to];
            if (s->enpassant == move.to) code ^= Key::square[opp_CPiece(p)][toSquare(file(move.to), rank(move.from))];
        } else if (cpieceToPiece(p) == Piece::King) {
            code ^= Key::square[p][move.from] ^ Key::square[p][move.to];
        }
        if (toPiece(board[move.to]) == Piece::Pawn) code ^= Key::square[board[move.to]][move.from];
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







