#include "setup.h"
#include <algorithm>
using namespace std;


//Note: return type of ChessGame's getBoard() method is <vector<vector<Piece *>> *.
string lowercase(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int strToCoord(char c) {
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

void userSetup(ChessGame *setupGame, vector<Piece *> &wPieces, vector<Piece *> &bPieces) {       //void because it makes changes to the ChessGame itself

    bool condFlag = 0;

    string command = "";
    while (condFlag == 0) {
        string piece = "";
        string place = "";
        string turn =  "";
        cin >> command;

        if (command == "+") {

            cin >> piece >> place;
            char row = place[1];
            if ((piece == "p" || piece == "P") && (row == '1' || row == '8')) {
                cout << "Cannot place pawns on first or last row of the board." << endl;
            } else if ((piece == "K") && (setupGame->isWhiteKingPresent())) {
                cout << "White King already placed!" << endl;
            } else if ((piece == "k") && (setupGame->isBlackKingPresent())) {
                cout << "Black King already placed!" << endl;
            } else {
                bool wp = 1;
                if (islower(piece[0])) {
                    wp = 0;
                }

                // setting up each individual piece
                if (piece == "p" || piece == "P") {

                    Pawn * p = new Pawn {piece, setupGame->getBoard(), wp, strToCoord(place[1]), strToCoord(place[0])};
                    //p->setLegalMoves(p->updateLegalMoves());

                    if (wp) {
                        wPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = wPieces.back();
                    } else {
                        bPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = bPieces.back();
                    } 
                } else if (piece == "r" || piece == "R") {
                    Rook * p = new Rook {piece, setupGame->getBoard(), wp, strToCoord(place[1]), strToCoord(place[0])};
                    //p->setLegalMoves(p->updateLegalMoves());

                    if (wp) {
                        wPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = wPieces.back();
                    } else {
                        bPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = bPieces.back();
                    }
                } else if (piece == "q" || piece == "Q") {
                    Queen * p = new Queen {piece, setupGame->getBoard(), wp, strToCoord(place[1]), strToCoord(place[0])};
                    //p->setLegalMoves(p->updateLegalMoves());

                    if (wp) {
                        wPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = wPieces.back();
                    } else {
                        bPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = bPieces.back();
                    } 
                } else if (piece == "k" || piece == "K") {
                    King * p = new King {piece, setupGame->getBoard(), wp, strToCoord(place[1]), strToCoord(place[0])};
                    //p->setLegalMoves(p->updateLegalMoves());

                    if (wp) {
                        wPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = wPieces.back();
                    } else {
                        bPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = bPieces.back();
                    }                     
                } else if (piece == "n" || piece == "N") {
                    Knight * p = new Knight {piece, setupGame->getBoard(), wp, strToCoord(place[1]), strToCoord(place[0])};
                    //p->setLegalMoves(p->updateLegalMoves());

                    if (wp) {
                        wPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = wPieces.back();
                    } else {
                        bPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = bPieces.back();
                    }                     
                } else if (piece == "b" || piece == "B") {
                    Bishop * p = new Bishop {piece, setupGame->getBoard(), wp, strToCoord(place[1]), strToCoord(place[0])};
                    //p->setLegalMoves(p->updateLegalMoves());

                    if (wp) {
                        wPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = wPieces.back();
                    } else {
                        bPieces.emplace_back(p);   //adding p to the vector
                        (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = bPieces.back();
                    }                     
                }

                int wSize = wPieces.size();
                int bSize = bPieces.size();
                //white pieces
                for (int i = 0; i < wSize; i++) {       //looping through all the pieces
                    (wPieces[i])->setLegalMoves((wPieces[i])->updateLegalMoves());
                }
                //black pieces
                for (int j = 0; j < bSize; j++) {       //looping through all the pieces
                    (bPieces[j])->setLegalMoves((bPieces[j])->updateLegalMoves());
                }

                setupGame->updateKingPresence();
                setupGame->checkingForKingCheck();
            }
        } 
        
        else if (command == "-") {
            cin >> place;
            // setup - needs fixing
            Piece * p = (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])];
            if (p) {
                if (p->checkWhitePlayer()) {
                    auto it = find(wPieces.begin(), wPieces.end(), p);
                    if (it != wPieces.end()) {
                        int index = it - wPieces.begin();
                        delete wPieces[index];
                    }

                } else {
                    auto it = find(bPieces.begin(), bPieces.end(), p);
                    if (it != bPieces.end()) {
                        int index = it - bPieces.begin();
                        delete bPieces[index];
                    }
                }
                (*(setupGame->getBoard()))[strToCoord(place[1])][strToCoord(place[0])] = nullptr;

                int wSize = wPieces.size();
                int bSize = bPieces.size();
                //white pieces
                for (int i = 0; i < wSize; i++) {       //looping through all the pieces
                    (wPieces[i])->setLegalMoves((wPieces[i])->updateLegalMoves());
                }
                //black pieces
                for (int j = 0; j < bSize; j++) {       //looping through all the pieces
                    (bPieces[j])->setLegalMoves((bPieces[j])->updateLegalMoves());
                }
                setupGame->updateKingPresence();
                setupGame->checkingForKingCheck();

            } else {
                cout << "There is no piece on the chosen tile! Try again!" << endl;
            } 
        } 
        
        else if (command == "=") {
            cin >> turn;
            turn = lowercase(turn);
            if (turn == "white") {
                setupGame->setTurn(1);
            } else if (turn == "black") {
                setupGame->setTurn(0);
            } else {
                cout << "Invalid color!" << endl;
            }
        } 
        
        else if (command == "done") {
            if ((setupGame->isWhiteKingPresent()) && (setupGame->isBlackKingPresent())
                && !(setupGame->isWhiteKingChecked()) && !(setupGame->isWhiteKingChecked())) {
                condFlag = 1;
            } else {
                if (!(setupGame->isWhiteKingPresent())) {
                    cout << "White King missing! ";
                } else if (!(setupGame->isBlackKingPresent())) {
                    cout << "Black King missing! ";
                } else if (setupGame->isWhiteKingChecked()) {
                    cout << "White King in check! ";
                } else if (setupGame->isBlackKingChecked()) {
                    cout << "Black King in check! ";
                }
                cout << "Cannot finish set-up!" << endl;
            }
        } 
        
        else {
            cout << "Invalid command! Please try again." << endl;
        }
    }
}



void defaultSetup(ChessGame *setupGame, vector<Piece *> &wPieces, vector<Piece *> &bPieces) {

    vector<string> row1{"R", "N", "B", "Q", "K", "B", "N", "R"};
    int wSize = 16;
    int bSize = 16;
    
    // setting up the pawns initially
    for (int i = 0; i < 8; i++) {

        // setting up the PAWNS for both sides
        Pawn * p1 = new Pawn {"P", setupGame->getBoard(), 1, 6, i};
        p1->setLegalMoves(p1->updateLegalMoves());
        wPieces.emplace_back(p1);
        (*(setupGame->getBoard()))[6][i] = wPieces.back();
        
        Pawn * p2 = new Pawn {"p", setupGame->getBoard(), 0, 1, i};
        p2->setLegalMoves(p2->updateLegalMoves());
        bPieces.emplace_back(p2);
        (*(setupGame->getBoard()))[1][i] = bPieces.back();

    
        // setting up the other white pieces
        if (row1[i] == "R") {
            Rook * tmp = new Rook {row1[i], setupGame->getBoard(), 1, 7, i};
            tmp->setLegalMoves(tmp->updateLegalMoves());
            wPieces.emplace_back(tmp);
            (*(setupGame->getBoard()))[7][i] = wPieces.back();
        } else if (row1[i] == "N") {
            Knight * tmp = new Knight {row1[i], setupGame->getBoard(), 1, 7, i};
            tmp->setLegalMoves(tmp->updateLegalMoves());
            wPieces.emplace_back(tmp);
            (*(setupGame->getBoard()))[7][i] = wPieces.back();
        } else if (row1[i] == "B") {
            Bishop * tmp = new Bishop {row1[i], setupGame->getBoard(), 1, 7, i};
            tmp->setLegalMoves(tmp->updateLegalMoves());
            wPieces.emplace_back(tmp);
            (*(setupGame->getBoard()))[7][i] = wPieces.back();            
        } else if (row1[i] == "Q") {
            Queen * tmp = new Queen {row1[i], setupGame->getBoard(), 1, 7, i};
            tmp->setLegalMoves(tmp->updateLegalMoves());
            wPieces.emplace_back(tmp);
            (*(setupGame->getBoard()))[7][i] = wPieces.back();                  
        } else if (row1[i] == "K") {
            King * tmp = new King {row1[i], setupGame->getBoard(), 1, 7, i};
            tmp->setLegalMoves(tmp->updateLegalMoves());
            wPieces.emplace_back(tmp);
            (*(setupGame->getBoard()))[7][i] = wPieces.back();                  
        }

        //setting up the other black pieces
        if (lowercase(row1[i]) == "r") {
            Rook * tmp = new Rook {lowercase(row1[i]), setupGame->getBoard(), 0, 0, i};
            tmp->setLegalMoves(tmp->updateLegalMoves());
            bPieces.emplace_back(tmp);
            (*(setupGame->getBoard()))[0][i] = bPieces.back();            
        } else if (lowercase(row1[i]) == "n") {
            Knight * tmp = new Knight {lowercase(row1[i]), setupGame->getBoard(), 0, 0, i};
            tmp->setLegalMoves(tmp->updateLegalMoves());
            bPieces.emplace_back(tmp);
            (*(setupGame->getBoard()))[0][i] = bPieces.back();             
        } else if (lowercase(row1[i]) == "b") {
            Bishop * tmp = new Bishop {lowercase(row1[i]), setupGame->getBoard(), 0, 0, i};
            tmp->setLegalMoves(tmp->updateLegalMoves());
            bPieces.emplace_back(tmp);
            (*(setupGame->getBoard()))[0][i] = bPieces.back();               
        } else if (lowercase(row1[i]) == "q") {
            Queen * tmp = new Queen {lowercase(row1[i]), setupGame->getBoard(), 0, 0, i};
            tmp->setLegalMoves(tmp->updateLegalMoves());
            bPieces.emplace_back(tmp);
            (*(setupGame->getBoard()))[0][i] = bPieces.back();               
        } else if (lowercase(row1[i]) == "k") {
            King * tmp = new King {lowercase(row1[i]), setupGame->getBoard(), 0, 0, i};
            tmp->setLegalMoves(tmp->updateLegalMoves());
            bPieces.emplace_back(tmp);
            (*(setupGame->getBoard()))[0][i] = bPieces.back();               
        }

    }
    //white pieces
    for (int i = 0; i < wSize; i++) {       //looping through all the pieces
        (wPieces[i])->setLegalMoves((wPieces[i])->updateLegalMoves());
    }
    //black pieces
    for (int j = 0; j < bSize; j++) {       //looping through all the pieces
        (bPieces[j])->setLegalMoves((bPieces[j])->updateLegalMoves());
    }
}
