// Author: Josh Halstead
#include <math.h>
#include "Board.h"
#include "misc.h"
#include "Move.h"
#include "Rules.h"
#include "Square.h"


Rules::Rules(Board* pointer) {
	pBoard = pointer;
}

bool Rules::isLegal(Move m, Player currPlayer) {
	bool legalStatus = true;
	Square startSq = m.getStart();
	Square endSq = m.getDestination();
	Piece p = startSq.getPiece();

	// Player can't move the other player's color
	if (p.pieceColor != currPlayer.playerColor) {
		legalStatus = false;

	// Can't move onto a square that one of your piece occupies
	} else if ((endSq.getPiece()).pieceColor == currPlayer.playerColor) {
		legalStatus = false;

	// if end square isn't empty
	// only matters if pawn is moving in a non-capture capacity
	// otherwise the piece will simply capture the occupant
	} else if ((endSq.getPiece()).pieceType != NOPIECE) {
		legalStatus = false;

	// Can't place your own King in check
	} else if (this->placesKingInCheck(m)) {
		legalStatus = false;

	// Movement path must match piece's established moving pattern
	} else if (!this->isValidMovementPath(m)) {
		legalStatus = false;

	// Can't move through any pieces that occupy the movement path
	// Unless the piece is a Knight
	} else if (collision(m)) {
		legalStatus = false;
	}


	// if castleStatus == true && castle is initiated
	// if enPassantStatus == true && en passant is initiated

	return legalStatus;
}

bool Rules::placesKingInCheck(Move m){
	// Make a copy of the board and execute the move.
	// Then call isCheck with new Board
	// Need two copies of isCheck maybe
	// 1 to handle ptr to board
	// 1 to handle Board passed as parameter
	Board b = *pBoard;
	b.makeMove(m);
	
	return this->isCheck(b);

}

bool Rules::isValidMovementPath(Move m) {
	int rowDiff = 0, colDiff = 0;
	bool validPath = true;
	Square startSq = m.getStart();
	Square endSq = m.getDestination();

	switch (((m.getStart()).getPiece()).pieceType) {
	case NOPIECE:
		validPath = false;
		break;
	case PAWN:
		// Can only move forward - therefore need player color
		// Can only move 1 space after being moved from its initial position
		// On its initial move it can move 1 or 2 spaces
		// On capturing a piece it can move diagonally forward one space
		break;
	case BISHOP:
		rowDiff = abs(startSq.getRow() - endSq.getRow());
		colDiff = abs(startSq.getCol() - endSq.getCol());

		if (!(rowDiff == colDiff)) {
			validPath = false;
		}

		break;

	case KNIGHT:
		rowDiff = abs(startSq.getRow() - endSq.getRow());
		colDiff = abs(startSq.getCol() - endSq.getCol());

		if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))) {
			validPath = false;
		}

		break;

	case ROOK:
		if (!(startSq.getRow() == endSq.getRow() ||
			  startSq.getCol() == endSq.getCol())) {
			validPath = false;
		}

		break;

	case QUEEN:

		rowDiff = abs(startSq.getRow() - endSq.getRow());
		colDiff = abs(startSq.getCol() - endSq.getCol());

		if (!(rowDiff == colDiff) || !(startSq.getRow() == endSq.getRow() || 
									startSq.getCol() == endSq.getCol())) {
			validPath = false;
		}

		break;

	case KING:
		rowDiff = abs(startSq.getRow() - endSq.getRow());
		colDiff = abs(startSq.getCol() - endSq.getCol());

		if (!(rowDiff <= 1 && colDiff <= 1)) {
			validPath = false;
		}

		break;

	default:
		validPath = false;
	}
	
	return false;
}

bool Rules::collision(Move m) {
	bool collisionStatus = false;
	Square s;

	s = m.getStart();

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

bool Rules::isCheck() {
	return false;
}

bool Rules::isCheckmate() {
	return false;
}

bool Rules::isDraw() {
	return false;
}

bool Rules::isStalemate() {
	return false;
}

bool Rules::isWhiteWin() {
	return false;
}

bool Rules::isBlackWin() {
	return false;
}

bool Rules::diagCollision(Move m) {
	return false;
}

bool Rules::colCollision(Move m) {
	return false;
}

bool Rules::rowCollision(Move m) {
	return false;
}