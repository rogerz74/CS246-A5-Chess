#include "bishop.h"

Bishop::Bishop(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord):
    Piece{name, board, whitePlayer, xCoord, yCoord} {}

bool Bishop::isLegal(Box &targetBox) {

    // if WHITE CAPTURE BLACK OR BLACK CAPTURE WHITE
    if (((checkWhitePlayer() && !(((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ||
         (!checkWhitePlayer() && (((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) )) {
        return true;
    }
    return false;
}

void Bishop::updateLegalMoves() {
    std::vector<Box> legalMoves;
    std::vector<int> moveStates;


    int x = this->getX();
    int y = this->getY();

    // will break loop if there is an existing piece on a box
    // this is also why we need separate loops for each direction

    for (int i = 1; x - i >= 0 && y + i < 8; ++i) {

        Box move1(x - i, y + i);
        // if there exists a piece on box (break) and it is capturable add to possible moves
        if (((*(this->getBoard()))[x - i][y + i])) {
            if(isLegal(move1)) {
                legalMoves.push_back(move1);
                moveStates.push_back(1);
            }
            break;
        }
        // location is empty
        legalMoves.push_back(move1);
        moveStates.push_back(0);
    }

    for (int i = 1; x + i  < 8 && y - i >= 0; ++i) {

        Box move1(x + i, y - i);
        if (((*(this->getBoard()))[x + i][y - i])) {
            if(isLegal(move1)) {
                legalMoves.push_back(move1);
                moveStates.push_back(1);
            }
            break;
        }
        legalMoves.push_back(move1);
        moveStates.push_back(0);
    }

    for (int i = 1; x - i  >= 0 && y - i >= 0; ++i) {

        Box move1(x - i, y - i);
        if (((*(this->getBoard()))[x - i][y - i])) {
            if(isLegal(move1)) {
                legalMoves.push_back(move1);
                moveStates.push_back(1);
            }
            break;
        }
        legalMoves.push_back(move1);
        moveStates.push_back(0);
    }

    for (int i = 1; x + i  < 8 && y + i < 8; ++i) {

        Box move1(x + i, y + i);
        if (((*(this->getBoard()))[x + i][y + i])) {
            if(isLegal(move1)) {
                legalMoves.push_back(move1);
                moveStates.push_back(1);
            }
            break;
        }
        legalMoves.push_back(move1);
        moveStates.push_back(0);
    }

    this->getLegalMoves() = &legalMoves;
    this->getMoveStates() = &moveStates;
}
