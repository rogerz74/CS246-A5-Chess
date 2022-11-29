#ifndef _CHESSGAME_H_
#define _CHESSGAME_H_
#include <iostream>
#include <string>
#include "subject.h"
#include <vector>
#include "record.h"
#include "box.h"
#include "piece.h"

/*

Note: This ChessGame class acts as our Concrete Subject for now. This class is originally known
as board but is changed to "ChessGame" b/c we have a field in this class already called board. 
In addition, this class is a concrete subject and having a concrete subject as Board with a 
board field seems weird. Hence, it has been RENAMED!!!

*/


class ChessGame: public Subject {
    std::vector< vector <Box*>>* board; // a 2D array of Box pointers
    std::vector <Record> history;
    bool whiteKingChecked = false;
    bool blackKingChecked = false;
    bool blackKingPresent = false;
    bool whiteKingPresent = false;
    bool playerTurn; // true = white, false = black; using bool instead of str b/c it's probably just easier to use bool than a string for the playerTurn state

    public:
        // to initialize the ChessGame
        explicit ChessGame(std::vector< vector <Box*>> board): board{board} {};

        void setBoard(std::vector< vector <Box*>> & targetBoard); // if we want to change the board

        // the function that sets the board in the right configuration?? not sure exactly what this function referred to
        void draw(); 
        // question: how are we going to check if there's stalemate again? is it when we find a possible AND legal move?
        bool isStalemate(); 

        // function that checks if the white king is checked;
        bool isWhiteKingChecked() {
            return whiteKingChecked;
        }; 
         // function that checks if the black king is checked;
        bool isBlackKingChecked() {
            return blackKingChecked;
        };

        // function that checks if the white king is present in the board;
        bool isWhiteKingPresent() {
            return whiteKingPresent;
        }; 
         // function that checks if the black king is present in the board;
        bool isBlackKingPresent() {
            return blackKingPresent;
        };
        
        std::vector< vector <Box *>> *& getBoard() {
            return board;
        };

        void setTurn(bool playerTurn);

        void switchTurn();

        bool getPlayerTurn();

        void updateKingPresence();

        void checkingForKingCheck();

        
};


#endif
