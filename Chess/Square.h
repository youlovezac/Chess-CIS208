#ifndef SQUARE_H
#define SQUARE_H

#include "misc.h"

class Square {
public:
	Square(); // Default constructor
	Square(const Square& s); // Copy constructor
	Square& operator=(const Square& s); // Overloaded assignment operator
	bool operator==(const Square& s); // Equivalance operator
	bool operator!=(const Square& s); // Inequivalence operator
	Color getColor() const;
	Piece getPiece() const;
	int getRow() const;
	int getCol() const;
	void setColor(Color);
	void setPiece(Piece);
	// Consider adding methods to get square coordinates
private:
	int row; // Rank
	int col; // File
	Color squareColor;
	Piece currPiece;
};

#endif
