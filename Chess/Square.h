#ifndef SQUARE_H
#define SQUARE_H


//const int WHITE = 0;
//const int BLACK = 1;
//const int NOPIECE = 0;
//const int PAWN = 1;
//const int KNIGHT = -3;
//const int BISHOP = 3;
//const int ROOK = 5;
//const int QUEEN = 9;
//const int KING = 1000;

enum colors {WHITE=0, BLACK=1};
enum pieces {NOPIECE=0, PAWN=1, KNIGHT=-3, BISHOP=3, ROOK=5, QUEEN=9, KING=1000};
enum pieceColors {WHITE=0, BLACK=1};

class Square {
public:
	Square();							// Default constructor
	Square(colors c);						// Square color constructor
	Square(colors c, pieces p);			// Complete square constructor
	Square(const Square& s);				// Copy constructor
	Square& operator=(const Square& s);		// Overloaded assignment operator
	colors getColor() const;
	pieces getPiece() const;
	pieceColors getPiece() const;
	void setColor(colors);
	void setPiece(pieces);
	void setPieceColor(pieceColors);
private:
	colors squareColor;
	pieces currPiece;
	pieceColors currPieceColor;
};

#endif SQUARE_H