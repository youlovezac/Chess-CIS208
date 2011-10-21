#ifndef RULES_H
#define RULES_H

// Defines the rules class
// Not responsible for storing position on board or for I/O
// It answers questions about what is legal given the board state
// Also, it doesn't make moves but it does check them to see if they are legal


// Author: Josh Halstead

#include "Move.h"
#include "Board.h"
#include "misc.h"

class Rules {
public:

	Rules();
	Rules(Board*);

	bool isLegal(Move, Player);

	bool isCheck(Square, Player);
    bool isCheck(Board); // TODO
	bool isCheckmate(); // TODO
	bool isDraw();
	// bool isStalemate(moveHistory); // TODO
	bool isWhiteWin(); // TODO
	bool isBlackWin(); // TODO

private:
	Board* pBoard;

	bool placesKingInCheck(Move) ;
	
	bool isValidMovementPath(Move, Player);
	bool isValidPawnMove(Square startSq, Square endSq, Player currPlayer);
	bool isValidBishopMove(Square startSq, Square endSq);
	bool isValidKnightMove(Square startSq, Square endSq);
	bool isValidRookMove(Square startSq, Square endSq);
	bool isValidQueenMove(Square startSq, Square endSq);
	bool isValidKingMove(Square startSq, Square endSq);
	
    bool isOutOfBounds(Square s);

	bool collision(Move);
	bool diagCollision(int startRow, int endRow, int startCol, int endCol);
	bool rowCollision(int row, int startCol, int endCol);
	bool colCollision(int col, int startRow, int endRow);

	bool isThreat(Color pColor, int row, int col, int threatType);
	bool isPawnThreat(Color pColor, int row, int col);
	bool isKnightThreat(Color pColor, int row, int col);

};

#endif
