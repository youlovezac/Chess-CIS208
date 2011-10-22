#include <cstdlib>
#include "Rules.h"

Rules::Rules() {
	pBoard = NULL;
}

Rules::Rules(Board* pointer) {
	pBoard = pointer;
}

bool Rules::isLegal(Move m, Color playerColor) {
	bool legalStatus = true;
	Square startSq = m.getStart();
	Square endSq = m.getDestination();
	Piece p = startSq.getPiece();

	if(p.pieceColor != playerColor) legalStatus = false;
	else if(endSq.getPiece().pieceColor == playerColor) legalStatus = false;
	else if(endSq.getPiece().pieceType != NOPIECE) legalStatus = false;
	//else if(placesKingInCheck(m)) legalStatus = false;
	else if(!isValidMovementPath(m, playerColor)) legalStatus = false;
	else if(collision(m)) legalStatus = false;
	return legalStatus;
}

bool Rules::placesKingInCheck(Move m) {
	Board b = *pBoard;
	Move tempMove(m.getStart().getRow(), m.getStart().getCol(), m.getDestination().getRow(), m.getDestination().getCol(), b);
	tempMove.execute();
	//return isCheck(b);
	return false;
}

bool Rules::isValidMovementPath(Move m, Color playerColor)  {
	bool validPath = true;
	Square startSq = m.getStart();
	Square endSq = m.getDestination();
	int ptype = m.getStart().getPiece().pieceType;
	if(startSq != endSq) validPath = false;
	else if(!isOutOfBounds(startSq) || !isOutOfBounds(endSq)) validPath = false;
	switch(m.getStart().getPiece().pieceType) {
	case PAWN:
		validPath = isValidPawnMove(startSq, endSq, playerColor);
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
    return(s.getRow() < SQ_LL || s.getRow() > SQ_UL || s.getCol() < SQ_LL || s.getCol() > SQ_UL); 
}

bool Rules::isValidPawnMove(Square startSq, Square endSq, Color playerColor)  {
	int absRowDiff = 0, absColDiff = 0, startRow = 0, endRow = 0, startCol = 0, endCol = 0;
	int whitePawnStartingRow = SQ_LL + 1;
	int blackPawnStartingRow = SQ_UL - 1;
	bool validPath = true;
	startRow = startSq.getRow();
	endRow = endSq.getRow();
	startCol = startSq.getCol();
	endCol = endSq.getCol();
	absRowDiff = abs(endRow - startRow);
	absColDiff = abs(endCol - startCol);
	if(playerColor == WHITE) {
		if(startRow < whitePawnStartingRow) {
			validPath = false;
        	} else if(endRow < startRow) {
			validPath = false;
        	} else if (!(startRow == whitePawnStartingRow && absRowDiff == 2) && !(startRow >= whitePawnStartingRow && absRowDiff == 1)) {
			validPath = false;
		} else if((startCol == endCol || absColDiff != 1 || endRow - startRow != 1) && (endSq.getPiece().pieceType != NOPIECE) && (startSq.getPiece().pieceColor != endSq.getPiece().pieceColor)) {
			validPath = false;
		}
	} else if(playerColor == BLACK) {
		if(startRow > blackPawnStartingRow) validPath = false;
		else if(endRow > startRow) validPath = false;
		else if(!(startRow == blackPawnStartingRow && absRowDiff == 2) && !(startRow <= blackPawnStartingRow && absRowDiff == 1)) validPath = false;
		else if((startCol == endCol || absColDiff != 1 || startRow - endRow != 1) && (endSq.getPiece().pieceType != NOPIECE) && (startSq.getPiece().pieceColor != endSq.getPiece().pieceColor)) validPath = false;
	} else validPath = false;
	return validPath;	
}

bool Rules::isValidBishopMove(Square startSq, Square endSq)  {
	int absRowDiff = abs(endSq.getRow() - startSq.getRow());
	int absColDiff = abs(endSq.getCol() - startSq.getCol());
	return (absRowDiff == absColDiff);
}

bool Rules::isValidKnightMove(Square startSq, Square endSq)  {
	int absRowDiff = abs(endSq.getRow() - startSq.getRow());
	int absColDiff = abs(endSq.getCol() - startSq.getCol());
	return (absRowDiff == 2 && absColDiff == 1) || (absRowDiff == 1 && absColDiff == 2);
}

bool Rules::isValidRookMove(Square startSq, Square endSq)  {
	return (startSq.getRow() == endSq.getRow()) || (startSq.getCol() == endSq.getCol());
}

bool Rules::isValidQueenMove(Square startSq, Square endSq)  {
	int absRowDiff = abs(endSq.getRow() - startSq.getRow());
	int absColDiff = abs(endSq.getCol() - startSq.getCol());
	return (absRowDiff == absColDiff) || (startSq.getRow() == endSq.getRow() || startSq.getCol() == endSq.getCol());
}

bool Rules::isValidKingMove(Square startSq, Square endSq)  {
	int absRowDiff = abs(endSq.getRow() - startSq.getRow());
	int absColDiff = abs(endSq.getCol() - startSq.getCol());
	return (absRowDiff <= 1) && (absColDiff <= 1);
}

bool Rules::collision(Move m)  {
	int rowDiff = 0, colDiff = 0, absRowDiff = 0, absColDiff = 0, startRow = 0, startCol = 0, endRow = 0, endCol = 0;
	bool collisionStatus = false;
	Square startSq = m.getStart();
	Square endSq = m.getDestination();
	startRow = startSq.getRow();
	startCol = startSq.getCol();
	endRow = endSq.getRow();
	endCol = endSq.getCol();
	rowDiff = endRow - startRow;
	colDiff = endCol - startCol;
	absRowDiff = abs(rowDiff);
	absColDiff = abs(colDiff);
	switch(startSq.getPiece().pieceType) {
	case PAWN:
		if(startCol == endCol) collisionStatus = colCollision(startCol, startRow, endRow + 1);
		break;
	case KNIGHT:
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

bool Rules::isCheck(Square king, Color playerColor) {
	int kRow = king.getRow();
	int kCol = king.getCol();
	bool checkStatus = isThreat(playerColor, kRow, kCol, PAWN);
	checkStatus = checkStatus || isThreat(playerColor, kRow, kCol, KNIGHT);
	for(int i = SQ_LL + 1; i <= SQ_UL && !checkStatus; ++i) {
		checkStatus = checkStatus || isThreat(playerColor, kRow + i, kCol + i, DIAG);
		checkStatus = checkStatus || isThreat(playerColor, kRow - i, kCol + i, DIAG);
		checkStatus = checkStatus || isThreat(playerColor, kRow - i, kCol - i, DIAG);
		checkStatus = checkStatus || isThreat(playerColor, kRow + i, kCol - i, DIAG);
		checkStatus = checkStatus || isThreat(playerColor, kRow, kCol + i, ROW);
		checkStatus = checkStatus || isThreat(playerColor, kRow, kCol - i, ROW);
		checkStatus = checkStatus || isThreat(playerColor, kRow + i, kCol, COL);
		checkStatus = checkStatus || isThreat(playerColor, kRow - i, kCol, COL);
	}
	return checkStatus;
}

bool Rules::isPawnThreat(Color pColor, int row, int col) {
	bool threatStatus = false;
	if(row < SQ_UL && row > SQ_LL && col < SQ_UL && col > SQ_LL) {
		Square s = pBoard->getSquare(row, col);
		threatStatus = s.getPiece().pieceType == PAWN && s.getPiece().pieceColor != pColor;
	}
	return threatStatus;
}


bool Rules::isKnightThreat(Color pColor, int row, int col) {
	bool threatStatus = false;
	if(row < SQ_UL && row > SQ_LL && col < SQ_UL && col > SQ_LL) {
		Square s = pBoard->getSquare(row, col);
		threatStatus = s.getPiece().pieceType == KNIGHT && s.getPiece().pieceColor != pColor;
	}
	return threatStatus;
}

bool Rules::isThreat(Color pColor, int row, int col, int threatType) {
	bool threatStatus = false;
	if(row < SQ_UL && row > SQ_LL && col < SQ_UL && col > SQ_LL) {
		Square s = pBoard->getSquare(row, col);
		switch(threatType) {
		case DIAG:
				threatStatus = (s.getPiece().pieceType == BISHOP || s.getPiece().pieceType == QUEEN) && 
							   (s.getPiece().pieceColor != pColor);
				break;
			case ROW:
				threatStatus = (s.getPiece().pieceType == ROOK || s.getPiece().pieceType == QUEEN) && 
							   (s.getPiece().pieceColor != pColor);
				break;
			case COL:
				threatStatus = (s.getPiece().pieceType == ROOK || s.getPiece().pieceType == QUEEN) && 
							   (s.getPiece().pieceColor != pColor);
				break;
			case KNIGHT: 
				threatStatus = isKnightThreat(pColor, row + 2, col + 1);
				threatStatus = threatStatus || isKnightThreat(pColor, row + 2, col - 1);
				threatStatus = threatStatus || isKnightThreat(pColor, row - 2, col + 1);
				threatStatus = threatStatus || isKnightThreat(pColor, row - 2, col - 1);
				threatStatus = threatStatus || isKnightThreat(pColor, row + 1, col + 2);
				threatStatus = threatStatus || isKnightThreat(pColor, row + 1, col - 2);
				threatStatus = threatStatus || isKnightThreat(pColor, row - 1, col + 2);
				threatStatus = threatStatus || isKnightThreat(pColor, row - 1, col - 2);
				break;
			case PAWN:
				if(pColor == WHITE) {
					threatStatus = isPawnThreat(pColor, row + 1, col - 1);
					threatStatus = threatStatus || isPawnThreat(pColor, row + 1, col + 1);
				} else {
					threatStatus = isPawnThreat(pColor, row - 1, col - 1);
					threatStatus = threatStatus || isPawnThreat(pColor, row - 1, col + 1);
				}
				break;
			default:
				threatStatus = true;
		}
	}

	return threatStatus;
 }

bool Rules::diagCollision(int startRow, int endRow, int startCol, int endCol)  {
	bool collisionStatus = false;
	if(startRow > endRow) {
		if(startCol > endCol) {
			for(int i = 1; i < abs(endRow - startRow); i++) {
				if(pBoard->getSquare(startRow - i, startCol - i).getPiece().pieceType != NOPIECE) collisionStatus = true;
			}
		} else {
			for(int i = 1; i < abs(endRow - startRow); i++) {
				if(pBoard->getSquare(startRow - i, startCol + i).getPiece().pieceType != NOPIECE) collisionStatus = true;
			}
		}
	} else {
		if(startCol > endCol) {
			for(int i = 1; i < abs(endRow - startRow); i++) {
				if(pBoard->getSquare(startRow + i, startCol - i).getPiece().pieceType != NOPIECE) collisionStatus = true;
			}
		} else {
			for(int i = 1; i < abs(endRow - startRow); i++) {
				if(pBoard->getSquare(startRow + i, startCol + i).getPiece().pieceType != NOPIECE) collisionStatus = true;
			}
		}
	}
	return collisionStatus;
}

bool Rules::colCollision(int col, int startRow, int endRow)  {
	bool collisionStatus = false;
	if(startRow > endRow) {
		for(int i = 1; i < abs(endRow - startRow); i++) {
			if(pBoard->getSquare(startRow - i, col).getPiece().pieceType != NOPIECE) collisionStatus = true;
		}
	} else {
		for(int i = 1; i < abs(endRow - startRow); i++) {
			if(pBoard->getSquare(startRow + i, col).getPiece().pieceType != NOPIECE) collisionStatus = true;
		}
	}
	return collisionStatus;
}

bool Rules::rowCollision(int row, int startCol, int endCol)  {
	bool collisionStatus = false;
	if(startCol > endCol) {
		for(int i = 1; i < abs(endCol - startCol); i++) {
			if(pBoard->getSquare(row, startCol - i).getPiece().pieceType != NOPIECE) collisionStatus = true;
		}
	} else {
		for(int i = 1; i < abs(endCol - startCol); i++) {
			if(pBoard->getSquare(row, startCol + i).getPiece().pieceType != NOPIECE) collisionStatus = true;
		}
	}
	return collisionStatus;
}
