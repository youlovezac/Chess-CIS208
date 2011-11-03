#include "Move.h"

Move::Move() {
	pboard = NULL;
}

Move::Move(int r1, int c1, int r2, int c2, Board& b) {
	pboard = &b;
	start = pboard->getSquare(r1, c1);
	destination = pboard->getSquare(r2, c2);
}

void Move::setStart(int r1, int c1) {
	start = pboard->getSquare(r1, c1); 
}

void Move::setDestination(int r2, int c2) {
	destination = pboard->getSquare(r2, c2);
}

void Move::setBoard(Board& b) {
	pboard = &b;
}

Square Move::getStart() {
	return start; 
}

Square Move::getDestination() {
	return destination;
}

void Move::execute() {
	Piece emptyPiece = { WHITE, NOPIECE };
	Piece movedPiece = start.getPiece();
	pboard->setSquare(start.getRow(), start.getCol(), emptyPiece);
	pboard->setSquare(destination.getRow(), destination.getCol(), movedPiece);
	pboard->incrementTurn();
}

