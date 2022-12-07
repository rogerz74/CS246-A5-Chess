#include "king.h"
#include <algorithm>

King::King(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord):
    Piece{name, board, whitePlayer, xCoord, yCoord}, isFirstMove{true} {}

bool King::getIsFirstMove() {
    return isFirstMove;
}

void King::updateIsFirstMove() {
    isFirstMove = false;
}

bool King::isLegal(Box &targetBox) {
    // checks if targetBox is occupied and Piece is of opposite colour (in order to capture)
    if ((((*(this->getBoard()))[targetBox.getX()][targetBox.getY()]) && 
        ((checkWhitePlayer() && !(((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ||
         (!checkWhitePlayer() && (((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ) )) {
        return true;
    }
    return false;
}

std::map<Box, int> King::updateLegalMoves() {
    std::map<Box, int> legalMoves;

    int x = this->getX();
    int y = this->getY();

    // castling
    // checks if king is white, on it's first move, rook is at it's necessary position,and on it's first move
    if (checkWhitePlayer() && isFirstMove && ((*(this->getBoard()))[7][0]) &&
        ((*(this->getBoard()))[7][0])->getName() == "R" && ((*(this->getBoard()))[7][0])->getIsFirstMove()) {
            bool isPiece = false;
            // checks if there are Pieces between the King and Rook used
            for (int i = 1; y - i > 0 && !isPiece; ++i) {
                if ((*(this->getBoard()))[x][y - i]) {
                    isPiece = true;
                    break;
                }
            }
            
            if (!isPiece) {
                // checks if king is in check in current position, final position, and position in between 
                // (x, y), (x, y - 1), (x, y - 2)

                // current position
                ChessGame checkGame1(this->getBoard());
                checkGame1.checkingForKingCheck();

                // check current position is check
                if (!(checkGame1.isWhiteKingChecked())) {
                    Piece * tmp = (*(this->getBoard()))[x][y];
                    (*(checkGame1.getBoard()))[x][y - 1] = tmp;
                    (*(checkGame1.getBoard()))[x][y] = nullptr;
                    checkGame1.checkingForKingCheck();

                    // check between position is check
                    if (!(checkGame1.isWhiteKingChecked())) {
                        Piece * tmp2 = (*(this->getBoard()))[x][y-1];
                        (*(checkGame1.getBoard()))[x][y - 2] = tmp2;
                        (*(checkGame1.getBoard()))[x][y-1] = nullptr;
                        checkGame1.checkingForKingCheck();
                    
                        // check final position is check
                        if (!(checkGame1.isWhiteKingChecked())) {
                            // put board back into original state
                            (*(this->getBoard()))[x][y - 2] = nullptr;
                            (*(this->getBoard()))[x][y] = this;

                            // add castling move to King
                            Box castlingKingMove(x, y - 2);
                            legalMoves.insert({castlingKingMove, 2});

                            // add castling move to Rook
                            Box castlingRookMove(x, y - 1);
                            ((((*(this->getBoard()))[7][0])->getLegalMoves())).insert({castlingRookMove, 2});
                        }
                    }
                }
            }
    }

    // castling
    // checks if king is white, on it's first move, rook is at it's necessary position,and on it's first move

    if (checkWhitePlayer() && isFirstMove && ((*(this->getBoard()))[7][7]) &&
        ((*(this->getBoard()))[7][7])->getName() == "R" && ((*(this->getBoard()))[7][7])->getIsFirstMove()) {
            bool isPiece = false;
            // checks if there are Pieces between the King and Rook used
            for (int i = 1; y + i < 7 && !isPiece; ++i) {
                if ((*(this->getBoard()))[x][y + i]) {
                    isPiece = true;
                    break;
                }
            }

            if (!isPiece) {
                // checks if king is in check in current position, final position, and position in between 
                // (x, y), (x, y + 1), (x, y + 2)
                std::cout << "inside checking loop" <<std::endl;
                // current position
                ChessGame checkGame2(this->getBoard());
                checkGame2.checkingForKingCheck();

                // check current position is check
                if (!(checkGame2.isWhiteKingChecked())) {

                    Piece * tmp = (*(this->getBoard()))[x][y];
                    (*(checkGame2.getBoard()))[x][y + 1] = tmp;
                    (*(checkGame2.getBoard()))[x][y] = nullptr;
                    checkGame2.checkingForKingCheck();

                    // check between position is check
                    if (!(checkGame2.isWhiteKingChecked())) {

                        Piece * tmp2 = (*(this->getBoard()))[x][y+1];
                        (*(checkGame2.getBoard()))[x][y + 2] = tmp2;
                        (*(checkGame2.getBoard()))[x][y+1] = nullptr;
                        checkGame2.checkingForKingCheck();
                    
                        // check final position is check
                        if (!(checkGame2.isWhiteKingChecked())) {

                            (*(this->getBoard()))[x][y + 2] = nullptr;
                            (*(this->getBoard()))[x][y] = this;

                            // add castling move to King
                            Box castlingKingMove(x, y + 2);
                            std::cout << "Inserted right castling" << std::endl;
                            std::cout << legalMoves.size() << std::endl;
                            legalMoves.insert({castlingKingMove, 2});
                            std::cout << legalMoves.size() << std::endl;
                            // add castling move to Rook
                            Box castlingRookMove(x, y + 1);
                            ((((*(this->getBoard()))[7][7])->getLegalMoves())).insert({castlingRookMove, 2});
                        }
                    }
                }
            }
    }

    // castling black player
    // checks if king is black, on it's first move, rook is at it's necessary position,and on it's first move
    if (!checkWhitePlayer() && isFirstMove && ((*(this->getBoard()))[0][0]) &&
        ((*(this->getBoard()))[0][0])->getName() == "r" && ((*(this->getBoard()))[0][0])->getIsFirstMove()) {
            bool isPiece = false;
            // checks if there are Pieces between the King and Rook used
            for (int i = 1; y - i >= 0 && !isPiece; ++i) {
                if ((*(this->getBoard()))[x][y - i]) {
                    isPiece = true;
                    break;
                }
            }
            
            if (!isPiece) {
                // checks if king is in check in current position, final position, and position in between 
                // (x, y), (x, y + 1), (x, y + 2)

                // current position
                ChessGame checkGame3(this->getBoard());
                checkGame3.checkingForKingCheck();

                // check current position is check
                if (!(checkGame3.isBlackKingChecked())) {

                    Piece * tmp = (*(this->getBoard()))[x][y];
                    (*(checkGame3.getBoard()))[x][y - 1] = tmp;
                    (*(checkGame3.getBoard()))[x][y] = nullptr;
                    checkGame3.checkingForKingCheck();

                    // check between position is check
                    if (!(checkGame3.isBlackKingChecked())) {

                        Piece * tmp2 = (*(this->getBoard()))[x][y-1];
                        (*(checkGame3.getBoard()))[x][y - 2] = tmp2;
                        (*(checkGame3.getBoard()))[x][y-1] = nullptr;
                        checkGame3.checkingForKingCheck();
                    
                        // check final position is check
                        if (!(checkGame3.isBlackKingChecked())) {
                            // put board back into original state
                            (*(this->getBoard()))[x][y - 2] = nullptr;
                            (*(this->getBoard()))[x][y] = this;

                            // add castling move to King
                            Box castlingKingMove(x, y - 2);
                            legalMoves.insert({castlingKingMove, 2});

                            // add castling move to Rook
                            Box castlingRookMove(x, y - 1);
                            ((((*(this->getBoard()))[0][0])->getLegalMoves())).insert({castlingRookMove, 2});
                        }
                    }
                }
            }
    }

    // castling black player
    // checks if king is black, on it's first move, rook is at it's necessary position,and on it's first move
    if (!checkWhitePlayer() && isFirstMove && ((*(this->getBoard()))[0][7]) &&
        ((*(this->getBoard()))[0][7])->getName() == "r" && ((*(this->getBoard()))[0][7])->getIsFirstMove()) {
            bool isPiece = false;
            // checks if there are Pieces between the King and Rook used
            for (int i = 1; y + i < 7 && !isPiece; ++i) {
                if ((*(this->getBoard()))[x][y + i]) {
                    isPiece = true;
                    break;
                }
            }
            
            if (!isPiece) {
                // checks if king is in check in current position, final position, and position in between 
                // (x, y), (x, y + 1), (x, y + 2)

                // current position
                ChessGame checkGame4(this->getBoard());
                checkGame4.checkingForKingCheck();

                // check current position is check
                if (!(checkGame4.isBlackKingChecked())) {
                    Piece * tmp = (*(this->getBoard()))[x][y];
                    (*(checkGame4.getBoard()))[x][y + 1] = tmp;
                    (*(checkGame4.getBoard()))[x][y] = nullptr;
                    checkGame4.checkingForKingCheck();

                    // check between position is check
                    if (!(checkGame4.isBlackKingChecked())) {

                        Piece * tmp2 = (*(this->getBoard()))[x][y+1];
                        (*(checkGame4.getBoard()))[x][y + 2] = tmp2;
                        (*(checkGame4.getBoard()))[x][y+1] = nullptr;
                        checkGame4.checkingForKingCheck();
                    
                        // check final position is check
                        if (!(checkGame4.isBlackKingChecked())) {
                            // put board back into original state
                            (*(this->getBoard()))[x][y + 2] = nullptr;
                            (*(this->getBoard()))[x][y] = this;

                            // add castling move to King
                            Box castlingKingMove(x, y + 2);
                            legalMoves.insert({castlingKingMove, 2});

                            // add castling move to Rook
                            Box castlingRookMove(x, y + 1);
                            ((((*(this->getBoard()))[0][7])->getLegalMoves())).insert({castlingRookMove, 2});
                        }
                    }
                }
            }
    }

    // regular moves in 8 directions
    if (x - 1 >= 0) {
        Box move1(x - 1, y);
        if (isLegal(move1)) {
            legalMoves.insert({move1, 1});
        } else if (!((*(this->getBoard()))[move1.getX()][move1.getY()])) {
            legalMoves.insert({move1, 0});
        }
    }

    if (x + 1 < 8) {
        Box move2(x + 1, y);
        if (isLegal(move2)) {
            legalMoves.insert({move2, 1});
        } else if (!((*(this->getBoard()))[move2.getX()][move2.getY()])) {
            legalMoves.insert({move2, 0});
        }
    }

    if (y - 1 >= 0) {
        Box move3(x, y - 1);
        if (isLegal(move3)) {
            legalMoves.insert({move3, 1});
        } else if (!((*(this->getBoard()))[move3.getX()][move3.getY()])) {
            legalMoves.insert({move3, 0});
        }
    }

    if (y + 1 < 8) {
        Box move4(x, y + 1);
        if (isLegal(move4)) {
            legalMoves.insert({move4, 1});
        } else if (!((*(this->getBoard()))[move4.getX()][move4.getY()])) {
            legalMoves.insert({move4, 0});
        }
    }

    if ((x - 1 >= 0) && (y - 1 >= 0)) {
        Box move5(x - 1, y - 1);
        if (isLegal(move5)) {
            legalMoves.insert({move5, 1});
        } else if (!((*(this->getBoard()))[move5.getX()][move5.getY()])) {
            legalMoves.insert({move5, 0});
        }
    }

    if ((x + 1 < 8) && (y - 1 >= 0)) {
        Box move6(x + 1, y - 1);
        if (isLegal(move6)) {
            legalMoves.insert({move6, 1});
        } else if (!((*(this->getBoard()))[move6.getX()][move6.getY()])) {
            legalMoves.insert({move6, 0});
        }
    }

    if ((x - 1 >= 0) && (y + 1 < 8)) {
        Box move7(x - 1, y + 1);
        if (isLegal(move7)) {
            legalMoves.insert({move7, 1});
        } else if (!((*(this->getBoard()))[move7.getX()][move7.getY()])) {
            legalMoves.insert({move7, 0});
        }
    }

    if ((x + 1 < 8) && (y + 1 < 8)) {
        Box move8(x + 1, y + 1);
        if (isLegal(move8)) {
            legalMoves.insert({move8, 1});
        } else if (!((*(this->getBoard()))[move8.getX()][move8.getY()])) {
            legalMoves.insert({move8, 0});
        }
    }
    std::cout << legalMoves.size() << std::endl;
    return legalMoves;
}
