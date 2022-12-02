#include "pawn.h"

Pawn::Pawn(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord):
    Piece{name, board,whitePlayer, xCoord, yCoord} {}

bool Pawn::isLegal(Box &targetBox) {
    // checks if targetBox is occupied and Piece is of opposite colour (in order to capture)
    if ((((*(this->getBoard()))[targetBox.getX()][targetBox.getY()]) && 
        ((checkWhitePlayer() && !(((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ||
         (!checkWhitePlayer() && (((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ) )) {
        return true;
    }
    return false;
}

void Pawn::updateLegalMoves() {
    std::vector<Box> legalMoves;
    std::vector<int> moveStates;

    int x = this->getX();
    int y = this->getY();

    // Caputre
    if (checkWhitePlayer() && (x - 1 >= 0) && (y - 1 >= 0)) {
        Box captureMove1(x - 1, y - 1);
        if (isLegal(captureMove1)) {
            legalMoves.push_back(captureMove1);
            moveStates.push_back(1);
        }
    }
    
    if (checkWhitePlayer() && (x - 1 >= 0) && (y + 1 < 8)) {
        Box captureMove2(x - 1, y + 1);
        if (isLegal(captureMove2)) {
            legalMoves.push_back(captureMove2);
            moveStates.push_back(1);
        }
    }

    if (!checkWhitePlayer() && (x + 1 < 8) && (y - 1 >= 0)) {
        Box captureMove3(x + 1, y - 1);
        if (isLegal(captureMove3)) {
            legalMoves.push_back(captureMove3);
            moveStates.push_back(1);
        }
    }

    if (!checkWhitePlayer() && (x + 1 < 8) && (y + 1 < 8)) {
        Box captureMove4(x + 1, y + 1);
        if (isLegal(captureMove4)) {
            legalMoves.push_back(captureMove4);
            moveStates.push_back(1);
        }
    }

    // First move (2 spaces forward)
    if (checkWhitePlayer() && (x == 6) && !((*(this->getBoard()))[x - 2][y])) {
        Box initialMove1(x - 2, y);
        legalMoves.push_back(initialMove1);
        moveStates.push_back(0);

        // En passant (Note that we need to delete the newly added move to the opposing pawn 
        // if it is not used immediately!)
        if ((y - 1 >= 0) && ((*(this->getBoard()))[x - 2][y - 1])->getName() == "p") {
            Box opponentPawnMove1(x - 1, y);
            ((*(this->getBoard()))[x - 2][y - 1])->getLegalMoves()->push_back(opponentPawnMove1);
            ((*(this->getBoard()))[x - 2][y - 1])->getMoveStates()->push_back(-1);
        }

        if ((y + 1 < 8) && ((*(this->getBoard()))[x - 2][y + 1])->getName() == "p") {
            Box opponentPawnMove2(x - 1, y);
            ((*(this->getBoard()))[x - 2][y + 1])->getLegalMoves()->push_back(opponentPawnMove2);
            ((*(this->getBoard()))[x - 2][y + 1])->getMoveStates()->push_back(-1);
        }
    }

    if (!checkWhitePlayer() && (x == 1) && !((*(this->getBoard()))[x - 2][y])) {
        Box initialMove2(x + 2, y);
        legalMoves.push_back(initialMove2);
        moveStates.push_back(0);

        // En passant (Note that we need to delete the newly added move to the opposing pawn 
        // if it is not used immediately!)
        if ((y - 1 >= 0) && ((*(this->getBoard()))[x + 2][y - 1])->getName() == "P") {
            Box opponentPawnMove1(x + 1, y);
            ((*(this->getBoard()))[x + 2][y - 1])->getLegalMoves()->push_back(opponentPawnMove1);
            ((*(this->getBoard()))[x + 2][y - 1])->getMoveStates()->push_back(-1);
        }

        if ((y + 1 < 8) && ((*(this->getBoard()))[x + 2][y + 1])->getName() == "p") {
            Box opponentPawnMove2(x + 1, y);
            ((*(this->getBoard()))[x + 2][y + 1])->getLegalMoves()->push_back(opponentPawnMove2);
            ((*(this->getBoard()))[x + 2][y + 1])->getMoveStates()->push_back(-1);
        }
    }

    // Regular one space forward
    if (checkWhitePlayer() && (x - 1 >= 0) && !((*(this->getBoard()))[x - 1][y])) {
        Box move1(x - 1, y);
        legalMoves.push_back(move1);
        moveStates.push_back(0);
    }

    if (!checkWhitePlayer() && (x + 1 < 8) && !((*(this->getBoard()))[x - 1][y])) {
        Box move2(x + 1, y);
        legalMoves.push_back(move2);
        moveStates.push_back(0);
    }

    this->getLegalMoves() = &legalMoves;
    this->getMoveStates() = &moveStates;
}
