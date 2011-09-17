#include "Board.h"
#include "Square.h"
#include "Rules.h"

// check correct color is being moved
// check piece has capacity to move to that square
// check that destination is vacant or occupied by opponent
// check that it doesn't place you into check
// check if anything is in the way (e2e4, nothing is on e3 unless it's a knight)
// check for castling
// check for en passant
// Consider checkDiagonal, checkRow, checkColumn methods
bool Rules::isLegal(Board b, Move m) {
	return false;
}

bool Rules::isCheck(Board b) {
	return false;
}

bool Rules::isCheckmate(Board b) {
	return false;
}

bool Rules::isDraw(Board b) {
	return false;
}

bool Rules::isStalemate(Board b, MoveHistory mh) {
	return false;
}

bool Rules::isWhiteWin(Board b) {
	return false;
}

bool Rules::isBlackWin(Board b) {
	return false;
}

MoveList Rules::legalMoveList(Board b) {
}

bool Rules::diagCollision(Move m, Board b) {
	return false;
}

bool Rules::colCollision(Move m, Board b) {
	return false;
}

bool Rules::rowCollision(Move m, Board b) {
	return false;
}