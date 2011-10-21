// Author: Josh Halstead

#include "Square.h"

// Default constructor
Square::Square() {
	squareColor = WHITE;
    currPiece.pieceType = NOPIECE;
	row = 1;
	col = 1;
}

// Copy Constructor
Square::Square(const Square& s) {
	squareColor = s.squareColor;
	currPiece = s.currPiece;
	row = s.row;
	col = s.col;
}

// Overloaded assignment operator
Square& Square::operator=(const Square& s) {
	if (this != &s) {
		squareColor = s.squareColor;
		currPiece = s.currPiece;
		row = s.row;
		col = s.col;
	}

	return *this;
}

bool Square::operator!=(const Square& s) {
	return row != s.getRow() && col != s.getCol();
}

bool Square::operator==(const Square& s) {
	return row == s.getRow() && col == s.getCol();
}

Color Square::getColor() const {
	return squareColor;
}

Piece Square::getPiece() const {
	return currPiece;
}

void Square::setRow(int r) {
	if (r <= SQ_UL && r >= SQ_LL) 
		row = r;
}

void Square::setCol(int c) {
	if (c <= SQ_UL && c >= SQ_LL)
		col = c;
}

int Square::getRow() const {
	return row;
}

int Square::getCol() const {
	return col;
}

void Square::setColor(Color c) {
	squareColor = c;
}

void Square::setPiece(Piece p) {
	currPiece = p;
}
