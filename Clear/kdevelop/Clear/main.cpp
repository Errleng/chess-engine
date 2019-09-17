#include <iostream>
#include "tester.h"

int main(int argc, char **argv) {
    std::cout << "Hello World!\n";
    Utils::initUtils();

    Board board;
    
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
    board.parseFen("r3k3/1K6/8/8/8/8/8/8 w q - 0 1");
    board.print();
    
    Tester tester;
    tester.position = board;
    tester.perftTest(6);
    
    return 0;
}
