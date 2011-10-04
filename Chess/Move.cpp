#include "Move.h" 

Move::Move(int r1, int c1, int r2, int c2, Board b)
{
    pboard = &b;
	start = pboard->getSquare(r1, c1); 
	destination = pboard->getSquare(r2, c2);
};

Square Move::getStart()
{
	return start;
}

Square Move::getDestination()
{
	return destination;
}