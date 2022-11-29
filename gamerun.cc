#include "gamerun.h"
using namespace std;

//Helper function to redirect the board and players to apppropriate gameflow

int gameRun(Observer *white, Observer *black, ChessGame *gameBoard) {
    int winner = 0;     //1 if white wins, -1 if black wins & 0 if it's a draw
    string W = white->name;
    string B = black->name;

    if ((W = "human") && (B = "human")) {
        winner = humanHuman(white, black, gameBoard);
    } else if (W = "human") {
        winner = humanComp(white, black, gameBoard);    //code down, not uploaded due to ambiguity of pickMove()
    } else if (B = "human") {
        winner = compHuman(white, black, gameBoard);    //code down, not uploaded due to ambiguity of pickMove()
    } else {
        winner = compComp(white, black, gameBoard);     //code down, not uploaded due to ambiguity of pickMove()
    }
    return winner;
}
