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
                if ((*(subject->getBoard()))[a][b-1]) {
                    (*(subject->getBoard()))[a][b-1]->print();
                } else { // printing black or white
                    int val1 = a % 2;
                    int val2 = b % 2;

                    if (!val1 && !val2) {
                        std::cout << " ";
                    } else {
                        std::cout << "_";
                    }
                }

            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "  abcdefgh" << std::endl; // printing the bottom a-h column value

}
