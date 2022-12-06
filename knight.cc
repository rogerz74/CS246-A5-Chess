#include "knight.h"

Knight::Knight(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord):
    Piece{name, board, whitePlayer, xCoord, yCoord} {}

bool Knight::getIsFirstMove() {
    return false;
}

void Knight::updateIsFirstMove() {}

bool Knight::isLegal(Box &targetBox) {

    // if WHITE CAPTURE BLACK OR BLACK CAPTURE WHITE
    if ((((*(this->getBoard()))[targetBox.getX()][targetBox.getY()]) && 
        ((checkWhitePlayer() && !(((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ||
         (!checkWhitePlayer() && (((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ) )) {
        return true;
    }
    return false;
}

std::map<Box, int> Knight::updateLegalMoves() {
    std::map<Box, int> legalMoves;

    int x = this->getX();
    int y = this->getY();

    if ((x + 2 < 8) && (y + 1 < 8)) {
        Box move1(x + 2, y + 1);
        if (isLegal(move1)) {
            legalMoves.insert({move1, 1});
        } else if (!((*(this->getBoard()))[move1.getX()][move1.getY()])) {
            legalMoves.insert({move1, 0});
        }
    }

    if ((x - 2 >= 0) && ( y - 1 >= 0)) {
        Box move2(x - 2, y - 1);
        if (isLegal(move2)) {
            legalMoves.insert({move2, 1});
        } else if(!((*(this->getBoard()))[move2.getX()][move2.getY()])) {
            legalMoves.insert({move2, 0});
        }
    }

    if ((x + 2 < 8) && ( y - 1 >= 0)) {
        Box move3(x + 2, y - 1);
        if (isLegal(move3)) {
            legalMoves.insert({move3, 1});
        } else if (!((*(this->getBoard()))[move3.getX()][move3.getY()])) {
            legalMoves.insert({move3, 0});
        }
    }

    if ((x - 2 >= 0) && (y + 1 < 8)) {
        Box move4(x - 2, y + 1);
        if (isLegal(move4)) {
            legalMoves.insert({move4, 1});
        } else if (!((*(this->getBoard()))[move4.getX()][move4.getY()])) {
            legalMoves.insert({move4, 0});
        }
    }

    if ((x + 1 < 8) && (y + 2 < 8)) {
        Box move5(x + 1, y + 2);
        if (isLegal(move5)) {
            legalMoves.insert({move5, 1});
        } else if (!((*(this->getBoard()))[move5.getX()][move5.getY()])) {
            legalMoves.insert({move5, 0});
        }
    }

    if ((x - 1 >= 0) && (y - 2 >= 0)) {
        Box move6(x - 1, y - 2);
        if (isLegal(move6)) {
            legalMoves.insert({move6, 1});
        } else if (!((*(this->getBoard()))[move6.getX()][move6.getY()])) {
            legalMoves.insert({move6, 0});
        }
    }

    if ((x + 1 < 8) && (y - 2 >= 0)) {
        Box move7(x + 1, y - 2);
        if (isLegal(move7)) {
            legalMoves.insert({move7, 1});
        } else if (!((*(this->getBoard()))[move7.getX()][move7.getY()])) {
            legalMoves.insert({move7, 0});
        }
    }

    if ((x - 1 >= 0) && (y + 2 < 8)) {
        Box move8(x - 1, y + 2);
        if (isLegal(move8)) {
            legalMoves.insert({move8, 1});
        } else if (!((*(this->getBoard()))[move8.getX()][move8.getY()])) {
            legalMoves.insert({move8, 0});
        }
    }

    return legalMoves;
}
