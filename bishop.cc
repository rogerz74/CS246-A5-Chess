#include "bishop.h"

Bishop::Bishop(std::string name, std::vector<std::vector<Box *>> &board, Box *box, bool whitePlayer):
    Piece{name, board, box, whitePlayer} {}

bool Bishop::isLegal(Box *targetBox) {
    if ((checkWhitePlayer() && !(targetBox->getPiece()->checkWhitePlayer())) |
        (!checkWhitePlayer() && targetBox->getPiece()->checkWhitePlayer())) {

        return true;
    }
    return false;
}

void Bishop::updateLegalMoves() {
    std::vector<Box*> legalMoves;

    int x = box->getX();
    int y = box->getY();

    // will break loop if there is an existing piece on a box
    // this is also why we need separate loops for each direction

    for (int i = 1; x - i >= 0 && y + i < 8; ++i) {
        // if there exists a piece on box (break) and it is capturable add to possible moves
        if (board[x - i][y + i]->isOccupied()) {
            if(isLegal(board[x - i][y + i])) {
                legalMoves.push_back(board[x - i][y + i]);
            }
            break;
        }

        legalMoves.push_back(board[x - i][y + i]);
    }

    for (int i = 1; x + i  < 8 && y - i >= 0; ++i) {
        if (board[x + i][y - i]->isOccupied()) {
            if(isLegal(board[x + i][y - i])) {
                legalMoves.push_back(board[x + i][y - i]);
            }
            break;
        }

        legalMoves.push_back(board[x + i][y - i]);
    }

    for (int i = 1; x - i  >= 0 && y - i >= 0; ++i) {
        if (board[x - i][y - i]->isOccupied()) {
            if(isLegal(board[x - i][y - i])) {
                legalMoves.push_back(board[x - i][y - i]);
            }
            break;
        }
        legalMoves.push_back(board[x - i][y - i]);
    }

    for (int i = 1; x + i  < 8 && y + i < 8; ++i) {
        if (board[x + i][y + i]->isOccupied()) {
            if(isLegal(board[x + i][y + i])) {
                legalMoves.push_back(board[x + i][y + i]);
            }
            break;
        }
        legalMoves.push_back(board[x + i][y + i]);
    }

    this->legalMoves = legalMoves;

}
