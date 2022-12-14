#include "pawn.h"
#include <algorithm>
#include <iostream>

Pawn::Pawn(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord):
    Piece{name, board,whitePlayer, xCoord, yCoord} {}

bool Pawn::getIsFirstMove() {
    return false;
}

void Pawn::updateIsFirstMove() {}

bool Pawn::isLegal(Box &targetBox) {
    // checks if targetBox is occupied and Piece is of opposite colour (in order to capture)
    if ((((*(this->getBoard()))[targetBox.getX()][targetBox.getY()]) && 
        ((checkWhitePlayer() && !(((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ||
         (!checkWhitePlayer() && (((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ) )) {
        return true;
    }
    return false;
}

std::map<Box, int> Pawn::updateLegalMoves() {
    std::map<Box, int> legalMoves;

    int x = this->getX();
    int y = this->getY();

    // Regular one space forward
    if (checkWhitePlayer() && (x - 1 >= 0) && !((*(this->getBoard()))[x - 1][y])) {
        Box move1(x - 1, y);
        legalMoves.insert({move1, 0});
    }

    if (!checkWhitePlayer() && (x + 1 < 8) && !((*(this->getBoard()))[x + 1][y])) {
        Box move2(x + 1, y);
        legalMoves.insert({move2, 0});
    }

    // Capture
    if (checkWhitePlayer() && (x - 1 >= 0) && (y - 1 >= 0)) {
        Box captureMove1(x - 1, y - 1);
        if (isLegal(captureMove1)) {
            legalMoves.insert({captureMove1, 1});
        }
    }
    
    if (checkWhitePlayer() && (x - 1 >= 0) && (y + 1 < 8)) {
        Box captureMove2(x - 1, y + 1);
        if (isLegal(captureMove2)) {
            legalMoves.insert({captureMove2, 1});
        }
    }

    if (!checkWhitePlayer() && (x + 1 < 8) && (y - 1 >= 0)) {
        Box captureMove3(x + 1, y - 1);
        if (isLegal(captureMove3)) {
            legalMoves.insert({captureMove3, 1});
        }
    }

    if (!checkWhitePlayer() && (x + 1 < 8) && (y + 1 < 8)) {
        Box captureMove4(x + 1, y + 1);
        if (isLegal(captureMove4)) {
            legalMoves.insert({captureMove4, 1});
        }
    }

    /* 
        Check if there was an en passant (capture) move added by different pawn (not attacking pawn).
        This is needed as we call updateLegalMoves() before every move attempted (check move() for more details).
        Thus, in order to not loose the en passant move added by a different pawn we must push it again to new 
        legalMoves array currently being constructed.
    */


    for (auto &pair: ((this->getLegalMoves()))) {
        // en passant move (-1) was found in PREVIOUS legalMovesArr and legalMoveStates
        if (pair.second == -1)  {
            // add en passant move to CURRENT legalMovesArr
            legalMoves.insert({pair.first, pair.second});
        }
    }

    // First move (2 spaces forward)
    if (checkWhitePlayer() && (x == 6) && !((*(this->getBoard()))[x - 2][y])) {
        Box initialMove1(x - 2, y);
        legalMoves.insert({initialMove1, 0});
        // En passant (Note that we need to delete the newly added move to the opposing pawn 
        // if it is not used immediately! - will be done in move())
        if ((y - 1 >= 0) && ((*(this->getBoard()))[x - 2][y - 1])) { // if there exists a piece on that specific [x-2][y-1] tile

            if (((*(this->getBoard()))[x - 2][y - 1])->getName() == "p") { // if the piece is a pawn
                Box opponentPawnMove1(x - 1, y);
                // adding en passient move
                ((((*(this->getBoard()))[x - 2][y - 1])->getLegalMoves())).insert({opponentPawnMove1, -1});
                
            }
        }

        if ((y + 1 < 8) && ((*(this->getBoard()))[x - 2][y + 1])) {

            if (((*(this->getBoard()))[x - 2][y + 1])->getName() == "p") { // if the piece is an opposing pawn
                Box opponentPawnMove2(x - 1, y);
                // adding en passient move
                ((((*(this->getBoard()))[x - 2][y + 1])->getLegalMoves())).insert({opponentPawnMove2, -1});
            }
        }
    }

    if (!checkWhitePlayer() && (x == 1) && !((*(this->getBoard()))[x + 2][y])) {
        Box initialMove2(x + 2, y);
        legalMoves.insert({initialMove2, 0});

        // En passant (Note that we need to delete the newly added move to the opposing pawn 
        // if it is not used immediately!)
        if ((y - 1 >= 0) && ((*(this->getBoard()))[x + 2][y - 1])) {

            if (((*(this->getBoard()))[x + 2][y - 1])->getName() == "P") {
                Box opponentPawnMove1(x + 1, y);
                // adding en passient move
                ((((*(this->getBoard()))[x + 2][y - 1])->getLegalMoves())).insert({opponentPawnMove1, -1});
            }

        }

        if ((y + 1 < 8) && ((*(this->getBoard()))[x + 2][y + 1])) {

            if (((*(this->getBoard()))[x + 2][y + 1])->getName() == "p") { // if the opposing piece is a pawn
              Box opponentPawnMove2(x + 1, y);  
                // adding en passient move
              ((((*(this->getBoard()))[x + 2][y + 1])->getLegalMoves())).insert({opponentPawnMove2, -1});
            }
        }
    }

    return legalMoves;
}
