#ifndef SQUARE_H
#define SQUARE_H

const int SQ_UL = 7;
const int SQ_LL = 0;

typedef enum Color { 
    NOCOLOR = -1,
	WHITE = 0,
	BLACK = 1
} Color;

typedef enum PieceType {
    NOPIECE = -1,
	PAWN = 1,
	KNIGHT = -3,
	BISHOP = 3,
	ROOK = 5,
	QUEEN = 9,
	KING = 1000
} PieceType;

typedef struct Piece {
	Color pieceColor;
	PieceType pieceType;
} Piece;

class Square {
public:
	Square();
	Square(const Square& s);
	Square& operator=(const Square& s);
	bool operator==(const Square& s);
	bool operator!=(const Square& s);
	int getRow() const;
	int getCol() const;
	void setRow(int r);
	void setCol(int c);
	Color getColor() const;
	Piece getPiece() const;
	void setColor(Color c);
	void setPiece(Piece p);
private:
	int row, col;
	Color squareColor;
	Piece currPiece;
};

#endif
