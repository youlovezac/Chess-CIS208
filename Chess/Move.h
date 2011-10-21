#ifndef MOVE_H 
#define MOVE_H 

#include "Board.h"

class Move {
public: 
	Move();
	Move(int, int, int, int, Board&);
	void setBoard(Board&);
	void setStart(int, int);
	void setDestination(int, int);
	Square getStart();
	Square getDestination();
	void execute();
private:
	Board* pboard;
	Square start, destination;
};
 
#endif
