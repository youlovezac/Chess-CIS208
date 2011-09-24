#include "Move.h"
#include "Board.h"

Move::Move(int r1, int c1, int r2, int c2, Board* pboard)
{
	start = pboard->getSquare(r1, c1); 
	destination = pboard->getSquare(r2, c2); 
};