#include "chessGame.h"
#include "subject.h"
#include "observer.h"
#include "human.h"
#include "computer.h"
#include "box.h"
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include <iostream>
#include <string>

using namespace std;

// a helper function that manages the initial setup and the pieces will need to created here.
// the return type of this function will probably need to indicate which color won the game

// a helper function to convert the letter to a number; I tried using enums but converting a string to an enum is difficult
int strToCoord(char c) {
    if (c == 'a') {
        return 0;
    } else if (c == 'b') {
        return 1;
    } else if (c == 'c') {
        return 2;
    } else if (c == 'd') {
        return 3;
    } else if (c == 'e') {
        return 4;
    } else if (c == 'f') {
        return 5;
    } else if (c == 'g') {
        return 6;
    } else {
        return 7;
    }
}

int main() {

    // this part will contain the loop that allows for multiple games of
    // chess to be run and tracked.


    


}