#ifndef MISC_H
#define MISC_H

// Defines several miscellaneous classes used by the program

enum Color {WHITE=0, BLACK=1};
enum Piece {NOPIECE=0, PAWN=1, KNIGHT=-3, BISHOP=3, ROOK=5, QUEEN=9, KING=1000};

typedef struct {
	Color pieceColor;
	Piece pieceType;
} Piece;

typedef struct {
	Color playerColor;
} Player;

#endif