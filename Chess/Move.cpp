#include "Move.h" 

Move::move(int r1, int c1, int r2, int c2, Board* pboard)
{
	start = pboard->getSquare(r1, c1); 
	destination = pboard->getSquare(r2, c2); 
};

Board Move::getStart(int, int)
{
	return start;
}

Board Move::getDestination(int, int)
{
	return destination;
}