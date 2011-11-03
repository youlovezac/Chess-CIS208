#include <iostream>
#include <cstdio>
#include "Display.h"

using namespace std;

Display::Display(int argc, char **argv) {
	if(argc < 2) filemode = false;
	else {
		filemode = true;
		filename = argv[1];
	}
}

Move Display::getMove(Board& b, Rules& r, Color playerColor) {
	if(!filemode) {
        cout << "  | 01234567 |" << endl;
        cout << "----------------" << endl;
        
        // In order to orient the board correctly, the first row sent to the console should be 
        // the last row of the board and so on.
        //
        // Also, I switched the row and col notation to the standard convention
        // Previously, row=j and col=i
        // Now, row=i and col=j
		for(int i=7; i>=0; i--) {
            cout << i << " | ";

		    for(int j=0; j<8; j++) {
				Color c = b.getSquare(i, j).getPiece().pieceColor;
				PieceType p = b.getSquare(i, j).getPiece().pieceType;
				if(p==NOPIECE) cout << " ";
				else if(c==BLACK) {
					if(p==PAWN) cout << "p";
					else if(p==KNIGHT) cout << "n";
					else if(p==BISHOP) cout << "b";
					else if(p==ROOK) cout << "r";
					else if(p==QUEEN) cout << "q";
					else if(p==KING) cout << "k";
				} else if(c==WHITE) {
					if(p==PAWN) cout << "P";
					else if(p==KNIGHT) cout << "N";
					else if(p==BISHOP) cout << "B";
					else if(p==ROOK) cout << "R";
					else if(p==QUEEN) cout << "Q";
					else if(p==KING) cout << "K";
				}
			}
            cout << " | " << i << endl;
		}
        cout << "----------------" << endl;
        cout << "  | 01234567 |" << endl;

		int startr=0, startc=0, endr=0, endc=0;
		while(1) {
			cout << "row 1: ";
			cin >> startr;
			cout << "column 1: ";
			cin >> startc;
			cout << "row 2: ";
			cin >> endr;
			cout << "column 2: ";
			cin >> endc;
			Move m(startr, startc, endr, endc, b);
			if(r.isLegal(m, playerColor)) return m;
			cout << "That's not a legal move" << endl;
		}
	}
}
