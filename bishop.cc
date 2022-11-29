#include "bishop.h"

Bishop::Bishop(std::string name, std::vector<std::vector<Box *>> &board, Box *box, bool whitePlayer):
    Piece{name, board, box, whitePlayer} {}

void Bishop::updateLegalMoves() {
    std::vector<Box*> legalMoves;

    int x = box->getX();
    int y = box->getY();

    // will break loop if there is an existing piece on a box
    // this is also why we need separate loops for each direction

    for (int i = 1; x - i >= 0 && y + i < 8; ++i) {
        if (board[x - i][y + i]->isOccupied()) {
            // if piece on box is capturable add to possible moves
            if ((checkWhitePlayer() && !(board[x - i][y + i]->getPiece()->checkWhitePlayer())) |
                (!checkWhitePlayer() && board[x - i][y + i]->getPiece()->checkWhitePlayer())) {
                legalMoves.push_back(board[x - i][y + i]);
            }
            break;
        }
        legalMoves.push_back(board[x - i][y + i]);
    }

    for (int i = 1; x + i  < 8 && y - i >= 0; ++i) {
        if (board[x + i][y - i]->isOccupied()) {
            if ((checkWhitePlayer() && !(board[x + i][y - i]->getPiece()->checkWhitePlayer())) |
                (!checkWhitePlayer() && board[x + i][y - i]->getPiece()->checkWhitePlayer())) {
                legalMoves.push_back(board[x + i][y - i]);
            }
            break;
        }
        legalMoves.push_back(board[x + i][y - i]);
    }

    for (int i = 1; x - i  >= 0 && y - i >= 0; ++i) {
        if (board[x - i][y - i]->isOccupied()) {
            if ((checkWhitePlayer() && !(board[x - i][y - i]->getPiece()->checkWhitePlayer())) |
                (!checkWhitePlayer() && board[x - i][y - i]->getPiece()->checkWhitePlayer())) {
                legalMoves.push_back(board[x - i][y - i]);
            }
            break;
        }
        legalMoves.push_back(board[x - i][y - i]);
    }

    for (int i = 1; x + i  < 8 && y + i < 8; ++i) {
        if (board[x + i][y + i]->isOccupied()) {
            if ((checkWhitePlayer() && !(board[x + i][y + i]->getPiece()->checkWhitePlayer())) |
                (!checkWhitePlayer() && board[x + i][y + i]->getPiece()->checkWhitePlayer())) {
                legalMoves.push_back(board[x + i][y + i]);
            }
            break;
        }
        legalMoves.push_back(board[x + i][y + i]);
    }

    this->legalMoves = legalMoves;

}
