#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include "observer.h"
#include "chessGame.h"
#include "piece.h"

class Computer: public Observer {
    ChessGame *subject;
    std::string name; // this is can acc probably be a str being either "Black" or "White"
    std::vector<Piece> * pieceArray; //vector array of pieces for the computer
    std::vector<Piece> * opponentArray; //vector array of pieces of the opponent (used for level3)

    public:
        Computer(ChessGame *chessGame, std::string name, std::vector<Piece> *pieceArray, std::vector<Piece> *opponentArray);
        void notify();
        virtual bool pickMove() = 0;
        ~Computer();
};

#endif
