#include "utils.h"

namespace Utils {
    std::array<int, NUM_SQUARES> sq64to120;
    std::array<int, NUM_POSSIBLE_SQUARES> sq120to64;

    std::array<int, NUM_POSSIBLE_SQUARES> filesBoard;
    std::array<int, NUM_POSSIBLE_SQUARES> ranksBoard;

    std::array<unsigned long long, NUM_SQUARES> setMask;
    std::array<unsigned long long, NUM_SQUARES> clearMask;

    unsigned long long sideKey;
    std::array<unsigned long long, 16> castleKeys;
    std::array<std::array<unsigned long long, NUM_POSSIBLE_SQUARES>, 13> pieceKeys;

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long long> randDistr;

    bool isSqOnBoard(const int square) {
        return filesBoard[square] != SQUARES::OFFBOARD;
    }

    bool isSideValid(const int side) {
        if (side == SIDE::WHITE || side == SIDE::BLACK) {
            return true;
        } else {
            return false;
        }
    }

    bool isFileOrRankValid(const int fileOrRank) {
        if (fileOrRank >= 0 && fileOrRank <= 7) {
            return true;
        } else {
            return false;
        }
    }

    bool isPieceValid(const int piece) {
        if (piece >= PIECES::WP && piece <= PIECES::BK) {
            return true;
        } else {
            return false;
        }
    }

    bool isPieceValidOrEmpty(const int piece) {
        if (piece >= PIECES::EMPTY && piece <= PIECES::BK) {
            return true;
        } else {
            return false;
        }
    }

    int fileRankToSq(const int file, const int rank) {
        return (21 + file) + (rank * 10);
    }

    int createMoveInt(const int fromSq, const int toSq, const int capture, const int promotion, const int flag) {
        return fromSq | (toSq << 7) | (capture << 14) | (promotion << 20) | flag;
    }

    int getFromSq(const int move) {
        return move & 0x7F;
    }

    int getToSq(const int move) {
        return (move >> 7) & 0x7F;
    }

    int getCapture(const int move) {
        return (move >> 14) & 0xF;
    }

    int getPromotion(const int move) {
        return (move >> 20) & 0xF;
    }

    void initSqArrs() {
        for (int i = 0; i < NUM_SQUARES; ++i) {
            sq64to120[i] = 120;
        }

        for (int i = 0; i < NUM_POSSIBLE_SQUARES; ++i) {
            sq120to64[i] = 65;
        }

        int sq64 = 0;
        for (int rank = RANKS::RANK_1; rank <= RANKS::RANK_8; ++rank) {
            for (int file = FILES::FILE_A; file <= FILES::FILE_H; ++file) {
                int sq = fileRankToSq(file, rank);

                assert(isSqOnBoard(sq));

                sq64to120[sq64] = sq;
                sq120to64[sq] = sq64;
                ++sq64;
            }
        }
    }

    void initFilesRanks() {
        for (int i = 0; i < NUM_POSSIBLE_SQUARES; ++i) {
            filesBoard[i] = SQUARES::OFFBOARD;
            ranksBoard[i] = SQUARES::OFFBOARD;
        }

        for (int rank = RANKS::RANK_1; rank <= RANKS::RANK_8; ++rank) {
            for (int file = FILES::FILE_A; file <= FILES::FILE_H; ++file) {
                int sq = fileRankToSq(file, rank);
                filesBoard[sq] = file;
                ranksBoard[sq] = rank;
            }
        }
    }

    void initBitmasks() {
        for (int i = 0; i < NUM_SQUARES; ++i) {
            setMask[i] = 0ULL | (1ULL << i);
            clearMask[i] = ~setMask[i];
        }
    }

    void initHashKeys() {
        sideKey = randDistr(gen);
        for (int i = 0; i < pieceKeys.size(); ++i) {
            for (int j = 0; j < pieceKeys[i].size(); ++j) {
                pieceKeys[i][j] = randDistr(gen);
            }
        }
        for (int i = 0; i < castleKeys.size(); ++i) {
            castleKeys[i] = randDistr(gen);
        }
    }

    void initUtils() {
        initSqArrs();
        initFilesRanks();
        initBitmasks();
        initHashKeys();
    }
}

