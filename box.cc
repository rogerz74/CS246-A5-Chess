#include "box.h"

Box::Box(int xCoord, int yCoord, Piece *currentPiece): 
    xCoord{xCoord}, yCoord{yCoord}, currentPiece{currentPiece} {}

int Box::getX() { 
    return xCoord; 
}

int Box::getY() {
    return yCoord;
}

Piece* Box::getPiece() {
    return currentPiece;
}

Piece* Box::setPiece(Piece *currentPiece) {
    this->currentPiece = currentPiece;
}

bool Box::blackTile() {
    int isXOdd = xCoord % 2;
    int isYOdd = yCoord % 2;

    if ((isXOdd && !isYOdd) | (!isXOdd && isYOdd)) {
        return true;
    }
    
    return false;
}

bool Box::isOccupied() { 
    if (currentPiece == nullptr) {
        return false;
    }
    return true;
}

Box::~Box() {
    delete currentPiece;
}
