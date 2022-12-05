#include <iostream>
#include "computer.h"


Computer::Computer(ChessGame *subject, std::string name, std::vector<Piece*> * pieceArray, std::vector<Piece*> * oppArray): subject{subject}, name{name}, pieceArray{pieceArray}, oppArray{oppArray} {
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

void Computer::promotePawn(Piece * p) {
    Piece *pawnPromoPiece;
    if (p->getName() == "P" && p->getX() == 0) {
        pawnPromoPiece = new Queen {"Q", subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
    }  else if (p->getName() == "p" && p->getX() == 7) {
        pawnPromoPiece = new Queen {"q", subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
    }

    // look for pawn and delete it
    pieceArray->erase(find(pieceArray->begin(), pieceArray->end(), p));

    // add queen to vector and board
    pieceArray->emplace_back(pawnPromoPiece);
    (*(subject->getBoard()))[p->getX()][p->getY()] = pawnPromoPiece;

    delete p;
}
