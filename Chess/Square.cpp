// Author: Josh Halstead

#include "Square.h"
#include "misc.h"

// Default constructor
Square::Square() {
	squareColor = WHITE;
	currPiece = NOPIECE;
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

colors Square::getColor() const {
	return squareColor;
}

pieces Square::getPiece() const {
	return currPiece;
}

void Square::setColor(colors c) {
	squareColor = c;
}

void Square::setPiece(pieces p) {
	currPiece = p;
}
