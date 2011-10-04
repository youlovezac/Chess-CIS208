#ifndef MOVE_H 
#define MOVE_H 

#include "Square.h"
#include "Board.h"

class Move 
{ 
public: 
	Move(int, int, int, int, Board); 
	Square getStart(); 
	Square getDestination(); 

private:
	Board* pboard;
	Square start; 
	Square destination;
}; 

#endif MOVE_H 
