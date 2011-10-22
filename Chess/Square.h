#ifndef SQUARE_H
#define SQUARE_H

#define SQ_UL 7
#define SQ_LL 0

typedef enum Color { 
	WHITE = 0,
	BLACK = 1
} Color;

typedef enum PieceType {
	NOPIECE = 0,
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
	void setRow(int r) { if(r <= SQ_UL && r >= SQ_LL) row = r; }
	void setCol(int c) { if(c <= SQ_UL && c >= SQ_LL) col = c; }
	Color getColor() const;
	Piece getPiece() const;
	void setColor(Color c) { squareColor = c; }
	void setPiece(Piece p) { currPiece = p; }
private:
	int row, col;
	Color squareColor;
	Piece currPiece;
};

#endif
