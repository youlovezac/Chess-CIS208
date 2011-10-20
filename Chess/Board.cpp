#include "Board.h"
#include "Square.h"
#include "Move.h"
#include "misc.h"
using namespace std;

void Board::setUp(){
	Square filler; // temporary square object used to fill each square
	Piece occupant; 
	turns = 0; // Turns will be initialized here because if it is initialized in the constructor, it won't reset when new games are started after the first without closing the program.
	Color squareColor;
 
	for(int j = 0; j < 8; j++){ // loop through ranks
		if(j == 0 || j == 7){ // if first or last rank (the ranks with the non-pawn pieces).
			for(int i = 0; i < 8; i++){ //loop through files
				
				if(j == 7) // if in the far row, piece color would be set to black.
					occupant.pieceColor = BLACK; // will likely change
				else
					occupant.pieceColor = WHITE; 
				if(i == 0 || i == 7) // for the 1st and last square of the back and front rows, the piece is a rook
					occupant.pieceType = ROOK; 
				else if(i == 1 || i == 6) // second and second to last square get knights
					occupant.pieceType = KNIGHT;
				else if(i == 2 || i == 5) // now for the bishops
					occupant.pieceType = BISHOP; 
				else if(i == 3)
					occupant.pieceType = KING;
				else if(i == 4)
					occupant.pieceType = QUEEN;
				// The following lines are if statements that create the alternating color scheme of the chessboard.
				// I would think there is a better way to do this, but I'll leave this in until I think of one or one is suggested.
				if(j % 2 == 0 || j == 0){ 
					if(i % 2 == 0 || i == 0) 
						squareColor = WHITE;
					else
						squareColor = BLACK;
				}
				else{
					if(i % 2 == 0 || i == 0) 
						squareColor = BLACK;
					else
						squareColor = WHITE;
				}

				filler.setCol(j);
				filler.setRow(i);
				filler.setPiece(occupant);
				filler.setColor(squareColor);
				*chessBoard[j][i] = filler;
				
			}
		}
		if(j == 1 || j == 6){ // if second or second to last rank (the pawn rows).
			occupant.pieceType = PAWN; // will likely change
			for(int i = 0; i < 8; i++){
				if(j == 6) // if second to farthest row
					occupant.pieceColor = BLACK; //will likely change
				else
					occupant.pieceColor = WHITE; //will likely change

				if(j % 2 == 0){ // condition changed due to the fact that J will never be zero here.
					if(i % 2 == 0 || i == 0) 
						squareColor = WHITE;
					else
						squareColor = BLACK;
				}
				else{
					if(i % 2 == 0 || i == 0) 
						squareColor = BLACK;
					else
						squareColor = WHITE;
				}

				filler.setCol(j);
				filler.setRow(i);
				filler.setPiece(occupant);
				filler.setColor(squareColor);
				*chessBoard[j][i] = filler;
			}
		}
		else{ // the rest will be empty squares
			occupant.pieceType = NOPIECE; // will likely change
			for(int i = 0; i < 8; i++){
				// empty squares still alternate colors
				if(j % 2 == 0){ // condition changed due to the fact that J will never be zero here.
					if(i % 2 == 0 || i == 0) 
						squareColor = WHITE;
					else
						squareColor = BLACK;
				}
				else{
					if(i % 2 == 0 || i == 0) 
						squareColor = BLACK;
					else
						squareColor = WHITE;
				}

				filler.setCol(j);
				filler.setRow(i);
				filler.setPiece(occupant);
				filler.setColor(squareColor);
				*chessBoard[j][i] = filler;
			}
		}

	} // end for(j =0;... loops

} // end setUp

Board& Board::operator=(const Board& board){
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j ++) {
			*chessBoard[i][j] = *board.chessBoard[i][j];
		}
	}
	return *this;
}

Board& Board::operator--(){
	turns--;
	// chessBoard = boardHistory.chessBoard[turns]; // There will be more to this once I figure out how this will interact with display.
	return *this;
}

Board::Board()
{
	setUp();
} // end constructor


Board::Board(const Board& board){ // copy constructor
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j ++) {
			*chessBoard[i][j] = *board.chessBoard[i][j];
		}
	}
}

void Board::makeMove(Move inMove){
	// Update the board so that the piece within the starting square is in the destination square. 
	Square start = inMove.getStart();
	Piece movedPiece, emptyPiece;
	int startRank = start.getRow();
	int startFile = start.getCol();
	Square dest = inMove.getDestination();
	int destRank = dest.getRow();
	int destFile = dest.getCol();

	movedPiece = start.getPiece(); // moves the piece
	emptyPiece.pieceType = NOPIECE;

	setSquare(startRank, startFile, emptyPiece); // removes the piece from the starting square
	setSquare(destRank, destFile, movedPiece);

	// will get much more complex as pawn promotion, en passant, and castling are taken into account
	turns++;
	updateBoardHistory();
}
Square Board::getSquare(int rank, int file){ 
	return *chessBoard[rank][file]; // returns the corresponding square
}


void Board::setSquare(int rank, int file, Piece p){ // 
	(*chessBoard[rank][file]).setPiece(p);
}

void Board::updateBoardHistory() {
	*boardHistory[turns] = (*this); 
	// using the turn number as an index, copies the current board-state into an element of the boardHistory array
}


