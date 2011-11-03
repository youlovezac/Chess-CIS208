#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Square.h"

class Board {
public:
	Board& operator=(const Board& board);
	Board();
	Board(const Board& board);
	void setSquare(int rank, int file, Piece p);
	Square getSquare(int rank, int file);
	void incrementTurn();
	void decrementTurn();
private:
	int turns;
	Square chessBoard[8][8];
};

#endif
