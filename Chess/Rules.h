#ifndef RULES_H
#define RULES_H

// Defines the rules class
// Not responsible for storing position on board or for I/O
// It answers questions about what is legal given the board state
// Also, it doesn't make moves but it does check them to see if they are legal


// Author: Josh Halstead
class Rules {
public:

	// check correct color is being moved
	// check piece has capacity to move to that square
	// check that destination is vacant or occupied by opponent
	// check that it doesn't place you into check
	// check if anything is in the way (e2e4, nothing is on e3 unless it's a knight)
	// check for castling
	// check for en passant
	// Consider checkDiagonal, checkRow, checkColumn methods

	// Board will be 
	bool isLegal(Board, move);

	bool isCheck(Board);
	bool isCheckmate(Board);
	bool isDraw(Board);
	bool isStalemate(Board, moveHistory);
	bool isWhiteWin(Board);
	bool isBlackWin(Board);
	list legalMoveList(Board);

private:
	bool diagCollision();
	bool rowCollision();
	bool colCollision();

};

#endif RULES_H