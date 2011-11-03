#include "Board.h"

Board& Board::operator=(const Board& board){
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j ++) {
			chessBoard[i][j] = board.chessBoard[i][j];
		}
	}
	return *this;
}

Board::Board() {
	Square filler;
	Piece occupant; 
	turns = 0;
	Color squareColor;
	for(int j=0; j<8; j++) {
		if(j==0 || j==7) {
			for(int i=0; i<8; i++) {
				if(j==7) occupant.pieceColor = BLACK;
				else occupant.pieceColor = WHITE; 
				if(i==0 || i==7) occupant.pieceType = ROOK; 
				else if(i==1 || i==6) occupant.pieceType = KNIGHT;
				else if(i==2 || i==5) occupant.pieceType = BISHOP; 
				else if(i==3) occupant.pieceType = KING;
				else if(i==4) occupant.pieceType = QUEEN;
				if(j%2==0){ 
					if(i%2==0) squareColor = WHITE;
					else squareColor = BLACK;
				} else {
					if(i%2==0) squareColor = BLACK;
					else squareColor = WHITE;
				}
				filler.setCol(j);
				filler.setRow(i);
				filler.setPiece(occupant);
				filler.setColor(squareColor);
				chessBoard[j][i] = filler;
				
			}
		} else if(j == 1 || j == 6) {
			occupant.pieceType = PAWN;
			for(int i=0; i<8; i++){
				if(j==6) occupant.pieceColor = BLACK;
				else occupant.pieceColor = WHITE;
				if(j%2==0) {
					if(i%2==0) squareColor = WHITE;
					else squareColor = BLACK;
				} else {
					if(i%2==0) squareColor = BLACK;
					else squareColor = WHITE;
				}
				filler.setCol(j);
				filler.setRow(i);
				filler.setPiece(occupant);
				filler.setColor(squareColor);
				chessBoard[j][i] = filler;
			}
		} else {
			occupant.pieceType = NOPIECE;
			for(int i = 0; i < 8; i++){
				if(j%2==0) {
					if(i%2==0) squareColor = WHITE;
					else squareColor = BLACK;
				} else{
					if(i%2==0)  squareColor = BLACK;
					else squareColor = WHITE;
				}
				filler.setCol(j);
				filler.setRow(i);
				filler.setPiece(occupant);
				filler.setColor(squareColor);
				chessBoard[j][i] = filler;
			}
		}
	}
}


Board::Board(const Board& board) {
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j ++) chessBoard[i][j] = board.chessBoard[i][j];
	}
}

Square Board::getSquare(int rank, int file){ 
	return chessBoard[rank][file];
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

