#ifndef SQUARE_H
#define SQUARE_H

#include "misc.h"


class Square {
public:
	Square();	// Default constructor
	Square(const Square& s); // Copy constructor
	Square& operator=(const Square& s); // Overloaded assignment operator
	colors getColor() const;
	pieces getPiece() const;
	void setColor(colors);
	void setPiece(pieces);
	// Consider adding methods to get square coordinates
private:
	int row; // Rank
	int col; // File
	colors squareColor;
	pieces currPiece;
};

#endif SQUARE_H