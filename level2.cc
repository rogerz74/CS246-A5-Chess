#include "level2.h"
/*
Level2::Level2(ChessGame *subject, std::string name, std::vector<Piece *> *pieceArray, std::vector<Piece *> *opponentArray):
                Computer{subject, name, pieceArray, opponentArray} {}


int Level2::pickMove() {
    std::cout << "Level 2 Computer makes its move." << std::endl;
    std::vector<std::pair<Piece *, Box>> newMap;
    std::vector<std::pair<Piece *, Box>> filteredMap;
    std::vector<Piece *> pieces = *pieceArray;
    int arraySize = pieces.size();

    for (int i = 0; i < arraySize; i++) {       //looping through all the pieces
        std::map<Box, int> lm = ((pieces[i])->getLegalMoves());

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
            tempPiece->setLegalMoves(tempPiece->updateLegalMoves());

            // if the current move is a capture we need to not loose the piece it will capture and bring it back after checking for king check
            if ((*(subject->getBoard()))[(move.first).getX()][(move.first).getY()]) {       //move is an iterator
                Piece *temp = (*(subject->getBoard()))[(move.first).getX()][(move.first).getY()];
                (*(subject->getBoard()))[(move.first).getX()][(move.first).getX()] = tempPiece;
                (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = nullptr;
                subject->checkingForKingCheck();

                // if my king is not in check after potential move is made -> add to newMap
                if (((*(pieces[i])).checkWhitePlayer() && !(subject->isWhiteKingChecked())) || 
                    (!((*(pieces[i])).checkWhitePlayer()) && !(subject->isBlackKingChecked()))) {
                    newMap.emplace_back(pieces[i], move.first);
                    if (move.second == 1 ||
                        ((*(pieces[i])).checkWhitePlayer() && subject->isBlackKingChecked()) ||
                        (!((*(pieces[i])).checkWhitePlayer()) && subject->isWhiteKingChecked())) {
                        // move is a captures opposing piece or checks opposing king
                        // need to put these in one check or else it may add the move twice
                        filteredMap.emplace_back(pieces[i], move.first);
                    }
                }

                // put board back into original state
                (*(subject->getBoard()))[(move.first).getX()][(move.first).getX()] = temp;
                (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = pieces[i];

            } else {
                (*(subject->getBoard()))[(move.first).getX()][(move.first).getX()] = tempPiece;
                (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = nullptr;
                subject->checkingForKingCheck();

                // if my king is not in check after potential move is made -> add to according filtered map
                if (((*(pieces[i])).checkWhitePlayer() && !(subject->isWhiteKingChecked())) || 
                    (!((*(pieces[i])).checkWhitePlayer()) && !(subject->isBlackKingChecked()))) {
                    newMap.emplace_back(pieces[i], move.first);
                    if (move.second == 1 ||
                        ((*(pieces[i])).checkWhitePlayer() && subject->isBlackKingChecked()) ||
                        (!((*(pieces[i])).checkWhitePlayer()) && subject->isWhiteKingChecked())) {
                        // move is a captures opposing piece or checks opposing king
                        // need to put these in one check or else it may add the move twice
                        filteredMap.emplace_back(pieces[i], move.first);
                    }
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


    int newSize = newMap.size();
    if (newSize == 0) {
        return 0;           //could be a stalemate or a checkmate
    }

    int filterSize = filteredMap.size();
    Piece *p;
    if (filterSize == 0) {                //choosing random move from newMap

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randompick(0, newSize-1); //picks random index in newMap
        std::vector<std::pair<Piece *, Box>>::iterator item = newMap.begin();                //iterator points to {Piece*:Box}
        std::advance( item, randompick(rng) );
        
        p = item->first;
        Box b = item->second;
        int bX = b.getX();
        int bY = b.getY();
        p->move(p, (*(subject->getBoard()))[bX][bY], bX, bY);

    } else {                                                //selecting random element from filteredMap

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randompick(0, filterSize-1); //picks random index in filteredMap
        std::vector<std::pair<Piece *, Box>>::iterator item = filteredMap.begin();                //iterator points to {Piece*:Box}
        std::advance( item, randompick(rng) );
        
        p = item->first;
        Box b = item->second;   
        int bX = b.getX();
        int bY = b.getY();
        p->move(p, (*(subject->getBoard()))[bX][bY], bX, bY);

    }
  
    //at this point, a move has certainly been made, either with elements of newMap or filteredMap.
    //we need to update every piece's legal moves.

    //the color's own pieces
    //the color's own pieces
    for (int i = 0; i < arraySize; i++) {       //looping through all the pieces
        (pieces[i])->setLegalMoves((pieces[i])->updateLegalMoves());
    }

    //opponent's pieces
    std::vector<Piece *> oppPieces = *opponentArray;
    int oppArraySize = oppPieces.size();
    for (int j = 0; j < oppArraySize; j++) {       //looping through all the pieces
        (oppPieces[j])->setLegalMoves((oppPieces[j])->updateLegalMoves());
    }
    
    // check for pawn promotion
    int aX = p->getX();
    int aY = p->getY();
    if ((((*(subject->getBoard()))[aX][aY])->getName() == "P" && ((*(subject->getBoard()))[aX][aY])->getX() == 0) || 
        (((*(subject->getBoard()))[aX][aY])->getName() == "p" && ((*(subject->getBoard()))[aX][aY])->getX() == 7)) {
        promotePawn(((*(subject->getBoard()))[aX][aY]));
    }
    return 1;
}
*/