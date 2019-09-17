#include <iostream>
#include "utils.h"
#include "board.h"

#define NDEBUG // disable assert

int main() {
    std::cout << "Hello World!\n";
    Utils::initUtils();

    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Board board;
    board.parseFen(fen);
    board.print();
    board.check();

    board.generateAllMoves();
    board.moveList.print();
}

