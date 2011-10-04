// Author: Josh Halstead
#include <math.h>
#include "Board.h"
#include "misc.h"
#include "Move.h"
#include "Rules.h"
#include "Square.h"

// We're undecided on what format to store the coordinates for each square in the Square class.
//		The choices are 0-based (0-7) and 1-based (1-8).
// 
// The Board is 0-based but the user will enter 1-based notation. Decisions, decisions...
// In the mean time these are here to ease the transition (if one occurs) from 0-based to 1-based
// in my code.
const int SQ_ROW_UL = 7; // Row Upper Limit
const int SQ_ROW_LL = 0; // Row Lower Limit
const int SQ_COL_UL = 7; // Column Upper Limit
const int SQ_COL_LL = 0; // Column Lower Limit

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
	} else if ((endSq.getPiece().pieceColor == currPlayer.playerColor) {
		legalStatus = false;

	// if end square isn't empty only matters if pawn is moving in a non-capture capacity
	// otherwise the piece will simply capture the occupant
	} else if (endSq.getPiece().pieceType != NOPIECE) {
		legalStatus = false;

	// Can't place your own King in check
	} else if (this->placesKingInCheck(m)) {
		legalStatus = false;

	// Movement path must match piece's established moving pattern
	} else if (!(this->isValidMovementPath(m, currPlayer))) {
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

bool Rules::isValidMovementPath(Move m, Player currPlayer) {
	bool validPath = true;
	
	Square startSq = m.getStart();
	Square endSq = m.getDestination();

	// A move must consist of at least two different squares
	// Otherwise the player can just pass their turn by entering
	// the same square for start and end squares.
	validPath = (startSq != endSq);

	// The start and end squares must be within the confines of the board
    validPath = !(isOutOfBounds(startSq) || isOutOfBounds(endSq));

	switch (m.getStart().getPiece().pieceType) {
	case PAWN:
		validPath = isValidPawnMove(startSq, endSq, currPlayer);
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

bool isOutOfBounds(Square s) {
    return (s.getRow() < SQ_ROW_LL || s.getRow() > SQ_ROW_UL ||
           s.getCol() < SQ_COL_LL || s.getCol() > SQ_COL_UL); 
}

bool Rules::isValidPawnMove(Square startSq, Square endSq, Player currPlayer) {
	int absRowDiff = 0, absColDiff = 0;

	int startRow = 0, endRow = 0;
	int startCol = 0, endCol = 0;

	int whitePawnStartingRow = SQ_ROW_LL + 1;
	int blackPawnStartingRow = SQ_ROW_UL - 1;

	bool validPath = true;

	startRow = startSq.getRow();
	endRow = endSq.getRow();

	startCol = startSq.getCol();
	endCol = endSq.getCol();

	absRowDiff = abs(endRow - startRow);
	absColDiff = abs(endCol - startCol);


	// Need current player's color since they move in opposing directions
	// White moves forward from Row 1 to Row 8
	if (currPlayer.playerColor == WHITE) {

		// Can't exist on White's "back row"
		if (startRow < whitePawnStartingRow) {
			validPath = false;

		// Can only move forward
        } else if (endRow < startRow) {
			validPath = false;

		// Can move 1 or 2 spaces if it's the pawn's initial move
		// and only 1 space if it's NOT the INTIAL move.
		//		Take advantage of the fact that a pawn can only exist 
		//		on its starting row if it hasn't previously moved
        } else if (!(startRow == whitePawnStartingRow && absRowDiff == 2) &&
			!(startRow >= whitePawnStartingRow && absRowDiff == 1)) {
			validPath = false;
		
		// Can move 1 space diagonally forward (left or right) to capture a piece
        } else if (startCol == endCol || absColDiff != 1 || endRow - startRow != 1) {
			validPath = false;
		}

	}
	// Black moves forward from Row 8 to Row 1
	else if (currPlayer.playerColor == BLACK) {

		// Can't exist on Black's "back row"
		if (startRow > blackPawnStartingRow) {
			validPath = false;

		// Can only move forward
		} else if (endRow > startRow) {
			validPath = false;

		// Can move 1 or 2 spaces if it's the pawn's initial move
		// and only 1 space if it's NOT the INTIAL move.
		//		Take advantage of the fact that a pawn can only exist 
		//		on its starting row if it hasn't previously moved
		} else if (!(startRow == blackPawnStartingRow && absRowDiff == 2) &&
				  !(startRow <= blackPawnStartingRow && absRowDiff == 1)) {
			validPath = false;
		
		// Can move 1 space diagonally forward (left or right) to capture a piece
		} else if (startCol == endCol || absColDiff != 1 || startRow - endRow != 1) {
			validPath = false;
		}

	} else {
		validPath = false;
	}

	return validPath;	
}

bool Rules::isValidBishopMove(Square startSq, Square endSq) {
	int absRowDiff = 0, absColDiff = 0;
	
	absRowDiff = abs(endSq.getRow() - startSq.getRow());
	absColDiff = abs(endSq.getCol() - startSq.getCol());
	
	return (absRowDiff == absColDiff);
}

bool Rules::isValidKnightMove(Square startSq, Square endSq) {
	int absRowDiff = 0, absColDiff = 0;
	
	absRowDiff = abs(endSq.getRow() - startSq.getRow());
	absColDiff = abs(endSq.getCol() - startSq.getCol());

	return (absRowDiff == 2 && absColDiff == 1) || (absRowDiff == 1 && absColDiff == 2);
}

bool Rules::isValidRookMove(Square startSq, Square endSq) {
	return (startSq.getRow() == endSq.getRow()) || (startSq.getCol() == endSq.getCol());
}

bool Rules::isValidQueenMove(Square startSq, Square endSq) {
	int absRowDiff = 0, absColDiff = 0;
	
	absRowDiff = abs(endSq.getRow() - startSq.getRow());
	absColDiff = abs(endSq.getCol() - startSq.getCol());

	return (absRowDiff == absColDiff) || (startSq.getRow() == endSq.getRow() || startSq.getCol() == endSq.getCol());
}

bool Rules::isValidKingMove(Square startSq, Square endSq) {
	int absRowDiff = 0, absColDiff = 0;
	
	absRowDiff = abs(endSq.getRow() - startSq.getRow());
	absColDiff = abs(endSq.getCol() - startSq.getCol());

	return (absRowDiff <= 1) && (absColDiff <= 1);
}

bool Rules::collision(Move m) {
    int rowDiff = 0, colDiff = 0;
    int absRowDiff = 0, absColDiff = 0;
    int startRow = 0, startCol = 0;
    int endRow = 0, endCol = 0;
	bool collisionStatus = false;

	Square startSq, endSq;

	startSq = m.getStart();
    endSq = m.getDestination();

    startRow = startSq.getRow();
    startCol = startSq.getCol();
    endRow = endSq.getRow();
    endCol = endSq.getCol();

    rowDiff = endRow - startRow;
    colDiff = endCol - startCol;
    absRowDiff = abs(rowDiff);
    absColDiff = abs(colDiff);

	switch (startSq.getPiece().pieceType) {
	case PAWN:
        // TODO
	case KNIGHT:
        // Knight's are the only piece that can move through other pieces
        collisionStatus = false;
        break;

	case BISHOP:
        collisionStatus = this->diagCollision(startRow, endRow, startCol, endCol);
        break;
	case ROOK:
        collisionStatus = this->rowCollision(startRow, startCol, endCol);
        collisionStatus = collisionStatus || this->colCollision(startCol, startRow, endRow);
        break;
	case QUEEN:
        // NOTE: The Queen & King have the same type of valid movements with the length of
        // each movement being the differing factor. But, since I pass the startRow/Col, endRow/Col
        // to each method I should be able to just let this drop through to the KING call.

        // collisionStatus = this->rowCollision(startRow, startCol, endCol);
        // collisionStatus = collisionStatus || this->colCollision(startCol, startRow, endRow);
        // collisionStatus = collisionStatus || this->diagCollision(startrow, endRow, startCol, endCol);
        // break;
	case KING:
        collisionStatus = this->rowCollision(startRow, startCol, endCol);
        collisionStatus = collisionStatus || this->colCollision(startCol, startRow, endRow);
        collisionStatus = collisionStatus || this->diagCollision(startRow, endRow, startCol, endCol);
	default:
	}

	return collisionStatus;
}

bool Rules::isCheck() {
	return false;
}

bool Rules::isCheck(Board b) {
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

bool Rules::diagCollision(int startRow, int endRow, int startCol, int endCol) {
    bool collisionStatus = false;

    if (startRow > endRow) {
        if (startCol > endCol) {
            for (int i = 1; i < abs(endRow - startRow); i++) {
                if (pBoard->getSquare(startRow - i, startCol - i).getPiece() != NOPIECE) {
                    collisionStatus = true;
                }
            }
        } else {
            for (int i = 1; i < abs(endRow - startRow); i++) {
                if (pBoard->getSquare(startRow - i, startCol + i).getPiece() != NOPIECE) {
                    collisionStatus = true;
                }
            }
        }
    } else {
        if (startCol > endCol) {
            for (int i = 1; i < abs(endRow - startRow); i++) {
                if (pBoard->getSquare(startRow + i, startCol - i).getPiece() != NOPIECE) {
                    collisionStatus = true;
                }
            }
        } else {
            for (int i = 1; i < abs(endRow - startRow); i++) {
                if (pBoard->getSquare(startRow + i, startCol + i).getPiece() != NOPIECE) {
                    collisionStatus = true;
                }
            }
        }
    }
	return collisionStatus;
}

bool Rules::colCollision(int col, int startRow, int endRow) {
    bool collisionStatus = false;

    if (startRow > endRow) {
        for (int i = 1; i < abs(endRow - startRow); i++) {
            if (pBoard->getSquare(startRow - i, col).getPiece() != NOPIECE) {
                collisionStatus = true;
            }
        }
    } else {
        for (int i = 1; i < abs(endRow - startRow); i++) {
            if (pBoard->getSquare(startRow + i, col).getPiece() != NOPIECE) {
                collisionStatus = true;
            }
        }
    }

	return collisionStatus;
}

bool Rules::rowCollision(int row, int startCol, int endCol) {
    bool collisionStatus = false;

    if (startCol > endCol) {
        for (int i = 1; i < abs(endCol - startCol); i++) {
            if(pBoard->getSquare(row, startCol - i).getPiece() != NOPIECE) {
                collisionStatus = true;
            }
        }
    } else {
        for (int i = 1; i < abs(endCol - startCol); i++) {
            if(pBoard->getSquare(row, startCol + i).getPiece() != NOPIECE) {
                collisionStatus = true;
            }
        }
    }

	return collisionStatus;
}