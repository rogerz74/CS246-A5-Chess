#include "gamerun.h"
using namespace std;

int gameRun(Observer *white, Observer *black, ChessGame *gameBoard) {
    int turn = gameBoard->getPlayerTurn();
    int toReturn = INT_MAX;
    string comm = "";
    string a = "";
    string b = "";

    white->notify();

    //implement error checking so INT_MAX returned if game unfinished
    //for status, resigned = -1, stalemate = 0, all good = 1
    while (toReturn == INT_MAX) {
        if (turn == 1) {
            cout << "White's Turn: ";
            int status = white->pickMove();       //pickMove() will have int return type
            if (status == -1) {                    //never executed with compcomp
                toReturn = -1;                     //i.e. Black wins
            } else if (status == 0) {     //isStalemate() is not a thing anymore
                if (gameBoard->isWhiteKingChecked() == 1) {
                    toReturn = -1;              //no legal moves remaining + checked
                    cout << "No move available due to Checkmate!" << endl;
                } else {
                    toReturn = 0;               //no legal moves remaining
                    cout << "No move available due to Stalemate!" << endl;
                }
            } else if (status == 1) {                            //status is just 1
                white->notify();
                gameBoard->switchTurn();
                turn = gameBoard->getPlayerTurn();
            } else {
                toReturn = -9999; //return code for incomplete game
            }
        } else {
            cout << "Black's Turn: ";
            int status  = black->pickMove();
            if (status == -1) {                 //if black resigns
                toReturn = 1;                   //White wins
            } else if (status == 0) {           //no legal moves left
                 if (gameBoard->isBlackKingChecked() == 1) {
                    toReturn = 1;               //checkmate
                    cout << "No move available due to Checkmate!" << endl;
                } else {
                    toReturn = 0;               //stalemate
                    cout << "No move available due to Stalemate!" << endl;
                }
            } else if (status == 1) {
                black->notify();
                gameBoard->switchTurn();
                turn = gameBoard->getPlayerTurn();
            } else {
                toReturn = -9999; //return code for incomplete game
            }
        }

    }
    return toReturn;
}
