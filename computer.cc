#include <iostream>
#include "computer.h"

using namespace std;


Computer::Computer(ChessGame *subject, std::string name, std::vector<Piece*> * pieceArray, std::vector<Piece*> * oppArray): 
    subject{subject}, name{name}, pieceArray{pieceArray}, oppArray{oppArray} {
    subject->attach(this);
}

Computer::~Computer() {
    subject->detach(this);
}

std::string Computer::getName() {
    return name;
}

int Computer::pickMove() {

    // contains the 3 levels, 4th level not implemented

    if (name == "level1") {
        std::cout << "Level 1 Computer makes its move." << std::endl;
        std::vector<std::pair<Piece *, Box>> newMap;
        std::vector<Piece *> pieces = *pieceArray;
        int arraySize = pieces.size();

        std::cout << arraySize << std::endl;

        for (int i = 0; i < arraySize; i++) {       //looping through all the pieces
            std::map<Box, int> lm = ((pieces[i])->updateLegalMoves());
            for (auto &move: lm) {           
                //looping through all legal moves

                // if the current move is a capture we need to not loose the piece it will capture and bring it back after checking for king check
                if ((*(subject->getBoard()))[(move.first).getX()][(move.first).getY()]) {       //move is an iterator

                    //current piece on the board at the location wanting to move to
                    Piece *temp = (*(subject->getBoard()))[(move.first).getX()][(move.first).getY()]; 

                    (*(subject->getBoard()))[(move.first).getX()][(move.first).getY()] = (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()];
                    (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = temp;

                    subject->checkingForKingCheck();

                    // if my king is not in check after potential move is made -> add to newMap
                    if (((*(pieces[i])).checkWhitePlayer() && !(subject->isWhiteKingChecked())) || 
                        (!((*(pieces[i])).checkWhitePlayer()) && !(subject->isBlackKingChecked()))) {
                        newMap.emplace_back(pieces[i], move.first);
                    }

                    // put board back into original state
                    (*(subject->getBoard()))[(move.first).getX()][(move.first).getY()]->move(
                        (*(subject->getBoard()))[(move.first).getX()][(move.first).getY()], 
                        (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()], 
                        (*(pieces[i])).getX(), 
                        (*(pieces[i])).getY());

                    (*(subject->getBoard()))[(move.first).getX()][(move.first).getY()] = temp;

                } else {


                    (*(subject->getBoard()))[(move.first).getX()][(move.first).getY()] = (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()];
                    (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = nullptr;


                    subject->checkingForKingCheck();

                    // if my king is not in check after potential move is made
                    if (((*(pieces[i])).checkWhitePlayer() && !(subject->isWhiteKingChecked())) || 
                        (!((*(pieces[i])).checkWhitePlayer()) && !(subject->isBlackKingChecked()))) {
                        newMap.emplace_back(pieces[i], move.first);
                    }

                    (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = (*(subject->getBoard()))[(move.first).getX()][(move.first).getY()];
                    (*(subject->getBoard()))[(move.first).getX()][(move.first).getY()] = nullptr;


                }

                // put back isBlackKingChecked() and isWhiteKingChecked() to original state
                subject->checkingForKingCheck();                    

            }
        }

        int size = newMap.size();
        if (size == 0) {
            return 0;           //could be a stalemate or a checkmate
        }
    
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randompick(0, size-1); //picks random index in newMap
        std::vector<std::pair<Piece *, Box>>::iterator item = newMap.begin();                //iterator points to {Piece*:Box}
        std::advance( item, randompick(rng) );
        
        Piece *p = item->first;         //might have to change to item.first
        Box b = item->second;           //might have to change to item.second
        int bX = b.getX();
        int bY = b.getY();
        bool status = true;
        for (int a = 0; a < 8 && status == true; a++) {
            for (int b = 0; b < 8 && status == true; b ++) {
                if ((*(subject->getBoard()))[a][b]) {
                    if ((*(subject->getBoard()))[a][b]->getX() == p->getX() && (*(subject->getBoard()))[a][b]->getY() == p->getY()) {
                        (*(subject->getBoard()))[a][b]->move((*(subject->getBoard()))[a][b], (*(subject->getBoard()))[bX][bY], bX, bY );
                    }  
                }

            }
        }

        //at this point, a move has certainly been made with elements of newMap.
        //we need to update every piece's legal moves.

        //the color's own pieces
        for (int i = 0; i < arraySize; i++) {       //looping through all the pieces
            (pieces[i])->setLegalMoves((pieces[i])->updateLegalMoves());
        }

        //opponent's pieces
        std::vector<Piece *> oppPieces = *oppArray;
        int oppArraySize = oppPieces.size();
        for (int j = 0; j < oppArraySize; j++) {       //looping through all the pieces
            (oppPieces[j])->setLegalMoves((oppPieces[j])->updateLegalMoves());
        }

        // check for pawn promotion
        if (p) {
            int aX = p->getX();
            int aY = p->getY();
            if ((((*(subject->getBoard()))[aX][aY])->getName() == "P" && ((*(subject->getBoard()))[aX][aY])->getX() == 0) || 
                (((*(subject->getBoard()))[aX][aY])->getName() == "p" && ((*(subject->getBoard()))[aX][aY])->getX() == 7)) {
                promotePawn(((*(subject->getBoard()))[aX][aY]));
            }  
        }
        

        return 1;



    } else if (name == "level2") { // LEVEL 2
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
        std::vector<Piece *> oppPieces = *oppArray;
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



    } else { // LEVEL 3

        int size = 0;
        std::cout << "Level 3 Computer makes its move." << std::endl;
        std::vector<std::pair<Piece *, Box>> filteredMap; // moves that are purely legal (doesn't put my king in check) and avoid capture
        std::vector<std::pair<Piece *, Box>> filteredMap2; // moves that are purely legal (doesn't put my king in check) and capture or checks
        std::vector<std::pair<Piece *, Box>> regularMap; // moves that are purely legal (doesn't put my king in check) and are not special (just a move)
        std::vector<Box> toAvoid;
        std::vector<Piece*> pieces = *pieceArray;
        std::vector<Piece*> opponentPieces = *oppArray;
        int arraySize = pieces.size();
        int opponentArraySize = opponentPieces.size();

        // looping through all of opponent's pieces
        for (int i = 0; i < opponentArraySize; ++i) {
            std::map<Box, int> opponentsLegalMoves = ((*(opponentPieces[i])).getLegalMoves());
            
            // loop through the piece's legal moves
            for (auto &move: opponentsLegalMoves) { 
                // if opponent has a capture move add it to toAvoid (places to avoid) 
                if (move.second == 1) {
                    toAvoid.push_back(move.first);
                }
            }
        }

        // checking is a move puts my king in check
        for (int i = 0; i < arraySize; ++i) {
            std::map<Box, int> potentialMoves = (((*(pieces[i])).getLegalMoves()));
            for (auto &move: potentialMoves) { 

                // create temporary pieces that will be moved around and then deleted
                Piece *tempPiece;
                if (((*pieces[i])).getName() == "p" || (*(pieces[i])).getName() == "P") {
                    tempPiece = new Pawn {(*(pieces[i])).getName(), subject->getBoard(), (*(pieces[i])).checkWhitePlayer(), (*(pieces[i])).getX(), (*(pieces[i])).getY()};
                } else if ((*(pieces[i])).getName() == "r" || (*(pieces[i])).getName() == "R") {
                    tempPiece = new Rook {(*(pieces[i])).getName(), subject->getBoard(), (*(pieces[i])).checkWhitePlayer(), (*(pieces[i])).getX(), (*(pieces[i])).getY()};  
                } else if ((*(pieces[i])).getName() == "q" || (*(pieces[i])).getName() == "Q") {
                    tempPiece = new Queen {(*(pieces[i])).getName(), subject->getBoard(), (*(pieces[i])).checkWhitePlayer(), (*(pieces[i])).getX(), (*(pieces[i])).getY()};
                } else if ((*(pieces[i])).getName() == "k" || (*(pieces[i])).getName() == "K") {
                    tempPiece = new King {(*(pieces[i])).getName(), subject->getBoard(), (*(pieces[i])).checkWhitePlayer(), (*(pieces[i])).getX(), (*(pieces[i])).getY()};             
                } else if ((*(pieces[i])).getName() == "n" || (*(pieces[i])).getName() == "N") {
                    tempPiece = new Knight {(*(pieces[i])).getName(), subject->getBoard(), (*(pieces[i])).checkWhitePlayer(), (*(pieces[i])).getX(), (*(pieces[i])).getY()};               
                } else {
                    tempPiece = new Bishop {(*(pieces[i])).getName(), subject->getBoard(), (*(pieces[i])).checkWhitePlayer(), (*(pieces[i])).getX(), (*(pieces[i])).getY()};          
                }
                tempPiece->setLegalMoves(tempPiece->updateLegalMoves());

                // if the current move is a capture we need to not loose the piece it will capture and bring it back after checking for king check
                if ((*(subject->getBoard()))[(move.first).getX()][(move.first).getY()]) {
                    Piece *temp = (*(subject->getBoard()))[(move.first).getX()][(move.first).getY()];
                    (*(subject->getBoard()))[(move.first).getX()][(move.first).getX()] = tempPiece;
                    (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = nullptr;
                    subject->checkingForKingCheck();

                    // if my king is not in check after potential move is made -> add to respective maps
                    if (((*(pieces[i])).checkWhitePlayer() && !(subject->isWhiteKingChecked())) || 
                        (!((*(pieces[i])).checkWhitePlayer()) && !(subject->isBlackKingChecked()))) {

                            if (find(toAvoid.begin(), toAvoid.end(), move.first) == toAvoid.end()) {
                                // move makes current piece captured
                                filteredMap.emplace_back(pieces[i], move.first);
                            }else if (move.second == 1 ||
                                ((*(pieces[i])).checkWhitePlayer() && subject->isBlackKingChecked()) ||
                                (!((*(pieces[i])).checkWhitePlayer()) && subject->isWhiteKingChecked())) {
                                    // move is a captures opposing piece or checks opposing king
                                    // need to put these in one check or else it may add the move twice
                                    filteredMap2.emplace_back(pieces[i], move.first);
                            } else {
                                regularMap.emplace_back(pieces[i], move.first);
                            }
                    }

                    // put board back into original state
                    (*(subject->getBoard()))[(move.first).getX()][(move.first).getX()] = temp;
                    (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = &(*(pieces[i]));

                } else {
                    (*(subject->getBoard()))[(move.first).getX()][(move.first).getX()] = tempPiece;
                    (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = nullptr;
                    subject->checkingForKingCheck();

                    // if my king is not in check after potential move is made -> add to according filtered map
                    if (((*(pieces[i])).checkWhitePlayer() && !(subject->isWhiteKingChecked())) || 
                        (!((*(pieces[i])).checkWhitePlayer()) && !(subject->isBlackKingChecked()))) {

                            if (find(toAvoid.begin(), toAvoid.end(), move.first) == toAvoid.end()) {
                                // move makes current piece captured
                                filteredMap.emplace_back(pieces[i], move.first);
                            } else if (move.second == 1 ||
                                ((*(pieces[i])).checkWhitePlayer() && subject->isBlackKingChecked()) ||
                                (!((*(pieces[i])).checkWhitePlayer()) && subject->isWhiteKingChecked())) {
                                    // move is a captures opposing piece or checks opposing king
                                    // need to put these in one check or else it may add the move twice
                                    filteredMap2.emplace_back(pieces[i], move.first);
                            } else {
                                regularMap.emplace_back(pieces[i], move.first);
                            }
                    }
                    
                    // put board back into original state
                    (*(subject->getBoard()))[(move.first).getX()][(move.first).getX()] = nullptr;
                    (*(subject->getBoard()))[(*(pieces[i])).getX()][(*(pieces[i])).getY()] = &(*(pieces[i]));
                }

                // put back isBlackKingChecked() and isWhiteKingChecked() to original state
                subject->checkingForKingCheck();                    
                        
                delete tempPiece;
        }
    }


    // Will now pick a move

    if (filteredMap.size() > 0) {
        // randomly pick a move that avoids capture
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randompick(0, size - 1); //picks random index in filteredMap
        auto item = filteredMap.begin();                //iterator points to {Piece*:Box}
        std::advance(item, randompick(rng));
        Piece *p = item->first;
        Box b = item->second;   
        int bX = b.getX();
        int bY = b.getY();

        p->move(p, (*(subject->getBoard()))[bX][bY], bX, bY);

        if ((p->getName() == "P" && p->getX() == 0) || (p->getName() == "p" && p->getX() == 7)) {
            promotePawn(p);
        }

    } else if (filteredMap2.size() > 0) {
        // there are no moves to avoid caputre so we randomly pick a capture or check
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randompick(0, size - 1); //picks random index in filteredMap
        auto item = filteredMap2.begin();                //iterator points to {Piece*:Box}
        std::advance(item, randompick(rng));
        Piece *p = item->first;
        Box b = item->second;   
        int bX = b.getX();
        int bY = b.getY();

        p->move(p, (*(subject->getBoard()))[bX][bY], bX, bY);

        if ((p->getName() == "P" && p->getX() == 0) || (p->getName() == "p" && p->getX() == 7)) {
            promotePawn(p);
        }
        
    } else if (regularMap.size() > 0) {
        // there are no moves to avoid caputre, capture, or check - so we randomly pick a regular move
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randompick(0, size - 1); //picks random index in filteredMap
        auto item = regularMap.begin();                //iterator points to {Piece*:Box}
        std::advance(item, randompick(rng));
        Piece *p = item->first;
        Box b = item->second;   
        int bX = b.getX();
        int bY = b.getY();

        p->move(p, (*(subject->getBoard()))[bX][bY], bX, bY);

        if ((p->getName() == "P" && p->getX() == 0) || (p->getName() == "p" && p->getX() == 7)) {
            promotePawn(p);
        }

    } else {
        // no legal moves
        // stalemate or checkmate
        return 0;
    }

    //the color's own pieces
    for (int i = 0; i < arraySize; i++) {       //looping through all the pieces
        (pieces[i])->setLegalMoves((pieces[i])->updateLegalMoves());
    }

    //opponent's pieces
    std::vector<Piece *> oppPieces = *oppArray;
    int oppArraySize = oppPieces.size();
    for (int j = 0; j < oppArraySize; j++) {       //looping through all the pieces
        (oppPieces[j])->setLegalMoves((oppPieces[j])->updateLegalMoves());
    }

    return 1;
    }
 }



void Computer::notify() {

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

}

void Computer::promotePawn(Piece * p) {
    Piece *pawnPromoPiece;
    if (p->getName() == "P" && p->getX() == 0) {
        pawnPromoPiece = new Queen {"Q", subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
        pawnPromoPiece->setLegalMoves(pawnPromoPiece->updateLegalMoves());
    }  else if (p->getName() == "p" && p->getX() == 7) {
        pawnPromoPiece = new Queen {"q", subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
        pawnPromoPiece->setLegalMoves(pawnPromoPiece->updateLegalMoves());
    }

    // look for pawn and delete it
    pieceArray->erase(find(pieceArray->begin(), pieceArray->end(), p));

    // add queen to vector and board
    pieceArray->emplace_back(pawnPromoPiece);
    (*(subject->getBoard()))[p->getX()][p->getY()] = pawnPromoPiece;

    delete p;
}
