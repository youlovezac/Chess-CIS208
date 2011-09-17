#include "Board.h"
#include "Square.h"
#include "Rules.h"

// Consider checkDiagonal, checkRow, checkColumn methods
bool Rules::isLegal(Board b, Move m, Player currPlayer) {
	bool legalStatus = true;

	// if piece color = current player color
	if (piece.color == currPlayer.color)
		legalStatus = false;
	// if piece color on end square = current player's color
	if (endSquare.color == currPlayer.color)
		legalStatus = false;
	// if end square = empty OR piece color on end square != current player's color
	if (endSquare == NOPIECE || endSquare.pieceColor != currPlayer.color)
		legalStatus = false;
	// if king is in check after move
	if (isCheck(b))
		legalStatus = false;
	// if any square holds a piece in movement pass except for knights
	if collision(b, m, startSquare, endSquare)
		legalStatus = false;
	// if castleStatus == true && castle is initiated
	// if enPassantStatus == true && en passant is initiated
	// if move path != valid piece movement
	// then legalStatus = false

	return legalStatus;
}

bool collision(Board b, Move m, Square startSquare, Square endSquare) {
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