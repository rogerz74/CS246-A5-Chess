#include <iostream>
#include "human.h"
#include "chessGame.h"

Human::Human(ChessGame *subject, std::string name): subject{subject}, name{name} {
    subject->attach(this);
}

Human::~Human() {
    subject->detach(this);
}


bool Human::pickMove() {
    bool resignStatus = 0;
    while ((resignStatus != 1) && (std::cin >> comm)) {
        if (comm == "move") {
            std::cin >> a >> b;
            std::cout << std::endl;
            int aX = strToCoord(a[1]);
            int aY = strToCoord(a[0]);
            int bX = strToCoord(b[1]);
            int bY = strToCoord(b[0]);
            success = (*(gameBoard->getBoard()))[aX][aY]->move((*(gameBoard->getBoard()))[aX][aY], 
                        (*(gameBoard->getBoard()))[bX][bY], bX, bY);
            if (success != 1) {
                std::cout << "Invalid move! Please try again: ";
            } 
        } else if (comm == "resign") {
            resignStatus = 1;
        } else {
            std::cout << "Invalid command! Please try again: ";
        }
    }
    return resignStatus;
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
