#ifndef SQUARE_H
#define SQUARE_H
const int RED = 0;
const int BLACK = 1;
const int PAWN = 1;
const int KNIGHT = -3;
const int BISHOP = 3;
const int ROOK = 5;
const int QUEEN = 9;
const int KING = 1000;

enum colors {RED, BLACK);
enum pieces {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};

class Square {
public:
	colors getColor() const;
	pieces getPiece() const;
	void setColor(int);
	void setPiece(int);
private:
	colors squareColor;
	pieces currPiece;
};

#endif SQUARE_H