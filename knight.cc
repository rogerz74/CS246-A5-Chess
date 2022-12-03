#include "knight.h"

Knight::Knight(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord):
    Piece{name, board, whitePlayer, xCoord, yCoord} {}

bool Knight::isLegal(Box &targetBox) {

    // if WHITE CAPTURE BLACK OR BLACK CAPTURE WHITE
    if ((((*(this->getBoard()))[targetBox.getX()][targetBox.getY()]) && 
        ((checkWhitePlayer() && !(((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ||
         (!checkWhitePlayer() && (((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ) )) {
        return true;
    }
    return false;
}

void Knight::updateLegalMoves() {
    std::vector<Box> legalMoves;
    std::vector<int> moveStates;

    int x = this->getX();
    int y = this->getY();

    if ((x + 2 < 8) && (y + 1 < 8)) {
        Box move1(x + 2, y + 1);
        if (isLegal(move1)) {
            legalMoves.push_back(move1);
            moveStates.push_back(1);
        } else if (!((*(this->getBoard()))[move1.getX()][move1.getY()])) {
            legalMoves.push_back(move1);
            moveStates.push_back(0);
        }
    }

    if ((x - 2 >= 0) && ( y - 1 >= 0)) {
        Box move2(x - 2, y - 1);
        if (isLegal(move2)) {
            legalMoves.push_back(move2);
            moveStates.push_back(1);
        } else if(!((*(this->getBoard()))[move2.getX()][move2.getY()])) {
            legalMoves.push_back(move2);
            moveStates.push_back(0);
        }
    }

    if ((x + 2 < 8) && ( y - 1 >= 0)) {
        Box move3(x + 2, y - 1);
        if (isLegal(move3)) {
            legalMoves.push_back(move3);
            moveStates.push_back(1);
        } else if (!((*(this->getBoard()))[move3.getX()][move3.getY()])) {
            legalMoves.push_back(move3);
            moveStates.push_back(0);
        }
    }

    if ((x - 2 >= 0) && (y + 1 < 8)) {
        Box move4(x - 2, y + 1);
        if (isLegal(move4)) {
            legalMoves.push_back(move4);
            moveStates.push_back(1);
        } else if (!((*(this->getBoard()))[move4.getX()][move4.getY()])) {
            legalMoves.push_back(move4);
            moveStates.push_back(0);
        }
    }

    if ((x + 1 < 8) && (y + 2 < 8)) {
        Box move5(x + 1, y + 2);
        if (isLegal(move5)) {
            legalMoves.push_back(move5);
            moveStates.push_back(1);
        } else if (!((*(this->getBoard()))[move5.getX()][move5.getY()])) {
            legalMoves.push_back(move5);
            moveStates.push_back(0);
        }
    }

    if ((x - 1 >= 0) && (y - 2 >= 0)) {
        Box move6(x - 1, y - 2);
        if (isLegal(move6)) {
            legalMoves.push_back(move6);
            moveStates.push_back(1);
        } else if (!((*(this->getBoard()))[move6.getX()][move6.getY()])) {
            legalMoves.push_back(move6);
            moveStates.push_back(0);
        }
    }

    if ((x + 1 < 8) && (y - 2 >= 0)) {
        Box move7(x + 1, y - 2);
        if (isLegal(move7)) {
            legalMoves.push_back(move7);
            moveStates.push_back(1);
        } else if (!((*(this->getBoard()))[move7.getX()][move7.getY()])) {
            legalMoves.push_back(move7);
            moveStates.push_back(0);
        }
    }

    if ((x - 1 >= 0) && (y + 2 < 8)) {
        Box move8(x - 1, y + 2);
        if (isLegal(move8)) {
            legalMoves.push_back(move8);
            moveStates.push_back(1);
        } else if (!((*(this->getBoard()))[move8.getX()][move8.getY()])) {
            legalMoves.push_back(move8);
            moveStates.push_back(0);
        }
    }

    this->getLegalMoves() = &legalMoves;
    this->getMoveStates() = &moveStates;
}
