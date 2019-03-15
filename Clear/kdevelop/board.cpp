#include "board.h"

unsigned long long Board::genPosKey() {
    unsigned long long finalKey = 0;

    for (int sq = 0; sq < NUM_POSSIBLE_SQUARES; ++sq) {
        int piece = pieces[sq];
        if (piece != SQUARES::NONE && piece != PIECES::EMPTY && piece != SQUARES::OFFBOARD) {
            assert(piece >= PIECES::WP && piece <= PIECES::BK);
            finalKey ^= Utils::pieceKeys[piece][sq];
        }
    }
    
    if (side == SIDE::WHITE) {
        finalKey ^= Utils::sideKey;
    }

    if (enPassant != SQUARES::NONE) {
        assert(enPassant >= 0 && enPassant < NUM_POSSIBLE_SQUARES);
        finalKey ^= Utils::pieceKeys[PIECES::EMPTY][enPassant];
    }

    assert(castlePerm >= 0 && castlePerm <= 15);
    finalKey ^= Utils::castleKeys[castlePerm];

    return finalKey;
}

bool Board::check() {
    std::array<int, NUM_PIECES> chkPieceNum = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::array<int, NUM_PIECE_TYPES> chkBigPieces = {0, 0};
    std::array<int, NUM_PIECE_TYPES> chkMajorPieces = {0, 0};
    std::array<int, NUM_PIECE_TYPES> chkMinorPieces = {0, 0};
    std::array<int, NUM_MATERIAL> chkMaterial = {0, 0};
    std::array<Bitboard, NUM_BITBOARD_PAWNS> chkPawns = {Bitboard(), Bitboard(), Bitboard()};

    chkPawns[SIDE::WHITE] = pawns[SIDE::WHITE];
    chkPawns[SIDE::BLACK] = pawns[SIDE::BLACK];
    chkPawns[SIDE::BOTH] = pawns[SIDE::BOTH];

    for (int piece = PIECES::WP; piece <= PIECES::BK; ++piece) {
        for (int num_piece = 0; num_piece < pieceNums[piece]; ++num_piece) {
            int sq120 = pieceList[piece][num_piece];
            assert(pieces[sq120] == piece);
        }
    }

    for (int sq64 = 0; sq64 < NUM_SQUARES; ++sq64) {
        int sq120 = Utils::sq64to120[sq64];
        int piece = pieces[sq120];
        int colour = PIECE_COLOUR[piece];
        
        ++chkPieceNum[piece];

        if (IS_PIECE_BIG[piece]) {
            ++chkBigPieces[colour];
        }
        if (IS_PIECE_MAJOR[piece]) {
            ++chkMajorPieces[colour];
        }
        if (IS_PIECE_MINOR[piece]) {
            ++chkMinorPieces[colour];
        }
        
        chkMaterial[colour] += PIECE_VALUES[piece];
    }

    for (int piece = PIECES::WP; piece <= PIECES::BK; ++piece) {
        assert(chkPieceNum[piece] == pieceNums[piece]);
    }

    int numPawns = chkPawns[SIDE::WHITE].getBitCount();
    assert(numPawns == pieceNums[PIECES::WP]);
    numPawns = chkPawns[SIDE::BLACK].getBitCount();
    assert(numPawns == pieceNums[PIECES::BP]);
    numPawns = chkPawns[SIDE::BOTH].getBitCount();
    assert(numPawns == pieceNums[PIECES::WP] + pieceNums[PIECES::BP]);

    while (!chkPawns[SIDE::WHITE].isEmpty()) {
        int sq64 = chkPawns[SIDE::WHITE].popBit();
        assert(pieces[Utils::sq64to120[sq64]] == PIECES::WP);
    }

    while (!chkPawns[SIDE::BLACK].isEmpty()) {
        int sq64 = chkPawns[SIDE::BLACK].popBit();
        assert(pieces[Utils::sq64to120[sq64]] == PIECES::BP);
    }

    while (!chkPawns[SIDE::BOTH].isEmpty()) {
        int sq64 = chkPawns[SIDE::BOTH].popBit();
        int piece = pieces[Utils::sq64to120[sq64]];
        assert(piece == PIECES::WP || piece == PIECES::BP);
    }

    assert(chkBigPieces[SIDE::WHITE] == bigPieces[SIDE::WHITE] && chkBigPieces[SIDE::BLACK] == bigPieces[SIDE::BLACK]);
    assert(chkMajorPieces[SIDE::WHITE] == majorPieces[SIDE::WHITE] && chkMajorPieces[SIDE::BLACK] == majorPieces[SIDE::BLACK]);
    assert(chkMinorPieces[SIDE::WHITE] == minorPieces[SIDE::WHITE] && chkMinorPieces[SIDE::BLACK] == minorPieces[SIDE::BLACK]);
    assert(chkMaterial[SIDE::WHITE] == material[SIDE::WHITE] && chkMaterial[SIDE::BLACK] == material[SIDE::BLACK]);

    assert(side == SIDE::WHITE || side == SIDE::BLACK);
    assert(genPosKey() == posKey);

    assert(enPassant == SQUARES::NONE || (Utils::ranksBoard[enPassant] == RANKS::RANK_6 && side == SIDE::WHITE) || (Utils::ranksBoard[enPassant] == RANKS::RANK_3 && side == SIDE::BLACK));
    
    assert(pieces[kingSq[SIDE::WHITE]] == PIECES::WK);
    assert(pieces[kingSq[SIDE::BLACK]] == PIECES::BK);

    return true;
}

void Board::updateMaterial() {
    for (int i = 0; i < NUM_POSSIBLE_SQUARES; ++i) {
        int sq=  i;
        int piece = pieces[i];
        if (piece != SQUARES::OFFBOARD && piece != PIECES::EMPTY) {
            int colour = PIECE_COLOUR[piece];

            if (IS_PIECE_BIG[piece]) {
                ++bigPieces[colour];
            }
            if (IS_PIECE_MAJOR[piece]) {
                ++majorPieces[colour];
            }
            if (IS_PIECE_MINOR[piece]) {
                ++minorPieces[colour];
            }

            material[colour] += PIECE_VALUES[piece];
            pieceList[piece][pieceNums[piece]] = sq;
            ++pieceNums[piece];

            if (piece == PIECES::WK) {
                kingSq[SIDE::WHITE] = sq;
            } else if (piece == PIECES::BK) {
                kingSq[SIDE::BLACK] = sq;
            }
            
            if (piece == PIECES::WP) {
                int sq64 = Utils::sq120to64[sq];
                pawns[SIDE::WHITE].setBit(sq64);
                pawns[SIDE::BOTH].setBit(sq64);
            } else if (piece == PIECES::BP) {
                int sq64 = Utils::sq120to64[sq];
                pawns[SIDE::BLACK].setBit(sq64);
                pawns[SIDE::BOTH].setBit(sq64);
            }
        }
    }
}


void Board::generateAllMoves() {
    assert(check());

    moveList.count = 0;

    if (side == SIDE::WHITE) {
        for (int pieceNum = 0; pieceNum < pieceNums[PIECES::WP]; ++pieceNum) {
            int sq = pieceList[PIECES::WP][pieceNum];
            assert(Utils::isSqOnBoard(sq));

            int toSq = sq + 10;
            if (pieces[toSq] == PIECES::EMPTY) {
                moveList.addPawnMove(SIDE::WHITE, sq, toSq);
                if (Utils::ranksBoard[sq] == RANKS::RANK_2) {
                    int jumpSq = sq + 20;
                    if (pieces[jumpSq] == EMPTY) {
                        moveList.addQuietMove(Utils::createMoveInt(sq, jumpSq, PIECES::EMPTY, PIECES::EMPTY, FLAG_PAWN_START));
                    }
                }
            }

            toSq = sq + 9;
            if (Utils::isSqOnBoard(toSq) && (PIECE_COLOUR[pieces[toSq]] == SIDE::BLACK)) {
                moveList.addPawnCaptureMove(SIDE::WHITE, sq, toSq, pieces[toSq]);
            }
            if (toSq == enPassant) {
                moveList.addCaptureMove(Utils::createMoveInt(sq, toSq, PIECES::EMPTY, PIECES::EMPTY, FLAG_EN_PASSANT));
            }

            toSq = sq + 11;
            if (Utils::isSqOnBoard(toSq) && (PIECE_COLOUR[pieces[toSq]] == SIDE::BLACK)) {
                moveList.addPawnCaptureMove(SIDE::WHITE, sq, toSq, pieces[toSq]);
            }
            if (toSq == enPassant) {
                moveList.addCaptureMove(Utils::createMoveInt(sq, toSq, PIECES::EMPTY, PIECES::EMPTY, FLAG_EN_PASSANT));
            }

            if (castlePerm & CASTLING::WKCA) {
                if ((pieces[SQUARES::F1] == PIECES::EMPTY) && (pieces[SQUARES::G1] == PIECES::EMPTY)) {
                    if (!isSqAttacked(SQUARES::E1, SIDE::BLACK) && !isSqAttacked(SQUARES::F1, SIDE::BLACK)) {
                        moveList.addQuietMove(Utils::createMoveInt(SQUARES::E1, SQUARES::G1, PIECES::EMPTY, PIECES::EMPTY, FLAG_CASTLE));
                    }
                }
            }

            if (castlePerm & CASTLING::WQCA) {
                if ((pieces[SQUARES::D1] == PIECES::EMPTY) && (pieces[SQUARES::C1] == PIECES::EMPTY)) {
                    if (!isSqAttacked(SQUARES::E1, SIDE::BLACK) && !isSqAttacked(SQUARES::D1, SIDE::BLACK)) {
                        moveList.addQuietMove(Utils::createMoveInt(SQUARES::E1, SQUARES::C1, PIECES::EMPTY, PIECES::EMPTY, FLAG_CASTLE));
                    }
                }
            }
        }
    } else if (side == SIDE::BLACK) {
        for (int pieceNum = 0; pieceNum < pieceNums[PIECES::BP]; ++pieceNum) {
            int sq = pieceList[PIECES::BP][pieceNum];
            assert(Utils::isSqOnBoard(sq));

            int toSq = sq - 10;
            if (pieces[toSq] == PIECES::EMPTY) {
                moveList.addPawnMove(SIDE::WHITE, sq, toSq);
                if (Utils::ranksBoard[sq] == RANKS::RANK_7) {
                    int jumpSq = sq - 20;
                    if (pieces[jumpSq] == EMPTY) {
                        moveList.addQuietMove(Utils::createMoveInt(sq, jumpSq, PIECES::EMPTY, PIECES::EMPTY, FLAG_PAWN_START));
                    }
                }
            }

            toSq = sq - 9;
            if (Utils::isSqOnBoard(toSq) && (PIECE_COLOUR[pieces[toSq]] == SIDE::WHITE)) {
                moveList.addPawnCaptureMove(SIDE::WHITE, sq, toSq, pieces[toSq]);
            }
            if (toSq == enPassant) {
                moveList.addCaptureMove(Utils::createMoveInt(sq, toSq, PIECES::EMPTY, PIECES::EMPTY, FLAG_EN_PASSANT));
            }

            toSq = sq - 11;
            if (Utils::isSqOnBoard(toSq) && (PIECE_COLOUR[pieces[toSq]] == SIDE::WHITE)) {
                moveList.addPawnCaptureMove(SIDE::WHITE, sq, toSq, pieces[toSq]);
            }
            if (toSq == enPassant) {
                moveList.addCaptureMove(Utils::createMoveInt(sq, toSq, PIECES::EMPTY, PIECES::EMPTY, FLAG_EN_PASSANT));
            }

            if (castlePerm & CASTLING::BKCA) {
                if ((pieces[SQUARES::F8] == PIECES::EMPTY) && (pieces[SQUARES::G8] == PIECES::EMPTY)) {
                    if (!isSqAttacked(SQUARES::E8, SIDE::WHITE) && !isSqAttacked(SQUARES::F8, SIDE::WHITE)) {
                        moveList.addQuietMove(Utils::createMoveInt(SQUARES::E8, SQUARES::G8, PIECES::EMPTY, PIECES::EMPTY, FLAG_CASTLE));
                    }
                }
            }

            if (castlePerm & CASTLING::BQCA) {
                if ((pieces[SQUARES::D8] == PIECES::EMPTY) && (pieces[SQUARES::C8] == PIECES::EMPTY)) {
                    if (!isSqAttacked(SQUARES::E8, SIDE::WHITE) && !isSqAttacked(SQUARES::D8, SIDE::WHITE)) {
                        moveList.addQuietMove(Utils::createMoveInt(SQUARES::E8, SQUARES::C8, PIECES::EMPTY, PIECES::EMPTY, FLAG_CASTLE));
                    }
                }
            }
        }
    } else {
        assert(false);
    }

    int opposingSide = side ^ 1;
    int pieceIndex = LOOP_SLIDER_INDEX[side];
    int piece = LOOP_SLIDERS[pieceIndex++];
    while (piece != 0) {
        assert(Utils::isPieceValid(piece));

        for (int pieceNum = 0; pieceNum < pieceNums[piece]; ++pieceNum) {
            int sq = pieceList[piece][pieceNum];
            assert(Utils::isSqOnBoard(sq));

            for (int i = 0; i < NUM_DIRS[piece]; ++i) {
                int dir = PIECE_DIRS[piece][i];
                int toSq = sq + dir;
                while (Utils::isSqOnBoard(toSq)) {
                    if (pieces[toSq] != PIECES::EMPTY) {
                        if (PIECE_COLOUR[pieces[toSq]] == opposingSide) {
                            moveList.addCaptureMove(Utils::createMoveInt(sq, toSq, pieces[toSq], PIECES::EMPTY, 0));
                        }
                        break;
                    }
                    moveList.addQuietMove(Utils::createMoveInt(sq, toSq, PIECES::EMPTY, PIECES::EMPTY, 0));
                    toSq += dir;
                }
            }
        }

        piece = LOOP_SLIDERS[pieceIndex++];
    }

    pieceIndex = LOOP_NON_SLIDER_INDEX[side];
    piece = LOOP_SLIDERS[pieceIndex++];
    while (piece != 0) {
        assert(Utils::isPieceValid(piece));

        for (int pieceNum = 0; pieceNum < pieceNums[piece]; ++pieceNum) {
            int sq = pieceList[piece][pieceNum];
            assert(Utils::isSqOnBoard(sq));

            for (int i = 0; i < NUM_DIRS[piece]; ++i) {
                int dir = PIECE_DIRS[piece][i];
                int toSq = sq + dir;

                if (Utils::isSqOnBoard(toSq)) {
                    if (pieces[toSq] != PIECES::EMPTY) {
                        if (PIECE_COLOUR[pieces[toSq]] == opposingSide) {
                            moveList.addCaptureMove(Utils::createMoveInt(sq, toSq, pieces[toSq], PIECES::EMPTY, 0));
                        }
                        continue;
                    }
                    moveList.addQuietMove(Utils::createMoveInt(sq, toSq, PIECES::EMPTY, PIECES::EMPTY, 0));
                }
            }
        }

        piece = LOOP_NON_SLIDERS[pieceIndex++];
    }
}


bool Board::parseFen(const std::string& fen) {
    assert(!fen.empty());

    reset();

    int rank = RANKS::RANK_8;
    int file = FILES::FILE_A;
    int i = 0;

    while (i < fen.length() && rank >= RANKS::RANK_1) {
        int piece = 0;
        int count = 1;

        switch (fen[i]) {
            case 'p': piece = PIECES::BP; break;
            case 'r': piece = PIECES::BR; break;
            case 'n': piece = PIECES::BN; break;
            case 'b': piece = PIECES::BB; break;
            case 'k': piece = PIECES::BK; break;
            case 'q': piece = PIECES::BQ; break;
            case 'P': piece = PIECES::WP; break;
            case 'R': piece = PIECES::WR; break;
            case 'N': piece = PIECES::WN; break;
            case 'B': piece = PIECES::WB; break;
            case 'K': piece = PIECES::WK; break;
            case 'Q': piece = PIECES::WQ; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = PIECES::EMPTY;
                count = fen[i] - '0';
                break;

            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                ++i;
                continue;              

            default:
                std::cout << "FEN error" << std::endl;;
                return false;
        }
        for (int j = 0; j < count; ++j) {
            int sq64 = rank * 8 + file;
            int sq120 = Utils::sq64to120[sq64];
            if (piece != PIECES::EMPTY) {
                pieces[sq120] = piece;
            }
            ++file;
        }
        ++i;
    }

    assert(fen[i] == 'w' || fen[i] == 'b');

    if (fen[i] == 'w') {
        side = SIDE::WHITE;
    } else {
        side = SIDE::BLACK;
    }

    i += 2;

    for (int j = 0; j < 4; ++j) {
        if (fen[i] == ' ') {
            break;
        }
        switch(fen[i]) {
            case 'K':
                castlePerm |= CASTLING::WKCA;
                break;
            case 'Q':
                castlePerm |= CASTLING::WQCA;
                break;
            case 'k':
                castlePerm |= CASTLING::BKCA;
                break;
            case 'q':
                castlePerm |= CASTLING::BQCA;
                break;
            default:
                break;
        }
        ++i;
    }
    ++i;
    
    assert(castlePerm >= 0 && castlePerm <= 15);

    if (fen[i] != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        assert(file >= FILES::FILE_A && file <= FILES::FILE_H);
        assert(file >= RANKS::RANK_1 && rank <= RANKS::RANK_8);

        enPassant = Utils::fileRankToSq(file, rank);
    }

    posKey = genPosKey();
    updateMaterial();

    return true;
}

bool Board::isSqAttacked(const int square, const int sideToCheck) {
    assert(Utils::isSqOnBoard(square));
    assert(Utils::isSideValid(sideToCheck));
    assert(check());

    if (sideToCheck == SIDE::WHITE) {
        if (pieces[square - 11] == PIECES::WP || pieces[square - 9] == PIECES::WP) {
            return true;
        }
    } else if (sideToCheck == SIDE::BLACK) {
        if (pieces[square + 11] == PIECES::BP || pieces[square + 9] == PIECES::BP) {
            return true;
        }
    } else {
        assert(false);
    }

    for (int i = 0; i < KNIGHT_DIRECTIONS.size(); ++i) {
        int piece = pieces[square + KNIGHT_DIRECTIONS[i]];
        if (IS_KNIGHT[piece] && PIECE_COLOUR[piece] == sideToCheck) {
            return true;
        }
    }

    for (int i = 0; i < ROOK_DIRECTIONS.size(); ++i) {
        int dir = ROOK_DIRECTIONS[i];
        int attackSq = square + dir;
        int piece = pieces[attackSq];

        while (piece != SQUARES::OFFBOARD) {
            if (piece != PIECES::EMPTY) {
                if (IS_ROOK_QUEEN[piece] && PIECE_COLOUR[piece] == sideToCheck) {
                    return true;
                }
                break;
            }
            attackSq += dir;
            piece = pieces[attackSq];
        }
    }

    for (int i = 0; i < BISHOP_DIRECTIONS.size(); ++i) {
        int dir = BISHOP_DIRECTIONS[i];
        int attackSq = square + dir;
        int piece = pieces[attackSq];

        while (piece != SQUARES::OFFBOARD) {
            if (piece != PIECES::EMPTY) {
                if (IS_BISHOP_QUEEN[piece] && PIECE_COLOUR[piece] == sideToCheck) {
                    return true;
                }
                break;
            }
            attackSq += dir;
            piece = pieces[attackSq];
        }
    }

    for (int i = 0; i < KING_DIRECTIONS.size(); ++i) {
        int piece = pieces[square + KING_DIRECTIONS[i]];
        if (IS_KING[piece] && PIECE_COLOUR[piece] == sideToCheck) {
            return true;
        }
    }
    
    return false;
}

void Board::reset() {
    for (int i = 0; i < NUM_POSSIBLE_SQUARES; ++i) {
        pieces[i] = SQUARES::OFFBOARD;
    }

    for (int i = 0; i < NUM_SQUARES; ++i) {
        pieces[Utils::sq64to120[i]] = PIECES::EMPTY;
    }

    for (int i = 0; i < 2; ++i) {
        bigPieces[i] = 0;
        majorPieces[i] = 0;
        minorPieces[i] = 0;
        material[i] = 0;
    }

    for (int i = 0; i < 3; ++i) {
        pawns[i].value = 0ULL;
    }

    for (int i = 0; i < pieceNums.size(); ++i) {
        pieceNums[i] = 0;
    }

    kingSq[SIDE::WHITE] = SQUARES::NONE;
    kingSq[SIDE::BLACK] = SQUARES::NONE;
    side = SIDE::BOTH;
    enPassant = SQUARES::NONE;
    fiftyMove = 0;
    ply = 0;
    histPly = 0;
    castlePerm = 0;
    posKey = 0ULL;
}

void Board::print() {
    for (int rank = RANKS::RANK_8; rank >= RANKS::RANK_1; --rank) {
        std::cout << (rank+1);
        for (int file = FILES::FILE_A; file <= FILES::FILE_H; ++file) {
            int sq = Utils::fileRankToSq(file, rank);
            int piece = pieces[sq];
            std::cout << std::setw(3) << (PIECE_CHAR[piece]);
        }
        std::cout << std::endl;
    }
    
    std::cout << " ";
    for (int file = FILES::FILE_A; file <= FILES::FILE_H; ++file) {
        std::cout << std::setw(3) << static_cast<char>('a' + file);
    }
    std::cout << std::endl;

    std::cout << "Side: " << SIDE_CHAR[side] << std::endl;
    std::cout << "En passant: " << enPassant << std::endl;
    std::cout << "Castle: " << (castlePerm & CASTLING::WKCA ? 'K' : '-') << (castlePerm & CASTLING::WQCA ? 'Q' : '-') << (castlePerm & CASTLING::BKCA ? 'k' : '-') << (castlePerm & CASTLING::BQCA ? 'q' : '-') << std::endl;
    std::cout << "Position key: " << posKey << std::endl;
}

