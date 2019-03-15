CXX = clang++
CXXFLAGS = -std=c++17 -Wall -g

clear: main.o utils.o board.o bitboard.o
	${CXX} ${CXXFLAGS} -o clear main.o utils.o bitboard.o board.o
utils.o: utils.h constants.h
board.o: board.h types.h bitboard.h
bitboard.o: utils.h
