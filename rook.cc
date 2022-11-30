#include "rook.h"

Rook::Rook(std::string name, std::vector<std::vector<Box *>> *board, Box *box, bool whitePlayer):
    Piece{name, board, box, whitePlayer} {}

bool Rook::isLegal(Box *targetBox) {
    if ((checkWhitePlayer() && !(targetBox->getPiece()->checkWhitePlayer())) ||
        (!checkWhitePlayer() && targetBox->getPiece()->checkWhitePlayer())) {

        return true;
    }
    return false;
}

void Rook::updateLegalMoves() {
    std::vector<Box*> legalMoves;

    int x = box->getX();
    int y = box->getY();

    // will break loop if there is an existing piece on a box
    // this is also why we need separate loops for each direction

    for (int i = x - 1; i >= 0; --i) {
        // if there exists a piece on box (break) and it is capturable add to possible moves
        if ((*board)[i][y]->isOccupied()) {
            if(isLegal((*board)[i][y])) {
                legalMoves.push_back((*board)[i][y]);
            }
            break;
        }
        legalMoves.push_back((*board)[i][y]);
    }

    for (int i = x + 1; i < 8; ++i) {
        if ((*board)[i][y]->isOccupied()) {
            if(isLegal((*board)[i][y])) {
                legalMoves.push_back((*board)[i][y]);
            }
            break;
        }
        legalMoves.push_back((*board)[i][y]);
    }

    for (int i = y + 1; i < 8; ++i) {
        if ((*board)[x][i]->isOccupied()) {
            if(isLegal((*board)[x][i])) {
                legalMoves.push_back((*board)[x][i]);
            }
            break;
        }
        legalMoves.push_back((*board)[x][i]);
    }

    for (int i = y - 1; i >= 0; --i) {
        if ((*board)[x][i]->isOccupied()) {
            if(isLegal((*board)[x][i])) {
                legalMoves.push_back((*board)[x][i]);
            }
            break;
        }
        legalMoves.push_back((*board)[x][i]);
    }

    this->legalMoves = legalMoves;
}
