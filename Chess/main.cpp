#include <iostream>
#include "Board.h"
#include "Display.h"
#include "Rules.h"
#include "Move.h"

using namespace std;

int main(int argc, char **argv) {
	Move move;
	Display d;
	Board b;
	Rules r;
	Color player = BLACK;
	
	move = d.getMove(b, player);

	return 0;
}
