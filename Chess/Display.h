#ifndef DISPLAY_H
#define DISPLAY_H

#include "Move.h"
#include "misc.h"

class Display {
public:
        Move getMove(Board& b, Player currentPlayer);
};

#endif