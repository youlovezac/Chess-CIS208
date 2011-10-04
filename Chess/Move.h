#ifndef MOVE_H 
#define MOVE_H 

class Move 
{ 
public: 
	move(int, int, int, int, Board*); 
	Board getStart(int, int); 
	Board getDestination(int, int); 

private:
	Board* pboard;
	Square start(); 
	Square destination();
}; 

#endif MOVE_H 
