#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include "observer.h"
#include "chessGame.h"
#include "piece.h"

class Computer: public Observer {
    ChessGame *subject;
    std::string name; // this is can acc probably be a str being either "Black" or "White"
    std::vector<Piece*> * pieceArray; //vector array of pieces for the computer

    public:
        Computer(ChessGame *chessGame, std::string name, vector<Piece*> * pieceArray);
        void notify();
        // this will return the winner of the game, ie. "Black", "White" or "Draw"
        std::string level1(ChessGame *chessGame);
        std::string level2(ChessGame *chessGame);
        std::string level3(ChessGame *chessGame);
        std::string level4(ChessGame *chessGame);
        ~Computer();
};

#endif
