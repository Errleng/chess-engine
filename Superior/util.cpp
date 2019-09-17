//
// Created by Recursor on 8/9/2018.
//

#include "util.h"

namespace Superior {

    // Bit utilities

    int firstBit(uint64_t b) {
        return __builtin_ctz(b);
    }

    int lastBit(uint64_t b) {
        return __builtin_clz(b);
    }

    int popBit(uint64_t& b) {
        const int i = firstBit(b);
        b &= b - 1;
        return i;
    }
}
