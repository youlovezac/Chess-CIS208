#include "Square.h"

Square::Square() {
	squareColor = WHITE;
	currPiece.pieceType = NOPIECE;
	row = 1;
	col = 1;
}

Square::Square(const Square& s) {
	squareColor = s.squareColor;
	currPiece = s.currPiece;
	row = s.row;
	col = s.col;
}

Square& Square::operator=(const Square& s) {
	if(this != &s) {
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

int Square::getRow() const {
	return row;
}

int Square::getCol() const {
	return col;
}

