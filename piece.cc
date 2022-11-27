#include "piece.h"
#include <algorithm>

Piece::Piece(std::string name, std::vector<std::vector<Box *>> board, Box *box, bool whitePlayer):
    name{name}, board{board}, box{box}, whitePlayer{whitePlayer}, captured{false} {};

std::string Piece::getName() {
    return name;
}

bool Piece::checkWhitePlayer() {
    return whitePlayer;
}

bool Piece::isCaptured() {
    return captured;
}

int Piece::move(Box *targetBox) {
    std::vector<Box *> pMoves = possibleMoves();
    if (find(pMoves.begin(),pMoves.end(), targetBox) != pMoves.end() && isLegal(targetBox)) {
        if (targetBox->getPiece() != nullptr) {
        targetBox->getPiece()->captured = true;
        }

        targetBox->setPiece(box->getPiece());
        box->setPiece(nullptr);
        box = targetBox;
        return 1;
    }

    return 0;
}

Piece::~Piece() {
    delete box;
}
