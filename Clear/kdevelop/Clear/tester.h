#ifndef TESTER_H
#define TESTER_H

#include "board.h"

class Tester
{
public:
    unsigned long long numLeafNodes;
    Board position;
    
    void perft(const int depth);
    void perftTest(const int depth);
};

#endif // TESTER_H
