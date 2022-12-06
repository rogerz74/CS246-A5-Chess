#include "piece.h"
#include <algorithm>
#include <iostream>
#include "box.h"

Piece::Piece(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, const int xCoord, const int yCoord):
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


void Piece::move(Piece *currentTile, Piece *targetTile, int newX, int newY) {

    // currentTile = the location of the current piece
    // targetTile = the location of where the piece wants to move (nullptr if empty, Piece if occupied)

    /*
    
    This updateLegalMoves() is moved here b/c when the chessGame is first constructed, you can't call on virtual void functions
    in the constructor. Hence, the initial setup of pieces all don't an array of legal moves. Thus, it is imperative that before
    each move, a new list of legal moves is obtained.

    */

    std::map<Box, int> tempLegalMovesMap = updateLegalMoves();
    legalMovesMap = tempLegalMovesMap;

    const Box targetBox(newX, newY);

    if (targetTile) { // if there is a piece on it
        targetTile = nullptr;
        std::swap(currentTile, targetTile); // b/c a piece is captured, that Piece * on the grid points to NULL and the actual gets deleted

    } else { // if the tile is empty
        std::swap(currentTile, targetTile);
    }

    // check if move was a King castling move
    if (targetTile->getName() == "K" && (legalMovesMap)[targetBox] == 2) {
        // to find which rook we are moving towards
        if (yCoord - newY > 0) {
            for (auto &pair: (((*board)[7][0]->getLegalMoves()))) {
                if (pair.second == 2) {
                    std::swap((*board)[7][0], (*board)[pair.first.getX()][pair.first.getY()]);
                    (*board)[pair.first.getX()][pair.first.getY()]->xCoord = pair.first.getX();
                    (*board)[pair.first.getX()][pair.first.getY()]->yCoord = pair.first.getY();
                }
            }
        } else {
            for (auto &pair: (((*board)[7][7]->getLegalMoves()))) {
                if (pair.second == 2) {
                    std::swap((*board)[7][7], (*board)[pair.first.getX()][pair.first.getY()]);
                    (*board)[pair.first.getX()][pair.first.getY()]->xCoord = pair.first.getX();
                    (*board)[pair.first.getX()][pair.first.getY()]->yCoord = pair.first.getY();
                }
            }
        }

    } else if (targetTile->getName() == "k" && (legalMovesMap)[targetBox] == 2) {
        // to find which rook we are moving towards
        if (yCoord - newY > 0) {
            for (auto &pair: (((*board)[0][0]->getLegalMoves()))) {
                if (pair.second == 2) {
                    std::swap((*board)[0][0], (*board)[pair.first.getX()][pair.first.getY()]);
                    (*board)[pair.first.getX()][pair.first.getY()]->xCoord = pair.first.getX();
                    (*board)[pair.first.getX()][pair.first.getY()]->yCoord = pair.first.getY();
                }
            }
        } else {
            for (auto &pair: (((*board)[0][7]->getLegalMoves()))) {
                if (pair.second == 2) {
                    std::swap((*board)[0][7], (*board)[pair.first.getX()][pair.first.getY()]);
                    (*board)[pair.first.getX()][pair.first.getY()]->xCoord = pair.first.getX();
                    (*board)[pair.first.getX()][pair.first.getY()]->yCoord = pair.first.getY();
                }
            }
        }
    }

    xCoord = newX;
    yCoord = newY;

    // check if piece is a pawn
    if (targetTile->getName() == "P" || targetTile->getName() == "p") {
            
        // check there is an en passant move in legalMovesMap
        for (auto &pair: (legalMovesMap)) {
            if (pair.second == -1) {
                // en passant move (-1) was found
                // delete en passant move from legalMovesArr and legalMoveStates
                legalMovesMap.erase(pair.first);
            }
        }
    }

    // update isFirstMove (applicable for king and rook)
    if (targetTile->getName() == "K" || targetTile->getName() == "k" || 
        targetTile->getName() == "R" || targetTile->getName() == "r") {
            targetTile->updateIsFirstMove();
    }

    std::map<Box, int> tempLegalMovesMap2 = updateLegalMoves();
    legalMovesMap = tempLegalMovesMap2;

}

