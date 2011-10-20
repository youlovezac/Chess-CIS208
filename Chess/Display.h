#ifndef DISPLAY_H
#define DISPLAY_H

#include <fstream>
#include <iostream>
#include <string>
#include "misc.h"

class Move;
class Rules;
class Display {
public:
	void setUpPlayers(Player wPlayer, Player bPlayer);
	void enableFileMode(const char *file);
	Move getMove(Board& board, Rules rules, Player currentPlayer);
private:
	bool isFileMode;
	const char *nameoffile;		// argv only comes in char pointer arrays, sorry for C++ strings
	ifstream chessfile;
	bool isWhite;
};

#endif