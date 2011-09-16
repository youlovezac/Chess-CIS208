#ifndef DISPLAY_H
#define DISPLAY_H

// defines class Display which handles all (?) the I/O, especially
// displaying the board, but doesn't actually keep track of the board position by itself


class Display
{
public:
	// returns players set to appropriate playerType
	// playerType is user, computer or file -- also store color?
	void setUpPlayers(Player wPlayer, Player bPlayer); 
												
private:
	// maybe store a pointer to the board here
};

#endif