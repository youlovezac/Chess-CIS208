// Author: Josh Halstead
#include <math.h>
#include "Board.h"
#include "misc.h"
#include "Move.h"
#include "Rules.h"
#include "Square.h"

const int SQ_ROW_UL = 7;
const int SQ_ROW_LL = 0;
const int SQ_COL_UL = 7;
const int SQ_COL_LL = 0;

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
	
	if (startSq == endSq) {
		validPath = false;
	}

	if (startSq.getRow() < SQ_ROW_LL || startSq.getRow() > SQ_ROW_UL) {
		validPath = false;
	} else if (endSq.getRow() < SQ_COL_LL || endSq.getRow() > SQ_COL_UL) {
		validPath = false;
	}

	switch (m.getStart().getPiece().pieceType) {
	case NOPIECE:
		validPath = false;
		break;
	case PAWN:
		validPath = isValidPawnMove(startSq, endSq);
		break;
	case BISHOP:
		validPath = isValidBishopMove(startSq, endSq);
		break;
	case KNIGHT:
		validPath = isValidKnightMove(startSq, endSq);
		break;
	case ROOK:
		validPath = isValidRookMove(startSq, endSq);
		break;
	case QUEEN:
		validPath = isValidQueenMove(startSq, endSq);
		break;
	case KING:
		validPath = isValidKingMove(startSq, endSq);
		break;
	default:
		validPath = false;
	}
	
	return validPath;
}

bool Rules::isValidPawnMove(Square startSq, Square endSq) {
	int rowDiff = 0, colDiff = 0, startRow = 0, startCol = 0, endRow = 0, endCol = 0;
	bool validPath = true;

	startRow = startSq.getRow();
	startCol = startSq.getCol();
	endRow = endSq.getRow();
	endCol = endSq.getCol();

	rowDiff = abs(startRow - endRow);
	colDiff = abs(startCol - endCol);

	// Can only move forward - therefore need player color
	if (p.playerColor == WHITE) {

		// Can only move forward
		if (endRow < startRow) {
			validPath = false;
		}

		// Can move 1 or 2 spaces if it's the pawn's initial move
		if (startRow == SQ_ROW_LL + 1 && rowDiff > 2) {
			validPath = false;
		}
		
		// Can only move 1 space after the pawn's initial move
		if (startRow > SQ_ROW_LL + 1 && rowDiff != 1) {
			validPath = false;
		}

		// Can move 1 space (left or right) diagonally forward to capture a piece
		if ((startCol != endCol) && 
			colDiff != 1 && 
			endRow - startRow != 1) {
			validPath = false;
		}

	}
	else if (p.playerColor == BLACK) {

		// Can only move forward
		if (endRow > startRow) {
			validPath = false;
		}

		// Can move 1 or 2 spaces if it's the pawn's initial move
		if ((startRow == SQ_ROW_UL - 1) && 
			(rowDiff == 1 || rowDiff == 2)) {
			validPath = false;
		}
		
		// Can only move 1 space after the pawn's initial move
		if (startRow < SQ_ROW_LL - 1 && rowDiff != 1) {
			validPath = false;
		}

		// Can move 1 space (left or right) diagonally forward to capture a piece
		if ((startCol != endCol) && 
		    (startRow - endRow != 1) &&
			(colDiff != 1)) {

			validPath = false;
		}

	} else {
		validPath = false;
	}

	return validPath;	
}

bool Rules::isValidBishopMove(Square startSq, Square endSq) {
	int rowDiff = 0, colDiff = 0;
	
	rowDiff = abs(startSq.getRow() - endSq.getRow());
	colDiff = abs(startSq.getCol() - endSq.getCol());
	
	return (rowDiff == colDiff);
}

bool Rules::isValidKnightMove(Square startSq, Square endSq) {
	int rowDiff = 0, colDiff = 0;
	
	rowDiff = abs(startSq.getRow() - endSq.getRow());
	colDiff = abs(startSq.getCol() - endSq.getCol());

	return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

bool Rules::isValidRookMove(Square startSq, Square endSq) {
	return (startSq.getRow() == endSq.getRow()) || (startSq.getCol() == endSq.getCol());
}

bool Rules::isValidQueenMove(Square startSq, Square endSq) {
	int rowDiff = 0, colDiff = 0;
	
	rowDiff = abs(startSq.getRow() - endSq.getRow());
	colDiff = abs(startSq.getCol() - endSq.getCol());

	return (rowDiff == colDiff) || (startSq.getRow() == endSq.getRow() || startSq.getCol() == endSq.getCol());
}

bool Rules::isValidKingMove(Square startSq, Square endSq) {
	int rowDiff = 0, colDiff = 0;
	
	rowDiff = abs(startSq.getRow() - endSq.getRow());
	colDiff = abs(startSq.getCol() - endSq.getCol());

	return (rowDiff <= 1) && (colDiff <= 1);
}

bool Rules::collision(Move m) {
	bool collisionStatus = false;
	Square startSq;

	startSq = m.getStart();

	switch (startSq.getPiece().pieceType) {
	case NOPIECE:
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

//bool Rules::isStalemate() {
//	return false;
//}

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