#include "level1.h"

Level1::Level1(ChessGame *subject, std::string name, std::vector<Piece *> *pieceArray, std::vector<Piece *> *opponentArray):
                Computer{subject, name, pieceArray, opponentArray} {}

int Level1::pickMove() {
    std::cout << "Level 1 Computer makes its move." << std::endl;
    std::map<Piece *, Box> newMap;
    std::vector<Piece *> pieces = *pieceArray;
    int arraySize = pieces.size();

    for (int i = 0; i < arraySize; i++) {       //looping through all the pieces
        std::map<Box, int> lm = *((pieces[i])->getlegalMoves());
        for (auto &move: lm) {                     //looping through all legal moves
            Piece *tempPiece;
            if ((pieces[i])->getName() == "p" || (pieces[i])->getName() == "P") {
                tempPiece = new Pawn {(pieces[i])->getName(), subject->getBoard(), (pieces[i])->checkWhitePlayer(), (pieces[i])->getX(), (pieces[i])->getY()};
            } else if ((pieces[i])->getName() == "r" || (pieces[i])->getName() == "R") {
                tempPiece = new Rook {(pieces[i])->getName(), subject->getBoard(), (pieces[i])->checkWhitePlayer(), (pieces[i])->getX(), (pieces[i])->getY()};
            } else if ((pieces[i])->getName() == "q" || (pieces[i])->getName() == "Q") {
                tempPiece = new Queen {(pieces[i])->getName(), subject->getBoard(), (pieces[i])->checkWhitePlayer(), (pieces[i])->getX(), (pieces[i])->getY()};
            } else if ((pieces[i])->getName() == "k" || (pieces[i])->getName() == "K") {
                tempPiece = new King {(pieces[i])->getName(), subject->getBoard(), (pieces[i])->checkWhitePlayer(), (pieces[i])->getX(), (pieces[i])->getY()};
            } else if ((pieces[i])->getName() == "n" || (pieces[i])->getName() == "N") {
                tempPiece = new Knight {(pieces[i])->getName(), subject->getBoard(), (pieces[i])->checkWhitePlayer(), (pieces[i])->getX(), (pieces[i])->getY()};
            } else {
                tempPiece = new Bishop {(pieces[i])->getName(), subject->getBoard(), (pieces[i])->checkWhitePlayer(), (pieces[i])->getX(), (pieces[i])->getY()};
            }

            // if the current move is a capture we need to not loose the piece it will capture and bring it back after checking for king check
            if ((*(subject->getBoard()))[(move.first).getX()][(move.first).getY()]) {       //move is an iterator
                Piece *temp = (*(subject->getBoard()))[(move.first).getX()][(move.first).getY()];
                (*(subject->getBoard()))[(move.first).getX()][(move.first).getX()] = tempPiece;
                (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = nullptr;
                subject->checkingForKingCheck();

                // if my king is not in check after potential move is made -> add to newMap
                if (((*(pieces[i])).checkWhitePlayer() && !(subject->isWhiteKingChecked())) || 
                    (!((*(pieces[i])).checkWhitePlayer()) && !(subject->isBlackKingChecked()))) {
                    newMap.insert({pieces[i], move.first});
                }

                // put board back into original state
                (*(subject->getBoard()))[(move.first).getX()][(move.first).getX()] = temp;
                (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = pieces[i];

            } else {
                (*(subject->getBoard()))[(move.first).getX()][(move.first).getX()] = tempPiece;
                (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = nullptr;
                subject->checkingForKingCheck();

                // if my king is not in check after potential move is made
                if (((*(pieces[i])).checkWhitePlayer() && !(subject->isWhiteKingChecked())) || 
                    (!((*(pieces[i])).checkWhitePlayer()) && !(subject->isBlackKingChecked()))) {
                    newMap.insert({pieces[i], move.first});
                }

                // put board back into original state
                (*(subject->getBoard()))[(move.first).getX()][(move.first).getX()] = nullptr;
                (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = pieces[i];
            }

            // put back isBlackKingChecked() and isWhiteKingChecked() to original state
            subject->checkingForKingCheck();                    
            delete tempPiece;
        }
    }

    int size = newMap.size();
    if (size == 0) {
        return 0;           //could be a stalemate or a checkmate
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randompick(0, size-1); //picks random index in newMap
    std::map<Piece *, Box> iterator item = newMap.begin();                //iterator points to {Piece*:Box}
    std::advance( item, randompick(rng) );
    
    Piece *p = item->first;         //might have to change to item.first
    Box b = item->second;           //might have to change to item.second
    int bX = b.getX();
    int bY = b.getY();

    p->move(p, (*(gameBoard->getBoard()))[bX][bY], bX, bY);
    return 1;
}
