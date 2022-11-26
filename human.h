#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "observer.h"
#include "chessGame.h"

class Human: public Observer {
    ChessGame *chessGame;
    std::string name;

    public:
        Human(ChessGame *chessGame, std::string name);
        void notify();
        ~Human();
};

#endif

