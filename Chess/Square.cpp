// Author: Josh Halstead

#include "Square.h"

// Default constructor to set each value to 0 (RED and NOPIECE)
Square::Square() {
	squareColor = WHITE;
	currPiece = NOPIECE;
	currPieceColor = WHITE;
}

// Square color constructor
Square::Square(colors c) {
	squareColor = c;
	currPiece = NOPIECE;
	currPieceColor = WHITE;
}

// Complete square constructor
Square::Square(colors c, pieces p, pieceColors pc) {
	squareColor = c;
	currPiece = p;
	currPieceColor = pc;
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
