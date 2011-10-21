#ifndef MOVE_H 
#define MOVE_H 

#include "Board.h"

class Move {
public: 
    Move();
	Move(int, int, int, int, Board&); // this should be what we need.

	void setBoard(Board&);
    void setStart(int, int);
    void setDestination(int, int);

    Square getStart();
    Square getDestination();

	void execute(); // Replaces makeMove in Board to remove circular reference issues 
private:
    Board* pboard;
    Square start, destination;
};
 
#endif