#include <iostream>
#include <stdio.h>
#include "Board.h"
#include "Display.h"
#include "Rules.h"
#include "Move.h"

using namespace std;

int main(int argc, char **argv) {
	Move move;
	Display d(argc, argv);
	Board b;
	Rules r;
	Color player = BLACK;
	while(1) {
		move = d.getMove(b, r, player);
		move.execute();
		player = (player==BLACK) ? WHITE : BLACK;
	}
	return 0;
}

/*
	//Board board;
	//Display display;
	//Rules rules;			// by convention, we'll list board, display and rules in this order, in parameter lists and so on
	//Move move;
	//Player wPlayer = {WHITE}, bPlayer = {BLACK}, currentPlayer;
	//
	//do {
	//	display.setUpPlayers(wPlayer, bPlayer); // returns players set to appropriate playerType
	//											// playerType is user, computer or file -- also store color?
	//	currentPlayer = wPlayer;
	//	board.setUp();
	//	display.showPosition(board);

	//	while (! rules.isGameOver(board)) {
	//		move = display.getMove(board, rules, currentPlayer); // move returned is legal
	//		board.makeMove(move); // no need to pass rules at this point
	//		display.showPosition(board);

	//		// change sides, i.e., whose turn it is to move
	//		if (currentPlayer == wPlayer)
	//			currentPlayer = bPlayer;
	//		else
	//			currentPlayer = wPlayer;
	//	}			// TODO leave the user a way to quit mid-game

	//	// TODO There must be a simpler and more elegant way to do this, 
	//	// involving interaction between rules, display and main()
	//	if (rules.isDraw(board)) 
	//		display.printDrawMessage();
	//	else if (rules.isWhiteWin(board))
	//		display.printWhiteWinsMessage();
	//	else if (rules.isBlackWin(board))
	//		display.printBlackWinsMessage();
	//} while (! display.askForGame()); // returns false if user quits

*/
