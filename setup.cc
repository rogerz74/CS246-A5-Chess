#include "setup.h"
using namespace std;

//Assumes return type of ChessGame's getBoard() method has been changed to <vector<vector<Box *>> &.
string lowercase(string s);
int strToCoord(char c);

void userSetup(ChessGame *setupGame, std::vector<Piece *> &wPieces, std::vector<Piece *> &bPieces) {       //void because it makes changes to the ChessGame itself
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
            if (((piece == "p") && (row == '1' || row == '8')) 
                || ((piece == "P") && (row == '1' || row == '8'))) {
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
                Piece p{piece, setupGame->getBoard(), setupGame->getBoard()[strToCoord(place[1])][strToCoord(place[0])], wp};
                setupGame->getBoard()[strToCoord(place[1])][strToCoord(place[0])]->setPiece(&p);

                //should update board's fields __KingPresent & __KingChecked but fields are private, and latter cannot 
                //be done in setup - maybe create ChessGame method kingStatus(), which updates with *every* piece placement/removal.

                if (wp) {
                    wPieces.push_back(&p);   //adding the adress of p to the vector
                } else {
                    bPieces.push_back(&p);
                }
            }
        } 
        
        else if (command == "-") {
            cin >> place;
            Piece * p = setupGame->getBoard()[strToCoord(place[1])][strToCoord(place[0])]->getPiece();
            if (p->checkWhitePlayer()) {
                wPieces.erase(std::remove(wPieces.begin(), wPieces.end(), p), wPieces.end());
            } else {
                bPieces.erase(std::remove(bPieces.begin(), bPieces.end(), p), bPieces.end());
            }
            setupGame->getBoard()[strToCoord(place[1])][strToCoord(place[0])]->setPiece(nullptr);

            //kingStatus() will be executed here again to check if king was removed, or a piece that protected
            //any of the kings from a check was removed.
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


/*  --IGNORE: IN PROGRESS - CREATES defaultBoard--
void defaultSetup(ChessGame *setupGame, std::vector<Piece *> &wPieces, std::vector<Piece *> &bPieces) {
    vector<string> row1{"R", "N", "B", "Q", "K", "B", "N", "R"};
    vector<string> row2(8, "P");
    
    for (auto piece : row1) {
        Piece p{piece, setupGame->getBoard(), setupGame->getBoard()[strToCoord(place[1])][strToCoord(place[0])], wp};
    }
    Piece p{piece, setupGame->getBoard(), setupGame->getBoard()[strToCoord(place[1])][strToCoord(place[0])], wp};
    setupGame->getBoard()[strToCoord(place[1])][strToCoord(place[0])]->setPiece(&p);
}
*/


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
