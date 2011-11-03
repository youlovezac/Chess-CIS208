#ifndef DISPLAY_H
#define DISPLAY_H

#include "Move.h"
#include "Rules.h"

class Display {
public:
	Display(int, char**);
        Move getMove(Board& b, Rules& r, Color playerColor);
private:
	bool filemode;
	char *filename; // argv is char*, not string
};

#endif
