#ifndef MOVE_H 
#define MOVE_H 



class Board;
class Square;
class Move {
public: 
    Move();
	Move(int, int, int, int, Board&); // this should be what we need.
    void setStart(int, int);
    void setDestination(int, int);
	void setBoard(Board&);
    Square getStart();
    Square getDestination();
private:
    Board* pboard;
    Square *start, *destination;
};
 
#endif