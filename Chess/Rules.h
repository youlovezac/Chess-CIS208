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
	bool isLegal(Move, Player) const;

	bool isCheck(Square king) const;
    bool isCheck(Board b) const;
	bool isCheckmate() const;
	bool isDraw() const;
	// bool isStalemate(moveHistory);
	bool isWhiteWin() const;
	bool isBlackWin() const;

private:
	Board* pBoard;

	bool placesKingInCheck(Move) const;
	
	bool isValidMovementPath(Move, Player) const;
	bool isValidPawnMove(Square startSq, Square endSq, Player currPlayer) const;
	bool isValidBishopMove(Square startSq, Square endSq) const;
	bool isValidKnightMove(Square startSq, Square endSq) const;
	bool isValidRookMove(Square startSq, Square endSq) const;
	bool isValidQueenMove(Square startSq, Square endSq) const;
	bool isValidKingMove(Square startSq, Square endSq) const;
	
    bool isOutOfBounds(Square s) const;

	bool collision(Move) const;
	bool diagCollision(int startRow, int endRow, int startCol, int endCol) const;
	bool rowCollision(int row, int startCol, int endCol) const;
	bool colCollision(int col, int startRow, int endRow) const;

};

#endif RULES_H