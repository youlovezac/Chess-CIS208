
#include "Move.h" 
#include "Board.h"
#include "Square.h"

Move::Move() {
	start = NULL;
	destination = NULL;
	pboard = NULL;
}

Move::Move(int r1, int c1, int r2, int c2, Board& b) { // this should be what we need.
    *start = pboard->getSquare(r1, c1); 
    *destination = pboard->getSquare(r2, c2);   
    pboard = &b; // This will take the address of the Board and give it to pBoard
}

void Move::setStart(int r1, int c1)
{
    *start = pboard->getSquare(r1, c1); 
}

void Move::setDestination(int r2, int c2)
{
    *destination = pboard->getSquare(r2, c2);
}

void Move::setBoard(Board& b)
{
    pboard = &b;
}

Square Move::getStart()
{
    return *start; 
}

Square Move::getDestination() 
{
    return *destination;
}
