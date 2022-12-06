#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "observer.h"
#include "chessGame.h"

class Human: public Observer {
    ChessGame *subject;
    std::string name;
    std::vector<Piece*> * pieceArray; //vector array of pieces for Human
    std::vector<Piece*> * opponentArray;

    public:
        Human(ChessGame *subject, std::string name, std::vector<Piece*> * pieceArray, std::vector<Piece*> * opponentArray);
        int pickMove();
        void notify(); // will print out the board;
        bool promotePawn(Piece * p, std::string promoName);
        ~Human();
};

#endif

