#include "chessGame.h"
#include "subject.h"
#include "observer.h"
#include "human.h"
#include "computer.h"
#include "box.h"
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include <iostream>
#include <string>

using namespace std;

// a helper function to convert the letter to a number; I tried using enums but converting a string to an enum is difficult
int strToCoord(char c) {
    if (c == 'a') {
        return 0;
    } else if (c == 'b') {
        return 1;
    } else if (c == 'c') {
        return 2;
    } else if (c == 'd') {
        return 3;
    } else if (c == 'e') {
        return 4;
    } else if (c == 'f') {
        return 5;
    } else if (c == 'g') {
        return 6;
    } else {
        return 7;
    }
}

    /*
    
    I don't think we should have the "void set()" function in the chessGame clasee (this was originally the BOARD CLASS). This is b/c
    if I do decide to create it in chessGame, once the function finishes and goes out of scope, the pieces will be destroyed and that's
    not what we want. We should create the pieces in this "main.cc" file so that the piece contiunes to exist until the game is over.

    */

void set(std::string piece, std::string box) {

    int row = strToCoord(box[0]); // the first char of the input is a letter from a-h, assuming valid input
    int col = box[1] - '0';
    Box * boxptr = this.getBoard()[col][row]; //is this the right way to access a position in a pointer to an array?
    
    if (piece == "K") {
        if (playerTurn) { //if it's white player's turn
            King k = new King (false, playerTurn, "K", false, boxptr);
        } else { // black player's turn
            King k = new King (false, playerTurn, "k", false, boxptr);
        }

    } else if (piece == "Q") {
        if (playerTurn) { //if it's white player's turn
            Queen Q = new King (false, playerTurn, "K", false, boxptr);
        } else { // black player's turn
            Queen k = new King (false, playerTurn, "k", false, boxptr);
        }

    } else if (piece == "B") {
        if (playerTurn) { //if it's white player's turn
            King k = new King (false, playerTurn, "K", false, boxptr);
        } else { // black player's turn
            King k = new King (false, playerTurn, "k", false, boxptr);
        }

    } else if (piece == "R") {
        
    } else if (piece == "N") {
        
    } else if (piece == "P") {
        
    }
}


int main() {

    vector<Box*> board;
    board.resize(8, vector<Box*>(8, 0));

    vector< vector <Box*>> * chessGameBoard = &board;

    // initializing the chessGame
    ChessGame game{chessGameBoard};

    /* PSEUDOCODE for the set function
    
    if (user wants to call on "set" function in command interpreter) {
        string piece;
        string box;

        cin >> piece;
        cin >> box;
    
        int row = strToCoord(box[0]); // the first char of the input is a letter from a-h, assuming valid input
        int col = box[1] - '0';
        Box * boxptr = game.getBoard()[col][row];

        if (piece == "K") {
            if (playerTurn) { //if it's white player's turn
                King K(false, playerTurn, "K", false, boxptr);
            } else { // black player's turn
                King k(false, playerTurn, "k", false, boxptr);
            }

        } else if (piece == "Q") {

        *************************** we are also going to need to figure how we want to name all these bishops and pawns for setup ***************************

        } else if (piece == "B") {

        } else if (piece == "R") {
            
        } else if (piece == "N") {
            
        } else if (piece == "P") {
            
        }

        }
    
    }
    
    */
    


}