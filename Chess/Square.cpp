#include "Square.h"

// Default assignment constructor to set each value to 0 (RED and NOPIECE)
Square::Square() {
	squareColor = RED;
	currPiece = NOPIECE;
}

// Color assignment constructor
Square::Square(colors c) {
	squareColor = c;
	currPiece = NOPIECE;
}

// Complete assignment constructor
Square::Square(colors c, pieces p) {
	squareColor = c;
	currPiece = p;
}

// Assignment operator
Square& Square::operator=(const Square& s) {
	if (this != &s) {
		squareColor = s.squareColor;
		currPiece = s.currPiece;
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
