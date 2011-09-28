#include "Board.h"
#include "misc.h"
#include "Square.h"
using namespace std;

class Board{

public:

Board::void setUp(){
	Square filler; // temporary square object used to fill each square
	Piece occupant; // with assumption that we will write a piece class
	Color pieceColor; // with assumption that we will write a color class for the board and pieces
	for(int j = 0; j < 8; i++){ // loop through ranks
		if(j = 0 || j = 7){ // if first or last rank (the ranks with the non-pawn pieces).
			for(int i = 0; i < 8; i++){ //loop through files
				
				if(j = 7) // if in the far row, piece color would be set to black.
					occupant.pieceColor = BLACK; // will likely change
				else
					pieceColor.pieceColor = WHITE; // " "
				if(i = 0 || i = 7) // for the 1st and last square of the back and front rows, the piece is a rook
					occupant.pieceType = ROOK; // will likely change
				else if(i = 1 || i = 6) // second and second to last square get knights
					occupant.pieceType = KNIGHT;
				else if(i = 2 || i = 5) // now for the bishops
					occupant.pieceType = BISHOP; // will likely change
				else if(i = 3)
					occupant.pieceType = KING;
				else if(i = 4)
					occupant.pieceType = QUEEN;
				

				
				filler.setPiece(occupant);
				filler.setColor(pieceColor);
				chessBoard[j][i] = filler; // should work since Josh overloaded Square's = operator
			}
		}
		if(j = 1 || j = 6){ // if second or second to last rank (the pawn rows).
			occupant = PAWN; // will likely change
			for(int k = 0; j < 8; j++){
				if(j = 6) // if second to farthest row
					pieceColor = BLACK; //will likely change
				else
					pieceColor = WHITE; //will likely change
				filler.setPiece(occupant);
				filler.setColor(pieceColor);
				chessBoard[j][k] = filler;
			}
		}
		else{ // the rest will be empty squares
			occupant = NOPIECE; // will likely change
			for(int l = 0; l < 8; l++){
				filler.setPiece(occupant);
				chessBoard[j][l] = filler;
			}
		}

	} // end for(j =0;... loops

} // end setUp

Board::Board& operator=(const Board& board){
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j ++) {
			chessBoard[i][j] = board.chessBoard[i][j];
		}
	}
}

Move Board::getMove(Move m){
	
}


void Board::makeMove(){
	// Not sure if I even need this, get and set square might be all I need.
}
Square Board::getSquare(int rank, int file){ 
	return chessBoard[rank][file];
}


void Board::setSquare(int rank, int file, Color color, Piece p){ // 
	chessBoard[rank][file].setColor(color);
	chessBoard[rank][file].currPiece(p);

}

void Board::updateBoardHistory() {
	boardHistory[turn - 1] = chessBoard; // using the turn number as an index, copies the current board-state into an element of the boardHistory array
    // how turns will be stored is speculative
}


private:
Board::Board() // standard constructor, might possibly be usable for initializing new games
{
	this->setUp();
} // end constructor


Board::Board(const Board& board){ // copy constructor
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j ++) {
			chessBoard[i][j] = board.chessBoard[i][j];
		}
	}
	// might also want to write something to copy boardHistory, but may not be needed.
}
Square chessBoard[8][8];
Board boardHistory[200]; // The 200 turn limit implies that there will be at the very most 200 different board-states. (Is that a word? It is now!)
};