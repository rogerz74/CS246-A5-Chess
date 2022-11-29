#include "chessGame.h"
#include "subject.h"
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include <iostream>
#include <string>

// The void draw() function and the isStalemate() function is missing. These will be implemented when we have
// a better understanding on how we want to create these functions.


void ChessGame::setTurn(bool playerTurn) {
    this.playerTurn = playerTurn; // true = white, false = black !!
}

bool ChessGame::getPlayerTurn() {
    return playerTurn;
};

void ChessGame::switchTurn() {
    playerTurn = !playerTurn;
};