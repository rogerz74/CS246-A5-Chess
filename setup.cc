#include "setup.h"
using namespace std;

/*
TO DO:
- Making required changes after box & piece ctors change.
*/

//Note: return type of ChessGame's getBoard() method is <vector<vector<Box *>> *.
string lowercase(string s);
int strToCoord(char c);

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
                Piece p{piece, setupGame->getBoard(), *(setupGame->getBoard())[strToCoord(place[1])][strToCoord(place[0])], wp};
                *(setupGame->getBoard())[strToCoord(place[1])][strToCoord(place[0])]->setPiece(&p);
                setupGame->updateKingPresence();
                setupGame->checkingForKingCheck();
                if (wp) {
                    wPieces.push_back(&p);   //adding the address of p to the vector
                } else {
                    bPieces.push_back(&p);
                }
            }
        } 
        
        else if (command == "-") {
            cin >> place;
            if (*(setupGame->getBoard())[strToCoord(place[1])][strToCoord(place[0])]->isOccupied()) {
                Piece * p = *(setupGame->getBoard())[strToCoord(place[1])][strToCoord(place[0])]->getPiece();
                if (p->checkWhitePlayer()) {
                    wPieces.erase(remove(wPieces.begin(), wPieces.end(), p), wPieces.end());
                } else {
                    bPieces.erase(remove(bPieces.begin(), bPieces.end(), p), bPieces.end());
                }
                *(setupGame->getBoard())[strToCoord(place[1])][strToCoord(place[0])]->setPiece(nullptr);
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
                setupGame->setTurn(true);
            } else if (turn == "black") {
                setupGame->setTurn(false);
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
    
    for (int i = 0; i < 8; i++) {
        Piece wOther{row1[i], setupGame->getBoard(), *(setupGame->getBoard())[7][i], 1};
        *(setupGame->getBoard())[7][i]->setPiece(&wOther);
        wPieces.push_back(&wOther);

        Piece wPawn{"P", setupGame->getBoard(), *(setupGame->getBoard())[6][i], 1};
        *(setupGame->getBoard())[6][i]->setPiece(&wPawn);
        wPieces.push_back(&wPawn);

        Piece bOther{lowercase(row1[i]), setupGame->getBoard(), *(setupGame->getBoard())[0][i], 0};
        *(setupGame->getBoard())[0][i]->setPiece(&bOther);
        bPieces.push_back(&bOther);

        Piece bPawn{"p", setupGame->getBoard(), *(setupGame->getBoard())[1][i], 0};
        *(setupGame->getBoard())[1][i]->setPiece(&bPawn);
        bPieces.push_back(&bPawn);
    }
}



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
