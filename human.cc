#include <iostream>
#include "human.h"
#include "chessGame.h"

Human::Human(ChessGame *subject, std::string name): subject{subject}, name{name} {
    subject->attach(this);
}

Human::~Human() {
    subject->detach(this);
}

// helper function
int stringToCoord(char c) {
    if (c == 'a' || c == '8') {
        return 0;
    } else if (c == 'b' || c == '7') {
        return 1;
    } else if (c == 'c' || c == '6') {
        return 2;
    } else if (c == 'd' || c == '5') {
        return 3;
    } else if (c == 'e' || c == '4') {
        return 4;
    } else if (c == 'f' || c == '3') {
        return 5;
    } else if (c == 'g' || c == '2') {
        return 6;
    } else {
        return 7;
    }
}

bool Human::pickMove() {
    bool resignStatus = 0;
    std::string comm;
    while ((resignStatus != 1) && (std::cin >> comm)) {
        if (comm == "move") {
            std::string a;
            std::string b;
            std::cin >> a >> b;
            std::cout << std::endl;
            int aX = stringToCoord(a[1]);
            int aY = stringToCoord(a[0]);
            int bX = stringToCoord(b[1]);
            int bY = stringToCoord(b[0]);
            int success = (*(subject->getBoard()))[aX][aY]->move((*(subject->getBoard()))[aX][aY], 
                        (*(subject->getBoard()))[bX][bY], bX, bY);
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
