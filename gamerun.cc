#include "gamerun.h"
using namespace std;

/*
TO DO:
- Add pickMove() method to Human
- Create Levelx subclasses for Computer, each with a pickMove() method
*/

int gameRun(Observer *white, Observer *black, ChessGame *gameBoard) {
    int turn = gameBoard->getPlayerTurn();
    int toReturn = INT_MAX;
    string comm = "";
    string a = "";
    string b = "";

    //implement error checking so INT_MAX returned if game unfinished

    while (toReturn == INT_MAX) {
        if (turn == 1) {
            cout << "White's Turn: ";
            bool resignStatus = white->pickMove();       //so pickMove() will have bool return type
            if (resignStatus == 1) {                    //never executed with compcomp
                toReturn = -1;
            } else if (gameBoard->isStalemate() == 1) {
                toReturn = 0;
            } else if (gameBoard->isBlackKingChecked() == 1) {
                toReturn = 1;
            } else {
                gameBoard->switchTurn();
                turn = gameBoard->getPlayerTurn();
            }
        } else {
            cout << "Black's Turn: ";
            bool resignStatus  = black->pickMove();
            if (resignStatus == 1) {
                toReturn = 1;
            } else if (gameBoard->isStalemate == 1) {
                 toReturn = 0;
            } else if (gameBoard->isWhiteKingChecked() == 1) {
                toReturn = -1;
            } else {
                gameBoard->switchTurn();
                turn = gameBoard->getPlayerTurn();
            }
        }
    }
    return toReturn;
}
