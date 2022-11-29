#include "chessGame.h"
#include "subject.h"
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "box.h"
#include "piece.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// The void draw() function and the isStalemate() function is missing. These will be implemented when we have
// a better understanding on how we want to create these functions.

void ChessGame::setBoard(std::vector< vector <Box*>> & targetBoard) {
    board = targetBoard;
}

void ChessGame::setTurn(bool playerTurn) {
    this.playerTurn = playerTurn; // true = white, false = black !!
}

bool ChessGame::getPlayerTurn() {
    return playerTurn;
};

void ChessGame::switchTurn() {
    playerTurn = !playerTurn;
};

void ChessGame::updateKingPresence() {
    blackKingPresent = false;
    whiteKingPresent = false;
    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            if (board[a][b]->getPiece()->getName() == "k") {
                blackKingPresent = true;
            } else if (board[a][b]->getPiece()->getName() == "K") {
                whiteKingPresent = true;
            }
        }
    }
};

void ChessGame::checkingForKingCheck() {

    int blackKingX = -1;
    int blackKingY = -1;
    int whiteKingX = -1;
    int whiteKingY = -1;

    // finding the position of the kings
    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            if (board[a][b]->getPiece()->getName() == "k") {
                blackKingX = board[a][b]->getX();
                blackKingY = board[a][b]->getY();
            } else if (board[a][b]->getPiece()->getName() == "K") {
                whiteKingX = board[a][b]->getX();
                whiteKingY = board[a][b]->getY();
            }
        }
    }

    whiteKingChecked = false;
    blackKingChecked = false;
    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            // getting size of legalMoves
            int moveSize = static_cast<int>(board[a][b]->getPiece()->getLegalMoves().size());

            // checking the legal moves and seeing if they lead to a check
            for (int c = 0; c < moveSize; c++) {
                // if blackKing is in check by a white piece
                if (blackKingX != -1 &&
                    blackKingY != -1 &&
                    board[a][b]->getPiece()->getLegalMoves()[c]->getX() == blackKingX &&
                    board[a][b]->getPiece()->getLegalMoves()[c]->getY() == blackKingY &&
                    board[a][b]->getPiece()->getLegalMoves()[c]->getPiece()->checkWhitePlayer()) {
                        blackKingChecked = true;

                // if whiteKing is in check by a black piece
                } else if (whiteKingX != -1 &&
                            whiteKingY != -1 &&
                            board[a][b]->getPiece()->getLegalMoves()[c]->getX() == whiteKingX &&
                            board[a][b]->getPiece()->getLegalMoves()[c]->getY() == whiteKingY &&
                            !(board[a][b]->getPiece()->getLegalMoves()[c]->getPiece()->checkWhitePlayer())) {
                        whiteKingChecked = true;
                }

                // breaks out of loop b/c there's no need to contiune checking if both kings are in check
                if (whiteKingChecked && blackKingChecked) {
                    break;
                }
            }

            if (whiteKingChecked && blackKingChecked) {
                break;
            }
        }
    }
};