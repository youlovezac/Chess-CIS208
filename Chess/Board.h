#ifndef BOARD_H
#define BOARD_H

// defines class Board which keeps track of the position, 
// but doesn't display it and doesn't know the rules

class Board
{
public:
void setUp();
Board& operator=(const Board& board);
Board& operator--(); // Overloaded the -- operator to retract moves.
Board(); // standard constructor
Board(const Board& board); // copy constructor
void makeMove(Move inMove);
Square getSquare(int rank, int file); // returns a specific square
void setSquare(int rank, int file, Color color, Piece p); 
void updateBoardHistory(); // copies current board-state to board history (Is that a word? It is now!)
private:

int turns = 0; // The turn number. I believe we settled on calling the game a draw at a certain number of turns. For now, I'm assuming 200 as that's the highest number I heard in our discussion on turn limits.
Square chessBoard[8][8];
Board boardHistory[200]; // The 200 turn limit implies that there will be at the very most 200 different board-states. 
};

#endif