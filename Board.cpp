#include "Board.h"

void Board::setUp() {
	Square filler;
	Piece occupant; 
	turns = 0;
	Color squareColor;
 
	for(int j = 0; j < 8; j++) {
		if(j == 0 || j == 7) {
			for(int i = 0; i < 8; i++) {
				if(j==7) occupant.pieceColor = BLACK;
				else occupant.pieceColor = WHITE; 
				if(i == 0 || i == 7) occupant.pieceType = ROOK; 
				else if(i == 1 || i == 6) occupant.pieceType = KNIGHT;
				else if(i == 2 || i == 5) occupant.pieceType = BISHOP; 
				else if(i == 3) occupant.pieceType = KING;
				else if(i == 4) occupant.pieceType = QUEEN;
				if(j % 2 == 0 || j == 0){ 
					if(i % 2 == 0 || i == 0) squareColor = WHITE;
					else squareColor = BLACK;
				} else {
					if(i % 2 == 0 || i == 0) squareColor = BLACK;
					else squareColor = WHITE;
				}
				filler.setCol(j);
				filler.setRow(i);
				filler.setPiece(occupant);
				filler.setColor(squareColor);
				chessBoard[j][i] = filler;
				
			}
		}
		else if(j == 1 || j == 6) {
			occupant.pieceType = PAWN;
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
				chessBoard[j][i] = filler;
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
				chessBoard[j][i] = filler;
			}
		}

	} // end for(j =0;... loops

} // end setUp

Board& Board::operator=(const Board& board){
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j ++) {
			chessBoard[i][j] = board.chessBoard[i][j];
		}
	}
	return *this;
}

Board::Board() {
	setUp();
} // end constructor


Board::Board(const Board& board){ // copy constructor
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j ++) {
			chessBoard[i][j] = board.chessBoard[i][j];
		}
	}
}

Square Board::getSquare(int rank, int file){ 
	return chessBoard[rank][file]; // returns the corresponding square
}

void Board::setSquare(int rank, int file, Piece p) {
	chessBoard[rank][file].setPiece(p);
}

void Board::incrementTurn() {
	turns++;
}

void Board::decrementTurn() {
	turns--;
}

