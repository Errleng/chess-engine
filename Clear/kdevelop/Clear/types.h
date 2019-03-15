#ifndef TYPES_H
#define TYPES_H

#include "utils.h"

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

    Move() {};

    Move(const int moveInt, const int moveScore) {
        move = moveInt;
        score = moveScore;
    }

    std::string str() {
        std::string stringRep = "";
        int fromSq = Utils::getFromSq(move);
        int fromFile = Utils::filesBoard[fromSq];
        int fromRank = Utils::ranksBoard[fromSq];

        int toSq = Utils::getToSq(move);
        int toFile = Utils::filesBoard[toSq];
        int toRank = Utils::ranksBoard[toSq];
        int promotion = Utils::getPromotion(move);

        stringRep += ('a' + fromFile);
        stringRep += ('1' + fromRank);
        stringRep += ('a' + toFile);
        stringRep += ('1' + toRank);
        
        if (promotion) {
            char promotionChar = 'q';
            if (IS_KNIGHT[promotion]) {
                promotionChar = 'n';
            } else if (IS_ROOK_QUEEN[promotion] && !IS_BISHOP_QUEEN[promotion]) {
                promotionChar = 'r';
            } else if (!IS_ROOK_QUEEN[promotion] && IS_BISHOP_QUEEN[promotion]) {
                promotionChar = 'b';
            }
            stringRep += promotionChar;
        }
        return stringRep;
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

    void addQuietMove(const int move) {
        addMove(move, 0);
    }

    void addCaptureMove(const int move) {
        addMove(move, 0);
    }

    void addEnPassantMove(const int move) {
        addMove(move, 0);
    }

    void addPawnMove(const int side, const int fromSq, const int toSq) {
        assert(Utils::isSqOnBoard(fromSq));
        assert(Utils::isSqOnBoard(toSq));
        
        if (side == SIDE::WHITE) {
            if (Utils::ranksBoard[fromSq] == RANKS::RANK_7) {
                addQuietMove(Utils::createMoveInt(fromSq, toSq, PIECES::EMPTY, PIECES::WQ, 0));
                addQuietMove(Utils::createMoveInt(fromSq, toSq, PIECES::EMPTY, PIECES::WR, 0));
                addQuietMove(Utils::createMoveInt(fromSq, toSq, PIECES::EMPTY, PIECES::WB, 0));
                addQuietMove(Utils::createMoveInt(fromSq, toSq, PIECES::EMPTY, PIECES::WN, 0));
            } else {
                addQuietMove(Utils::createMoveInt(fromSq, toSq, PIECES::EMPTY, PIECES::EMPTY, 0));
            }
        } else if (side == SIDE::BLACK) {
            if (Utils::ranksBoard[fromSq] == RANKS::RANK_2) {
                addQuietMove(Utils::createMoveInt(fromSq, toSq, PIECES::EMPTY, PIECES::BQ, 0));
                addQuietMove(Utils::createMoveInt(fromSq, toSq, PIECES::EMPTY, PIECES::BR, 0));
                addQuietMove(Utils::createMoveInt(fromSq, toSq, PIECES::EMPTY, PIECES::BB, 0));
                addQuietMove(Utils::createMoveInt(fromSq, toSq, PIECES::EMPTY, PIECES::BN, 0));
            } else {
                addQuietMove(Utils::createMoveInt(fromSq, toSq, PIECES::EMPTY, PIECES::EMPTY, 0));
            }
        } else {
            assert(false);
        }
    }

    void addPawnCaptureMove(const int side, const int fromSq, const int toSq, const int capture) {
        assert(Utils::isPieceValidOrEmpty(capture));
        assert(Utils::isSqOnBoard(fromSq));
        assert(Utils::isSqOnBoard(toSq));

        if (side == SIDE::WHITE) {
            if (Utils::ranksBoard[fromSq] == RANKS::RANK_7) {
                addCaptureMove(Utils::createMoveInt(fromSq, toSq, capture, PIECES::WQ, 0));
                addCaptureMove(Utils::createMoveInt(fromSq, toSq, capture, PIECES::WR, 0));
                addCaptureMove(Utils::createMoveInt(fromSq, toSq, capture, PIECES::WB, 0));
                addCaptureMove(Utils::createMoveInt(fromSq, toSq, capture, PIECES::WN, 0));
            } else {
                addCaptureMove(Utils::createMoveInt(fromSq, toSq, capture, PIECES::EMPTY, 0));
            }
        } else if (side == SIDE::BLACK) {
            if (Utils::ranksBoard[fromSq] == RANKS::RANK_2) {
                addCaptureMove(Utils::createMoveInt(fromSq, toSq, capture, PIECES::BQ, 0));
                addCaptureMove(Utils::createMoveInt(fromSq, toSq, capture, PIECES::BR, 0));
                addCaptureMove(Utils::createMoveInt(fromSq, toSq, capture, PIECES::BB, 0));
                addCaptureMove(Utils::createMoveInt(fromSq, toSq, capture, PIECES::BN, 0));
            } else {
                addCaptureMove(Utils::createMoveInt(fromSq, toSq, capture, PIECES::EMPTY, 0));
            }
        } else {
            assert(false);
        }
    }

    void print() {
        for (int i = 0; i < count; ++i) {
            Move move = moves[i];
            std::cout << "Move " << (i+1) << ": " << move.str() << ", " << move.score << std::endl;
        }
        std::cout << count << " total moves" << std::endl;
    }
};

#endif // TYPES_H
