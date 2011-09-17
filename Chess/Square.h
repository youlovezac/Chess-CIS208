#ifndef SQUARE_H
#define SQUARE_H

const int RED = 0;
const int BLACK = 1;
const int NOPIECE = 0;
const int PAWN = 1;
const int KNIGHT = -3;
const int BISHOP = 3;
const int ROOK = 5;
const int QUEEN = 9;
const int KING = 1000;

enum colors {RED, BLACK);
enum pieces {NOPIECE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};

class Square {
public:
	Square();							// Default constructor
	Square(colors c);						// Square color constructor
	Square(colors c, pieces p);			// Complete square constructor
	Square(const Square& s);				// Copy constructor
	Square& operator=(const Square& s);		// Overloaded assignment operator
	colors getColor() const;
	pieces getPiece() const;
	void setColor(colors);
	void setPiece(pieces);
private:
	colors squareColor;
	pieces currPiece;
};

#endif SQUARE_H