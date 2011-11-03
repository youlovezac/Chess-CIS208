#include <cstdlib>
#include "Rules.h"
#include "Square.h"

// Defines the generic threat types
const int DIAG = 0;
const int ROW = -1;
const int COL = 2;

Rules::Rules() {
    pBoard = NULL;
}

Rules::Rules(Board* pointer) {
	pBoard = pointer;
}

// check correct color is being moved
// check piece has capacity to move to that square
// check that destination is vacant or occupied by opponent
// check that it doesn't place you into check
// check if anything is in the way (e.g. e2e4, nothing is on e3 unless it's a knight)
// TODO check for castling
// TODO check for en passant
bool Rules::isLegal(Move m, Color currPlayerColor) {
	bool legalStatus = true;
	Square startSq = m.getStart();
	Square endSq = m.getDestination();
	Piece p = startSq.getPiece();

	// Player can't move the other player's color
	if (p.pieceColor != currPlayerColor) {
		legalStatus = false;

	// Can't move onto a square that one of your piece occupies
	} else if (endSq.getPiece().pieceColor == currPlayerColor) {
		legalStatus = false;

	// if end square isn't empty only matters if pawn is moving in a non-capture capacity
	// otherwise the piece will simply capture the occupant
    // TODO Double check this check.
	} else if (endSq.getPiece().pieceType != NOPIECE) {
		legalStatus = false;

	// Can't place your own King in check
	} else if (placesKingInCheck(m)) {
		legalStatus = false;

	// Movement path must match piece's established moving pattern
	} else if (!isValidMovementPath(m, currPlayerColor)) {
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

bool Rules::placesKingInCheck(Move m) {
	// Make a copy of the board and execute the move.
	// Then call isCheck with new Board
	    // Need two copies of isCheck maybe
	    // 1 to handle ptr to board
	    // 1 to handle Board passed as parameter
	Board b = *pBoard;

	Move tempMove(m.getStart().getRow(), m.getStart().getCol(), m.getDestination().getRow(), m.getDestination().getCol(), b);
	tempMove.execute();

	return isCheck(b);
}

bool Rules::isValidMovementPath(Move m, Color currPlayerColor)  {
	bool validPath = true;

	Square startSq = m.getStart();
	Square endSq = m.getDestination();

	// A move must consist of at least two different squares
	// Otherwise the player can just pass their turn by entering
	// the same square for start and end squares.
	validPath = (startSq.getRow() != endSq.getRow() || startSq.getCol() != endSq.getCol());

	// The start and end squares must be within the confines of the board
    validPath = !(isOutOfBounds(startSq) || isOutOfBounds(endSq));

	switch (startSq.getPiece().pieceType) {
	case PAWN:
		validPath = isValidPawnMove(startSq, endSq, currPlayerColor);
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

bool Rules::isOutOfBounds(Square s)  {
    return (SQ_LL >= s.getRow() || s.getRow() <= SQ_UL ||
           SQ_LL >= s.getCol() || s.getCol() <= SQ_UL); 
}

bool Rules::isValidPawnMove(Square startSq, Square endSq, Color currPlayerColor)  {
	int absRowDiff = 0, absColDiff = 0;

	int startRow = 0, endRow = 0;
	int startCol = 0, endCol = 0;

	int whitePawnStartingRow = SQ_LL + 1;
	int blackPawnStartingRow = SQ_UL - 1;

	bool validPath = true;

	startRow = startSq.getRow();
	endRow = endSq.getRow();

	startCol = startSq.getCol();
	endCol = endSq.getCol();

	absRowDiff = abs(endRow - startRow);
	absColDiff = abs(endCol - startCol);


	// Need current player's color since they move in opposing directions
	// White moves forward from Row 1 to Row 8
	if (currPlayerColor == WHITE) {

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
        } else if ((startCol == endCol || absColDiff != 1 || endRow - startRow != 1) && 
                  (endSq.getPiece().pieceType != NOPIECE) &&
                  (startSq.getPiece().pieceColor != endSq.getPiece().pieceColor)) {
			validPath = false;
		}

	}
	// Black moves forward from Row 8 to Row 1
	else if (currPlayerColor == BLACK) {

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
        } else if ((startCol == endCol || absColDiff != 1 || startRow - endRow != 1) && 
                  (endSq.getPiece().pieceType != NOPIECE) && 
                  (startSq.getPiece().pieceColor != endSq.getPiece().pieceColor)) {
			validPath = false;
		}

	} else {
		validPath = false;
	}

	return validPath;	
}

bool Rules::isValidBishopMove(Square startSq, Square endSq)  {
	int absRowDiff = 0, absColDiff = 0;

	absRowDiff = abs(endSq.getRow() - startSq.getRow());
	absColDiff = abs(endSq.getCol() - startSq.getCol());

	return (absRowDiff == absColDiff);
}

bool Rules::isValidKnightMove(Square startSq, Square endSq)  {
	int absRowDiff = 0, absColDiff = 0;

	absRowDiff = abs(endSq.getRow() - startSq.getRow());
	absColDiff = abs(endSq.getCol() - startSq.getCol());

	return (absRowDiff == 2 && absColDiff == 1) || (absRowDiff == 1 && absColDiff == 2);
}

bool Rules::isValidRookMove(Square startSq, Square endSq)  {
	return (startSq.getRow() == endSq.getRow()) || (startSq.getCol() == endSq.getCol());
}

bool Rules::isValidQueenMove(Square startSq, Square endSq)  {
	int absRowDiff = 0, absColDiff = 0;

	absRowDiff = abs(endSq.getRow() - startSq.getRow());
	absColDiff = abs(endSq.getCol() - startSq.getCol());

	return (absRowDiff == absColDiff) || (startSq.getRow() == endSq.getRow() || startSq.getCol() == endSq.getCol());
}

bool Rules::isValidKingMove(Square startSq, Square endSq)  {
	int absRowDiff = 0, absColDiff = 0;

	absRowDiff = abs(endSq.getRow() - startSq.getRow());
	absColDiff = abs(endSq.getCol() - startSq.getCol());

	return (absRowDiff <= 1) && (absColDiff <= 1);
}

bool Rules::collision(Move m)  {
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

        // A hack to get the colCollision method to work with pawns.
        // Normally the xxxCollision methods check every square upto the 
        // end square. However, the pawn needs its end square checked so
        // I need to pass row after the endRow to the method
        if (startCol == endCol) {
            collisionStatus = colCollision(startCol, startRow, endRow + 1);
        }
        break;
	case KNIGHT:
        // Knight's are the only piece that can move through other pieces
        collisionStatus = false;
        break;

	case BISHOP:
        collisionStatus = diagCollision(startRow, endRow, startCol, endCol);
        break;
	case ROOK:
        collisionStatus = rowCollision(startRow, startCol, endCol);
        collisionStatus = collisionStatus || colCollision(startCol, startRow, endRow);
        break;
	case QUEEN:
        // NOTE: The Queen & King have the same type of valid movements with the length of
        // each movement being the differing factor. But, since I pass the startRow/Col, endRow/Col
        // to each method I should be able to just let this drop through to the KING case.
	case KING:
        collisionStatus = rowCollision(startRow, startCol, endCol);
        collisionStatus = collisionStatus || colCollision(startCol, startRow, endRow);
        collisionStatus = collisionStatus || diagCollision(startRow, endRow, startCol, endCol);
        break;
	default:
        collisionStatus = true;
	}

	return collisionStatus;
}

bool Rules::isCheck(Square king, Color currPlayerColor) {
	int kRow, kCol;
	bool checkStatus;

	kRow = king.getRow();
	kCol = king.getCol();

	// Pawn threat detection
	checkStatus = isThreat(currPlayerColor, kRow, kCol, PAWN);

	// Knight threat detection
	checkStatus = checkStatus || isThreat(currPlayerColor, kRow, kCol, KNIGHT);

	// General threat detection for everything but Pawns and Knights
	for (int i = SQ_LL + 1; i <= SQ_UL && !checkStatus; ++i) {

		// Diagonal threat detection.
		checkStatus = checkStatus || isThreat(currPlayerColor, kRow + i, kCol + i, DIAG); // 1st quadrant diag
		checkStatus = checkStatus || isThreat(currPlayerColor, kRow - i, kCol + i, DIAG); // 2nd quadrant diag
		checkStatus = checkStatus || isThreat(currPlayerColor, kRow - i, kCol - i, DIAG); // 3rd quadrant diag
		checkStatus = checkStatus || isThreat(currPlayerColor, kRow + i, kCol - i, DIAG); // 4th quadrant diag
		// Row threat detection
		checkStatus = checkStatus || isThreat(currPlayerColor, kRow, kCol + i, ROW); // Squares to right of king
		checkStatus = checkStatus || isThreat(currPlayerColor, kRow, kCol - i, ROW); // Squares to left of king
		// Column threat detection
		checkStatus = checkStatus || isThreat(currPlayerColor, kRow + i, kCol, COL); // Squares above king
		checkStatus = checkStatus || isThreat(currPlayerColor, kRow - i, kCol, COL); // Square below king
	}

	return checkStatus;
}

bool Rules::isPawnThreat(Color currPlayerColor, int row, int col) {
	Square s;
	bool threatStatus = false;

	//TODO: Should I return TRUE if it's out of bounds???

	if ((row > SQ_UL || row < SQ_LL ) || (col > SQ_UL || col < SQ_LL)) {
		// Outside of board boundaries = no threat
	} else {

		s = pBoard->getSquare(row, col);
		threatStatus = s.getPiece().pieceType == PAWN && s.getPiece().pieceColor != currPlayerColor;
	}

	return threatStatus;
}


bool Rules::isKnightThreat(Color currPlayerColor, int row, int col) {
	Square s;
	bool threatStatus = false;

	//TODO: Should I return TRUE if it's out of bounds???

	if ((row > SQ_UL || row < SQ_LL ) || (col > SQ_UL || col < SQ_LL)) {
		// Outside of board boundaries = no threat
	} else {
		s = pBoard->getSquare(row, col);
		threatStatus = s.getPiece().pieceType == KNIGHT && s.getPiece().pieceColor != currPlayerColor;
	}

	return threatStatus;
}

bool Rules::isThreat(Color currPlayerColor, int row, int col, int threatType) {
	Square s;
	bool threatStatus = false;

	//TODO: Should I return TRUE if it's out of bounds???

	if ((row > SQ_UL || row < SQ_LL ) || (col > SQ_UL || col < SQ_LL)) {
		// Outside of board boundaries = no threat
	}
	else {
		// TODO: Validate that the square returned has the player's king on it
		s = pBoard->getSquare(row, col);

		switch(threatType) {
			case DIAG:
				threatStatus = (s.getPiece().pieceType == BISHOP || s.getPiece().pieceType == QUEEN) && 
							   (s.getPiece().pieceColor != currPlayerColor);
				break;
			// TODO: The ROW and COL cases are identical, and I could just let ROW drop through to COL
			case ROW:
				threatStatus = (s.getPiece().pieceType == ROOK || s.getPiece().pieceType == QUEEN) && 
							   (s.getPiece().pieceColor != currPlayerColor);
				break;
			case COL:
				threatStatus = (s.getPiece().pieceType == ROOK || s.getPiece().pieceType == QUEEN) && 
							   (s.getPiece().pieceColor != currPlayerColor);
				break;
			case KNIGHT: // KNIGHT value is from the Piece enumeration
				// Check the eight possible squares, relative to the king, that a knight can
				// threaten the king from
				threatStatus = isKnightThreat(currPlayerColor, row + 2, col + 1);
				threatStatus = threatStatus || isKnightThreat(currPlayerColor, row + 2, col - 1);
				threatStatus = threatStatus || isKnightThreat(currPlayerColor, row - 2, col + 1);
				threatStatus = threatStatus || isKnightThreat(currPlayerColor, row - 2, col - 1);
				threatStatus = threatStatus || isKnightThreat(currPlayerColor, row + 1, col + 2);
				threatStatus = threatStatus || isKnightThreat(currPlayerColor, row + 1, col - 2);
				threatStatus = threatStatus || isKnightThreat(currPlayerColor, row - 1, col + 2);
				threatStatus = threatStatus || isKnightThreat(currPlayerColor, row - 1, col - 2);
				break;
			case PAWN: // PAWN value is from the Piece enumeration
				// Check the two squares immediately diagonal to (and in front of) the king's current position
				if (currPlayerColor == WHITE) {
					threatStatus = isPawnThreat(currPlayerColor, row + 1, col - 1);
					threatStatus = threatStatus || isPawnThreat(currPlayerColor, row + 1, col + 1);
				} else {
					threatStatus = isPawnThreat(currPlayerColor, row - 1, col - 1);
					threatStatus = threatStatus || isPawnThreat(currPlayerColor, row - 1, col + 1);
				}
				break;
			default:
				threatStatus = true;
		}
	}

	return threatStatus;
 }


bool Rules::isCheck(Board b) {
	return false;
}

bool Rules::isCheckmate()  {
    // See isCheck AND add condition that King cannot move out of check
    //      (i.e. move king to all positions and recheck for check)
	return false;
}

bool Rules::isDraw()  {
	return false;
}

//bool Rules::isStalemate() {
//	return false;
//}

bool Rules::isWhiteWin()  {
	return false;
}

bool Rules::isBlackWin()  {
	return false;
}

bool Rules::diagCollision(int startRow, int endRow, int startCol, int endCol)  {
    bool collisionStatus = false;

    if (startRow > endRow) {
        if (startCol > endCol) {
            for (int i = 1; i < abs(endRow - startRow); i++) {
                if (pBoard->getSquare(startRow - i, startCol - i).getPiece().pieceType != NOPIECE) {
                    collisionStatus = true;
                }
            }
        } else {
            for (int i = 1; i < abs(endRow - startRow); i++) {
                if (pBoard->getSquare(startRow - i, startCol + i).getPiece().pieceType != NOPIECE) {
                    collisionStatus = true;
                }
            }
        }
    } else {
        if (startCol > endCol) {
            for (int i = 1; i < abs(endRow - startRow); i++) {
                if (pBoard->getSquare(startRow + i, startCol - i).getPiece().pieceType != NOPIECE) {
                    collisionStatus = true;
                }
            }
        } else {
            for (int i = 1; i < abs(endRow - startRow); i++) {
                if (pBoard->getSquare(startRow + i, startCol + i).getPiece().pieceType != NOPIECE) {
                    collisionStatus = true;
                }
            }
        }
    }
	return collisionStatus;
}

bool Rules::colCollision(int col, int startRow, int endRow)  {
    bool collisionStatus = false;

    if (startRow > endRow) {
        for (int i = 1; i < abs(endRow - startRow); i++) {
            if (pBoard->getSquare(startRow - i, col).getPiece().pieceType != NOPIECE) {
                collisionStatus = true;
            }
        }
    } else {
        for (int i = 1; i < abs(endRow - startRow); i++) {
            if (pBoard->getSquare(startRow + i, col).getPiece().pieceType != NOPIECE) {
                collisionStatus = true;
            }
        }
    }

	return collisionStatus;
}

bool Rules::rowCollision(int row, int startCol, int endCol)  {
    bool collisionStatus = false;

    if (startCol > endCol) {
        for (int i = 1; i < abs(endCol - startCol); i++) {
            if(pBoard->getSquare(row, startCol - i).getPiece().pieceType != NOPIECE) {
                collisionStatus = true;
            }
        }
    } else {
        for (int i = 1; i < abs(endCol - startCol); i++) {
            if(pBoard->getSquare(row, startCol + i).getPiece().pieceType != NOPIECE) {
                collisionStatus = true;
            }
        }
    }

	return collisionStatus;
}