#ifndef MISC_H
#define MISC_H

// Defines several miscellaneous classes used by the program


// We're undecided on what format to store the coordinates for each square in the Square class.
//		The choices are 0-based (0-7) and 1-based (1-8).
// 
// The Board is 0-based but the user will enter 1-based notation. Decisions, decisions...
// In the mean time these are here to ease the transition (if one occurs) from 0-based to 1-based
// in my code.
const int SQ_UL = 7;
const int SQ_LL = 0;

enum Color {WHITE=0, BLACK=1};
enum PieceType {NOPIECE=0, PAWN=1, KNIGHT=-3, BISHOP=3, ROOK=5, QUEEN=9, KING=1000};

struct Piece {
	Color pieceColor;
	PieceType pieceType;
};

struct Player {
	Color playerColor;
};

#endif