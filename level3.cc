#include "level3.h"

Level3::Level3(ChessGame *subject, std::string name, std::vector<Piece*> *pieceArray, std::vector<Piece*> *oppArray):
                Computer{subject, name, pieceArray, oppArray} {}

int Level3::pickMove() {
    int size = 0;
    std::cout << "Level 3 Computer makes its move." << std::endl;
    std::map<Piece *, Box> filteredMap; // moves that are purely legal (doesn't put my king in check) and avoid capture
    std::map<Piece *, Box> filteredMap2; // moves that are purely legal (doesn't put my king in check) and capture or checks
    std::map<Piece *, Box> regularMap; // moves that are purely legal (doesn't put my king in check) and are not special (just a move)
    std::vector<Box> toAvoid;
    std::vector<Piece*> pieces = *pieceArray;
    std::vector<Piece*> opponentPieces = *oppArray;
    int arraySize = pieces.size();
    int opponentArraySize = opponentPieces.size();

    // looping through all of opponent's pieces
    for (int i = 0; i < opponentArraySize; ++i) {
        std::map<Box, int> opponentsLegalMoves = (*(*(opponentPieces[i])).getLegalMoves());
        
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
        std::map<Box, int> potentialMoves = (*((*(pieces[i])).getLegalMoves()));
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
                            filteredMap.insert({pieces[i], move.first});
                        }else if (move.second == 1 ||
                            ((*(pieces[i])).checkWhitePlayer() && subject->isBlackKingChecked()) ||
                            (!((*(pieces[i])).checkWhitePlayer()) && subject->isWhiteKingChecked())) {
                                // move is a captures opposing piece or checks opposing king
                                // need to put these in one check or else it may add the move twice
                                filteredMap2.insert({pieces[i], move.first});
                        } else {
                            regularMap.insert({pieces[i], move.first});
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
                            filteredMap.insert({pieces[i], move.first});
                        } else if (move.second == 1 ||
                            ((*(pieces[i])).checkWhitePlayer() && subject->isBlackKingChecked()) ||
                            (!((*(pieces[i])).checkWhitePlayer()) && subject->isWhiteKingChecked())) {
                                // move is a captures opposing piece or checks opposing king
                                // need to put these in one check or else it may add the move twice
                                 filteredMap2.insert({pieces[i], move.first});
                        } else {
                            regularMap.insert({pieces[i], move.first});
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
            promotePawn(subject, pieceArray, p);
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
            promotePawn(subject, pieceArray, p);
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
            promotePawn(subject, pieceArray, p);
        }

    } else {
        // no legal moves
        // stalemate or checkmate
        return 0;
    }

    return 1;
}
