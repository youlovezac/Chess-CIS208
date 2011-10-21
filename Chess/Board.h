#ifndef BOARD_H
#define BOARD_H

// defines class Board which keeps track of the position, 
// but doesn't display it and doesn't know the rules

#include <iostream>
#include "Square.h"


class Board
{

public:
	Board& operator=(const Board& board);
	Board(); // standard constructor
	Board(const Board& board); // copy constructor

	void setSquare(int rank, int file, Piece p);
	Square getSquare(int rank, int file); // returns a specific square

	void setUp();
	void incrementTurn();
	void decrementTurn();

private:
	int turns; // The turn number. I believe we settled on calling the game a draw at a certain number of turns. For now, I'm assuming 200 as that's the highest number I heard in our discussion on turn limits.
	Square chessBoard[8][8];
};

#endif