#include "piece.h"
#include <algorithm>
#include <iostream>
#include "box.h"

Piece::Piece(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, const int& xCoord, const int& yCoord):
    name{name}, board{board}, whitePlayer{whitePlayer}, xCoord{xCoord}, yCoord{yCoord} {};

int Piece::getX() {
    return xCoord;
}

int Piece::getY() {
    return yCoord;
}

std::string Piece::getName() {
    return name;
}

bool Piece::checkWhitePlayer() {
    return whitePlayer;
}

void Piece::print() {
    std::cout << name;
}

int Piece::move(Piece *currentTile, Piece *targetTile, int newX, int newY) {

    // currentTile = the location of the current piece
    // targetTile = the location of where the piece wants to move (nullptr if empty, Piece if occupied)

    /*
    
    This updateLegalMoves() is moved here b/c when the chessGame is first constructed, you can't call on virtual void functions
    in the constructor. Hence, the initial setup of pieces all don't an array of legal moves. Thus, it is imperative that before
    each move, a new list of legal moves is obtained.

    */

    updateLegalMoves();

    const Box targetBox(newX, newY);

    if (std::find(legalMovesArr->begin(),legalMovesArr->end(), targetBox) != legalMovesArr->end()) {
        if (targetTile) { // if there is a piece on it
            targetTile = nullptr;
            std::swap(currentTile, targetTile); // b/c a piece is captured, that Piece * on the grid points to NULL and the actual gets deleted

        } else { // if the tile is empty
            std::swap(currentTile, targetTile);
        }

        xCoord = newX;
        yCoord = newY;

        updateLegalMoves();
        return 1;
    }

    return 0;
}

Piece::~Piece() {}
