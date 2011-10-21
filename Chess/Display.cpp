#include <iostream>
#include "Display.h"
using namespace std;

Move Display::getMove(Board& b, Player currentPlayer) {
        int startr=0, startc=0, endr=0, endc=0;
        while(1) {
                cout << "Enter the starting row: ";
                cin >> startr;
                cout << "Enter the starting column: ";
                cin >> startc;
                cout << "Enter the requested row: ";
                cin >> endr;
                cout << "Enter the requested column: ";
                cin >> endc;
                Move m(startr, startc, endr, endc, b);
                // I took out rules for now because my use of it was old and broken
                return m;
        }
}
