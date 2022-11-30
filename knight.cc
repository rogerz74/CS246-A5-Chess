#include "knight.h"

Knight::Knight(std::string name, std::vector<std::vector<Box *>> *board, Box *box, bool whitePlayer):
    Piece{name, board, box, whitePlayer} {}

bool Knight::isLegal(Box *targetBox) {
    if (!(targetBox->isOccupied()) || 
        (targetBox->isOccupied() && 
        (checkWhitePlayer() && !(targetBox->getPiece()->checkWhitePlayer())) ||
        (!checkWhitePlayer() && targetBox->getPiece()->checkWhitePlayer()))) {

        return true;
    }
    return false;
}

void Knight::updateLegalMoves() {
    std::vector<Box*> legalMoves;

    int x = box->getX();
    int y = box->getY();

    // if move is capturable (opposite colour) or if box is unoccupied then add to possible moves

    if (isLegal((*board)[x + 2][y + 1])) {
        legalMoves.push_back((*board)[x + 2][y + 1]);
    }

    if (isLegal((*board)[x - 2][y - 1])) {
        legalMoves.push_back((*board)[x - 2][y - 1]);
    }

    if (isLegal((*board)[x + 2][y - 1])) {
        legalMoves.push_back((*board)[x + 2][y - 1]);
    }

    if (isLegal((*board)[x - 2][y + 1])) {
        legalMoves.push_back((*board)[x - 2][y + 1]);
    }
    
    if (isLegal((*board)[x + 1][y + 2])) {
        legalMoves.push_back((*board)[x + 1][y + 2]);
    }

    if (isLegal((*board)[x - 1][y - 2])) {
        legalMoves.push_back((*board)[x - 1][y - 2]);
    }

    if (isLegal((*board)[x + 1][y - 2])) {
        legalMoves.push_back((*board)[x + 1][y - 2]);
    }

    if (isLegal((*board)[x - 1][y + 2])) {
        legalMoves.push_back((*board)[x - 1][y + 2]);
    }      

    this->legalMoves = legalMoves;
}
