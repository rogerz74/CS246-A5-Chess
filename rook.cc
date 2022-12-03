#include "rook.h"

Rook::Rook(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord):
    Piece{name, board, whitePlayer, xCoord, yCoord}, isFirstMove{true} {}

bool Rook::getIsFirstMove() {
    return isFirstMove;
}

bool Rook::isLegal(Box &targetBox) {
    // if WHITE CAPTURE BLACK OR BLACK CAPTURE WHITE
    if (((checkWhitePlayer() && !(((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ||
         (!checkWhitePlayer() && (((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) )) {
        return true;
    }
    return false;
}

std::map<Box, int> Rook::updateLegalMoves() {
    std::map<Box, int> legalMoves;

    int x = this->getX();
    int y = this->getY();

    // will break loop if there is an existing piece on a box
    // this is also why we need separate loops for each direction

    for (int i = x - 1; i >= 0; --i) {
        Box move1(i, y);
        // if there exists a piece on box (break) and it is capturable add to possible moves
        if ((*(this->getBoard()))[i][y]) {
            if(isLegal(move1)) {
                legalMoves[move1] = 1;
            }
            break;
        }

        // location is empty
        legalMoves[move1] = 0;
    }

    for (int i = x + 1; i < 8; ++i) {
        Box move1(i, y);
        // if there exists a piece on box (break) and it is capturable add to possible moves
        if ((*(this->getBoard()))[i][y]) {
            if(isLegal(move1)) {
                legalMoves[move1] = 1;
            }
            break;
        }

        legalMoves[move1] = 0;
    }

    for (int i = y + 1; i < 8; ++i) {
        Box move1(x, i);
        // if there exists a piece on box (break) and it is capturable add to possible moves
        if ((*(this->getBoard()))[x][i]) {
            if(isLegal(move1)) {
                legalMoves[move1] = 1;
            }
            break;
        }
        
        legalMoves[move1] = 0;
    }

    for (int i = y - 1; i >= 0; --i) {
        Box move1(x, i);
        // if there exists a piece on box (break) and it is capturable add to possible moves
        if ((*(this->getBoard()))[x][i]) {
            if(isLegal(move1)) {
                legalMoves[move1] = 1;
            }
            break;
        }

        legalMoves[move1] = 0;
    }

    return legalMoves;
}
