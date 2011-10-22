#ifndef RULES_H
#define RULES_H

#include "Move.h"
#include "Board.h"

#define DIAG 0
#define ROW -1
#define COL 2

class Rules {
public:
	Rules();
	Rules(Board*);
	bool isLegal(Move, Color);
	bool isCheck(Square, Color);
private:
	Board* pBoard;
	bool placesKingInCheck(Move);
	bool isValidMovementPath(Move, Color);
	bool isValidPawnMove(Square startSq, Square endSq, Color playerColor);
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
