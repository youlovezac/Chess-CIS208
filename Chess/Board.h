#ifndef BOARD_H
#define BOARD_H

// defines class Board which keeps track of the position, 
// but doesn't display it and doesn't know the rules

class Board
{
public:
	Board(); // standard constructor
	Board(const Board& board); // copy constructor
	Board& operator=(const Board& board);
	Move getMove(Square start, square dest); // this might end up not being used
	void makeMove(Move m); // this either
	Square getSquare(int rank, int file); // returns a specific square
	void setSquare(int rank, int file, Color color, Piece p); // I can't recall exactly what setSquare should be passed, but this'll do for now.
private:
	Move m;
	Square chessBoard[8][8];
	Board boardHistory[200]; // The 200 turn limit implies that there will be at the very most 200 different board-states. (Is that a word? It is now!)
};

#endif