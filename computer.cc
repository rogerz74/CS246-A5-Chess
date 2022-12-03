#include <iostream>
#include "computer.h"
#include "chessGame.h"
#include "piece.h"


/*

IMPORTANT: The implementation for the 4 levels function is missing right now. That will be added once we have all the other components working properly.

*/

Computer::Computer(ChessGame *subject, std::string name, vector<Piece> * pieceArray): subject{subject}, name{name}, pieceArray{pieceArray} {
    subject->attach(this);
}

Computer::~Computer() {
    subject->detach(this);
}

void Computer::notify() {

    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 9; b++) {
            if (b == 0) {
                std::cout << (8-a) << " "; // printing the left-hand side row value
            } else {
                // we will NEED TO ADD A print() function to Box Class to print either a piece, a Black tile (_) or a white tile ( )
                std::cout << subject->getBoard()[a][b-1]->print();
            }
        }
    }
    std::cout << std::endl;
    std::cout << "  abcdefgh" << std::endl; // printing the bottom a-h column value

}
