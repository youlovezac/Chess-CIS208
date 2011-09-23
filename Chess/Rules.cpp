// Author: Josh Halstead
// Author: Josh Halstead
#include "Board.h"
#include "Square.h"
#include "Rules.h"

bool Rules::isLegal(Board b, Move m, Player currPlayer) {
	bool legalStatus = true;

	// if piece color = current player color
	if (piece.color == currPlayer.color)
		legalStatus = false;
	// if end square has a piece that's the same as the current player's color
	if (endSquare.pieceColor == currPlayer.color)
		legalStatus = false;
	// if end square isn't empty
	if (endSquare.piece != NOPIECE)
		legalStatus = false;
	// if king is in check after move
	if (isCheck(b))
		legalStatus = false;
	// if any square holds a piece in movement pass except for knights
	if collision(b, m)
		legalStatus = false;
	// if castleStatus == true && castle is initiated
	// if enPassantStatus == true && en passant is initiated
	// if move path != valid piece movement
	// then legalStatus = false

	return legalStatus;
}

bool collision(Board b, Move m) {
	bool collisionStatus = false;
	Square s;

	s = m.getStartSquare();

	switch (s.getPiece()) {
		case PAWN:
		case KNIGHT:
		case BISHOP:
		case ROOK:
		case QUEEN:
		case KING:
		default:
	}

	return collisionStatus;
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

bool Rules::isStalemate(Board b) {
	return false;
}

bool Rules::isWhiteWin(Board b) {
	return false;
}

bool Rules::isBlackWin(Board b) {
	return false;
}

bool Rules::diagCollision(Board b, Move m) {
	return false;
}

bool Rules::colCollision(Board b, Move m) {
	return false;
}

bool Rules::rowCollision(Board b, Move m) {
	return false;
}