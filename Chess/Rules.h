#ifndef RULES_H
#define RULES_H

// Defines the rules class
// Not responsible for storing position on board or for I/O
// It answers questions about what is legal given the board state
// Also, it doesn't make moves but it does check them to see if they are legal


// Author: Josh Halstead

class Rules {
public:

	Rules();
	Rules(Board*);

	// check correct color is being moved
	// check piece has capacity to move to that square
	// check that destination is vacant or occupied by opponent
	// check that it doesn't place you into check
	// check if anything is in the way (e2e4, nothing is on e3 unless it's a knight)
	// check for castling
	// check for en passant
	// Consider checkDiagonal, checkRow, checkColumn methods
	bool isLegal(Move, Player);

	bool isCheck();
	bool isCheckmate();
	bool isDraw();
	// bool isStalemate(moveHistory);
	bool isWhiteWin();
	bool isBlackWin();

private:
	Board* pBoard;

	bool placesKingInCheck(Move);
	
	bool isValidMovementPath(Move);
	bool isValidPawnMove(Square startSq, Square endSq);
	bool isValidBishopMove(Square startSq, Square endSq);
	bool isValidKnightMove(Square startSq, Square endSq);
	bool isValidRookMove(Square startSq, Square endSq);
	bool isValidQueenMove(Square startSq, Square endSq);
	bool isValidKingMove(Square startSq, Square endSq);
	
	bool collision(Move);
	bool diagCollision(Move);
	bool rowCollision(Move);
	bool colCollision(Move);

};

#endif RULES_H