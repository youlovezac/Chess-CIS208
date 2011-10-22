#ifndef DISPLAY_H
#define DISPLAY_H

#include "Move.h"
#include "Rules.h"

class Display {
public:
        Move getMove(Board& b, Rules& r, Color playerColor);
private:
	
};

#endif
