#include "piece.h"
#include <algorithm>

Piece::Piece(std::string name, std::vector<std::vector<Box *>> &board, Box *box, bool whitePlayer):
    name{name}, board{board}, box{box}, whitePlayer{whitePlayer}, captured{false} {
        updateLegalMoves();
    };

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
    if (find(legalMoves.begin(),legalMoves.end(), targetBox) != legalMoves.end()) {
        if (targetBox->getPiece() != nullptr) {
        targetBox->getPiece()->captured = true;
        }

        targetBox->setPiece(box->getPiece());
        box->setPiece(nullptr);
        box = targetBox;
        updateLegalMoves();
        return 1;
    }

    return 0;
}

Piece::~Piece() {
    delete box;
}
