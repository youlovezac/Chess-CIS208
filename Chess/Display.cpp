#include "Display.h"
#include "Move.h"

void Display::setUpPlayers(Player wPlayer, Player bPlayer) {
	isWhite = true;
}

void Display::enableFileMode(const char *file) {
	isFileMode = true;
	chessfile.open(file, fstream::out);
	
}

Move Display::getMove(Board* board, Rules rules, Player currentPlayer) {
	if(currentPlayer.playerColor == BLACK) isWhite = false;
	else isWhite = true;
	int startr=0, startc=0, endr=0, endc=0;
	Move retMove;
	bool readytomoveon = false;
	if(enableFileMode) {
		chessfile >> startr >> startc >> endr >> endc;
		Move tempMove(startr, startc, endr, endc, board);
		if(isLegal(tempMove, currentPlayer)) readytomoveon = true;
	}
		
	while(!readytomoveon) {
		cout << "Enter the starting row: ";
		cin >> startr;
		cout << "Enter the starting column: ";
		cin >> startc;
		cout << "Enter the requested row: ";
		cin >> endr;
		cout << "Enter the requested column: ";
		cin >> endc;
		Move tempMove(startr, startc, endr, endc, board);
		if(isLegal(tempMove, currentPlayer)) readytomoveon = true;
	}
	retMove = tempMove;
	return retMove;
}
	
