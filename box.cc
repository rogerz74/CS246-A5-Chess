#include "box.h"
#include <iostream>

Box::Box(int xCoord, int yCoord, Piece *currentPiece): 
    xCoord{xCoord}, yCoord{yCoord}, currentPiece{currentPiece} {

    int isXOdd = xCoord % 2;
    int isYOdd = yCoord % 2;

    if ((isXOdd && !isYOdd) | (!isXOdd && isYOdd)) {
        isBlackTile = true;
    } else {
        isBlackTile =  false;
    }
}

int Box::getX() { 
    return xCoord; 
}

int Box::getY() {
    return yCoord;
}

Piece* Box::getPiece() {
    return currentPiece;
}

void Box::setPiece(Piece *currentPiece) {
    this->currentPiece = currentPiece;
}

bool Box::isOccupied() { 
    if (currentPiece == nullptr) {
        return false;
    }
    return true;
}

void Box::print() {
    if (isBlackTile && !isOccupied()) {
        std::cout << "_";
    } else if(!isBlackTile && !isOccupied()) {
        std::cout << " ";
    } else {
        std::cout << currentPiece->getName();
    }
}

Box::~Box() {
    delete currentPiece;
}
