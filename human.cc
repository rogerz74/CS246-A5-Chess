#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include "human.h"
#include "chessGame.h"
#include "pawn.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"

Human::Human(ChessGame *subject, std::string name, std::vector<Piece*> *pieceArray, std::vector<Piece*> * opponentArray):
                subject{subject}, name{name}, pieceArray{pieceArray}, opponentArray{opponentArray} { subject->attach(this); }

Human::~Human() {
    subject->detach(this);
}

// helper function
int stringToCoord(char c) {
    if (c == 'a' || c == '8') {
        return 0;
    } else if (c == 'b' || c == '7') {
        return 1;
    } else if (c == 'c' || c == '6') {
        return 2;
    } else if (c == 'd' || c == '5') {
        return 3;
    } else if (c == 'e' || c == '4') {
        return 4;
    } else if (c == 'f' || c == '3') {
        return 5;
    } else if (c == 'g' || c == '2') {
        return 6;
    } else {
        return 7;
    }
}

bool Human::promotePawn(Piece * p, std::string promoName) {

    Piece *pawnPromoPiece;
    if (p->getName() == "P") {
        if (promoName == "R") {
            pawnPromoPiece = new Rook {promoName, subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};  
            pawnPromoPiece->setLegalMoves(pawnPromoPiece->updateLegalMoves());
        } else if (promoName == "Q") {
            pawnPromoPiece = new Queen {promoName, subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
            pawnPromoPiece->setLegalMoves(pawnPromoPiece->updateLegalMoves());
        } else if (promoName == "N") {
            pawnPromoPiece = new Knight {promoName, subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
            pawnPromoPiece->setLegalMoves(pawnPromoPiece->updateLegalMoves());               
        } else if (promoName == "B") {
            pawnPromoPiece = new Bishop {promoName, subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
            pawnPromoPiece->setLegalMoves(pawnPromoPiece->updateLegalMoves());          
        } else {
            return 0;
        }
    } else {
        if (promoName == "r") {
            pawnPromoPiece = new Rook {promoName, subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
            pawnPromoPiece->setLegalMoves(pawnPromoPiece->updateLegalMoves());  
        } else if (promoName == "q") {
            pawnPromoPiece = new Queen {promoName, subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
            pawnPromoPiece->setLegalMoves(pawnPromoPiece->updateLegalMoves());
        } else if (promoName == "n") {
            pawnPromoPiece = new Knight {promoName, subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
            pawnPromoPiece->setLegalMoves(pawnPromoPiece->updateLegalMoves());               
        } else if (promoName == "b") {
            pawnPromoPiece = new Bishop {promoName, subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
            pawnPromoPiece->setLegalMoves(pawnPromoPiece->updateLegalMoves());          
        } else {
            return 0;
        }
    }

    // add promotion piece to vector and board
    pieceArray->emplace_back(pawnPromoPiece);
    (*(subject->getBoard()))[p->getX()][p->getY()] = pawnPromoPiece;

    // look for pawn and delete it
    pieceArray->erase(find(pieceArray->begin(), pieceArray->end(), p));

    delete p;
    return 1;
}

int Human::pickMove() {
    
    std::string comm;
    while (std::cin >> comm) {
        if (comm == "move") {
            std::string a;
            std::string b;
            std::string promotionP;
            std::string line;

            // cin input for a, b, and promotionP, if there is an input for prompotionP
            while (std::getline(std::cin, line)) {

                std::istringstream ss1{ line };
                ss1 >> a;
                ss1 >> b;
                if (!(ss1 >> promotionP)) {
                    promotionP = " ";
                }
                break;
            }

            int aX = stringToCoord(a[1]);
            int aY = stringToCoord(a[0]);
            int bX = stringToCoord(b[1]);
            int bY = stringToCoord(b[0]);
            std::map<Box, Piece *> filteredMap;
            std::map<Box, int> currLegalMoves = (((*(subject->getBoard()))[aX][aY])->updateLegalMoves());

            // loop through the piece's legal moves
            for (auto &move: currLegalMoves) { 

                // if move does not put player's King in check, add to filteredMap
                // temp so we do not loose the current piece we are trying to move
                Piece *currPiece = (*(subject->getBoard()))[aX][aY];
                
                // create temporary piece that will be moved around and then get deleted
                Piece *tempPiece;
                if (currPiece->getName() == "p" || currPiece->getName() == "P") {
                    tempPiece = new Pawn {currPiece->getName(), subject->getBoard(), currPiece->checkWhitePlayer(), currPiece->getX(), currPiece->getY()};
                } else if (currPiece->getName() == "r" || currPiece->getName() == "R") {
                    tempPiece = new Rook {currPiece->getName(), subject->getBoard(), currPiece->checkWhitePlayer(), currPiece->getX(), currPiece->getY()};  
                } else if (currPiece->getName() == "q" || currPiece->getName() == "Q") {
                    tempPiece = new Queen {currPiece->getName(), subject->getBoard(), currPiece->checkWhitePlayer(), currPiece->getX(), currPiece->getY()};
                } else if (currPiece->getName() == "k" || currPiece->getName() == "K") {
                    tempPiece = new King {currPiece->getName(), subject->getBoard(), currPiece->checkWhitePlayer(), currPiece->getX(), currPiece->getY()};             
                } else if (currPiece->getName() == "n" || currPiece->getName() == "N") {
                    tempPiece = new Knight {currPiece->getName(), subject->getBoard(), currPiece->checkWhitePlayer(), currPiece->getX(), currPiece->getY()};               
                } else {
                    tempPiece = new Bishop {currPiece->getName(), subject->getBoard(), currPiece->checkWhitePlayer(), currPiece->getX(), currPiece->getY()};          
                }
                tempPiece->setLegalMoves(tempPiece->updateLegalMoves());

                // if the current move is a capture we need to not loose the piece it will capture and bring it back after checking for king check
                if ((*(subject->getBoard()))[move.first.getX()][move.first.getY()]) {
                    Piece *temp = (*(subject->getBoard()))[move.first.getX()][move.first.getY()];
                    (*(subject->getBoard()))[move.first.getX()][move.first.getY()] = tempPiece;
                    (*(subject->getBoard()))[aX][aY] = nullptr;
                    subject->checkingForKingCheck();

                    // if my king is not in check after potential move is made -> add to filteredMap
                    if ((currPiece->checkWhitePlayer() && !(subject->isWhiteKingChecked())) || 
                        (!(currPiece->checkWhitePlayer()) && !(subject->isBlackKingChecked()))) {
                            filteredMap.insert({move.first, currPiece});
                    }

                    // put board back into original state
                    (*(subject->getBoard()))[aX][aY] = currPiece;
                    (*(subject->getBoard()))[move.first.getX()][move.first.getY()] = temp;

                } else { // move is NOT A CAPTURE

                    (*(subject->getBoard()))[move.first.getX()][move.first.getY()] = tempPiece;
                    (*(subject->getBoard()))[aX][aY] = nullptr;
                    subject->checkingForKingCheck();

                    // if my king is not in check after potential move is made -> add to filteredMap
                    if ((currPiece->checkWhitePlayer() && !(subject->isWhiteKingChecked())) || 
                        (!(currPiece->checkWhitePlayer()) && !(subject->isBlackKingChecked()))) {
                            filteredMap.insert({move.first, currPiece});
                    }

                    // put board back into original state
                    (*(subject->getBoard()))[aX][aY] = currPiece;
                    (*(subject->getBoard()))[move.first.getX()][move.first.getY()] = nullptr;
                }

                // put back isBlackKingChecked() and isWhiteKingChecked() to original state
                subject->checkingForKingCheck();

                delete tempPiece;
            }

            // check if "stalemate"
            if (filteredMap.size() == 0) {
                return 0;
            } else {
                bool state = false;
                int legalMoveValuation; //the int value associated with the particular legal move
                for (auto i: filteredMap) {
                    if (i.first.getX() == bX && i.first.getY() == bY) {
                        state = true;

                        for (auto m: currLegalMoves) { //finding the int value associated with the particular legal move
                            if (m.first.getX() == bX && m.first.getY() == bY ) {
                                legalMoveValuation = m.second;
                                break;
                            }
                        }
                         
                        break;
                    }
                }

                // check if move given by user is in filteredMap
                if (state) { // need to find if the moveBox is possible or not
                    // move the piece
                    (*(subject->getBoard()))[aX][aY]->move((*(subject->getBoard()))[aX][aY], (*(subject->getBoard()))[bX][bY], bX, bY);
                    
                    if (legalMoveValuation == 2 && aX == 7 && bY == aY + 2) { // White Castling to the Right, Move Rook
                        (*(subject->getBoard()))[7][7]->move((*(subject->getBoard()))[7][7], (*(subject->getBoard()))[ bX ][ bY-1], bX, bY - 1);
                    } else if (legalMoveValuation == 2 && aX == 7 && bY == aY - 2) {
                        (*(subject->getBoard()))[7][0]->move((*(subject->getBoard()))[7][0], (*(subject->getBoard()))[ bX ][ bY+1], bX, bY + 1);
                    } else if (legalMoveValuation == 2 && aX == 0 && bY == aY + 2) {
                        (*(subject->getBoard()))[0][7]->move((*(subject->getBoard()))[0][7], (*(subject->getBoard()))[ bX ][ bY-1], bX, bY - 1);
                    } else if (legalMoveValuation == 2 && aX == 0 && bY == aY - 2) {
                        (*(subject->getBoard()))[0][0]->move((*(subject->getBoard()))[0][0], (*(subject->getBoard()))[ bX ][ bY+1], bX, bY + 1);
                    }

                    for (int a = 0; a < 8; a++) {
                        for (int b = 0; b < 8; b ++) {
                            if ((*(subject->getBoard()))[a][b]) {
                                (*(subject->getBoard()))[a][b]->setLegalMoves(((*(subject->getBoard()))[a][b])->updateLegalMoves());
                            }

                        }
                    }

                    // check for pawn promotion
                    if ((((*(subject->getBoard()))[bX][bY])->getName() == "P" && ((*(subject->getBoard()))[bX][bY])->getX() == 0) || 
                        (((*(subject->getBoard()))[bX][bY])->getName() == "p" && ((*(subject->getBoard()))[bX][bY])->getX() == 7)) {
                            if (promotePawn((*(subject->getBoard()))[aX][aY], promotionP) == 0) {
                                std::cout << "Invalid promotion piece! Please try again: "; 
                            } else {
                                return 1;
                            }
                    } else {
                        return 1;
                    }
                } else {
                    for (int a = 0; a < 8; a++) {
                        for (int b = 0; b < 8; b ++) {
                            if ((*(subject->getBoard()))[a][b]) {
                                (*(subject->getBoard()))[a][b]->setLegalMoves(((*(subject->getBoard()))[a][b])->updateLegalMoves());
                            }

                        }
                    }
                    std::cout << "Invalid move! Please try again: ";
                }
            }

        } else if (comm == "resign") {
            return -1;
        } else {
            std::cout << "Invalid command! Please try again: ";
        }
    }
    return -9999; // return if user decides to Cmd D on their turn, resulting in an incomplete game
}


void Human::notify() {

    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 9; b++) {
            if (b == 0) {
                std::cout << (8-a) << " "; // printing the left-hand side row value
            } else {
                // we will NEED TO ADD A print() function to Box Class to print either a piece, a Black tile (_) or a white tile ( )
                if ((*(subject->getBoard()))[a][b-1]) {
                    std::cout << (*(subject->getBoard()))[a][b-1]->getName();
                } else { // printing black or white
                    int val1 = a % 2;
                    int val2 = b % 2;

                    if (!val1 && !val2) {
                        std::cout << "_";
                    } else if (val1 == 1 && val2 == 1) {
                        std::cout << "_";
                    } else {
                        std::cout << " ";
                    }
                }

            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "  abcdefgh" << std::endl; // printing the bottom a-h column value
    std::cout << std::endl;

}
