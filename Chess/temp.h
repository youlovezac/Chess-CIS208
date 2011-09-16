// Players can be one of three types: user, AI, file

// One way of handling the three types -- define constants with numeric values 

int const USER = 0;
int const AI = 1;
int const FILE = 2;

switch (currentPlayer) {
	USER: // do stuff for user player
	  break;
	AI:// do stuff for AI player
	  break;
	FILE: // do stuff for file
	  break;
}

// A better way of handling the three types -- define a single enumerated type

enum playerType {USER, AI, FILE};	// C++ compiler actually sets USER to 0, AI to 1, etc

switch (currentPlayer) {	
	USER: // do stuff for user player
	  break;
	AI:// do stuff for AI player
	  break;
	FILE: // do stuff for file
	  break;
};

// This does everything the first example does, but also allows the compiler to do 
// some useful type-checking










