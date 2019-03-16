#include "tester.h"

void Tester::perft(const int depth) {
    assert(position.check());
    
    if (depth == 0) {
        ++numLeafNodes;
    } else {
        position.genAllMoves();
        MoveList moveList = position.moveList;
        for (int i = 0; i < moveList.count; ++i) {
            if (!position.makeMove(moveList.moves[i].move)) {
                continue;
            }
            perft(depth - 1);
            position.undoMove();
        }
    }
}

void Tester::perftTest(const int depth) {
    assert(position.check());
    numLeafNodes = 0;
    
    std::cout << "Testing to depth " << depth << std::endl;
    position.print();
    
    position.genAllMoves();
    MoveList moveList = position.moveList;
    
    for (int i = 0; i < moveList.count; ++i) {
        Move move = moveList.moves[i];
        if (!position.makeMove(move.move)) {
            continue;
        }
        
        unsigned long long totalNodes = numLeafNodes;
        perft(depth - 1);
        position.undoMove();
        
        unsigned long long oldNodes = numLeafNodes - totalNodes;
        std::cout << "Move " << (i+1) << ": " << move.str() << " " << oldNodes << std::endl;
    }
    std::cout << numLeafNodes << " leaf nodes" << std::endl;
}
