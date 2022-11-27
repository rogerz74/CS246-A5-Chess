#ifndef _CHESSGAME_H_
#define _CHESSGAME_H_
#include <iostream>
#include <string>
#include "subject.h"
#include <vector>
#include "record.h"

/*

Note: This ChessGame class acts as our Concrete Subject for now. This class is originally known
as board but is changed to "ChessGame" b/c we have a field in this class already called board. 
In addition, this class is a concrete subject and having a concrete subject as Board with a 
board field seems weird. Hence, it has been RENAMED!!!

*/


class ChessGame: public Subject {
    std::vector< vector <Box*>> * board; // pointer to a 2D array of Box pointers
    std::vector <Record>
    bool whiteKingChecked;
    bool blackKingChecked;
    bool playerTurn; // true = white, false = black; using bool instead of str b/c it's probably just easier to use bool than a string for the playerTurn state

    public:
        // to initialize the ChessGame
        explicit ChessGame(std::vector< vector <Box*>> * board): board{board} {}

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
        
        std::vector< vector <Box *>> *&getBoard() {
            return board;
        };

        void set(std::string piece, std::string box, bool playerTurn); // WILL NEED THE PLAYER STATUS!!!!

        void setTurn(bool playerTurn);

        // bool pawnsInLimit(); --> Brought up by Shriya; this might be implemented later. For now, it's just been commented out.
        
};


#endif
