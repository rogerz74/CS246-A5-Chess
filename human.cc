#include <iostream>
#include "human.h"
#include "chessGame.h"

Human::Human(ChessGame *subject, std::string name): subject{subject}, name{name} {
    subject->attach(this);
}

Human::~Human() {
    subject->detach(this);
}

void Human::notify() {

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
