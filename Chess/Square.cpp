#include "Square.h"

// Default constructor to set each value to 0 (RED and NOPIECE)
Square::Square() {
	squareColor = RED;
	currPiece = NOPIECE;
}

// Square color constructor
Square::Square(colors c) {
	squareColor = c;
	currPiece = NOPIECE;
}

// Complete square constructor
Square::Square(colors c, pieces p) {
	squareColor = c;
	currPiece = p;
}

// Copy Constructor
Square::Square(const Square& s) {
	squareColor = s.squareColor;
	currPiece = s.currPiece;
}

// Overloaded assignment operator
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
