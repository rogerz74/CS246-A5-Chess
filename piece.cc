#include "piece.h"

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

void Piece::move(Box *targetBox) {
    if (targetBox->getPiece() != nullptr) {
        targetBox->getPiece()->captured = true;
    }

    targetBox->setPiece(box->getPiece());
    box->setPiece(nullptr);
    box = targetBox;
}

Piece::~Piece() {
    delete box;
}
