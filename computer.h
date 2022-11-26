#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include "observer.h"
#include "chessGame.h"

class Computer: public Observer {
    ChessGame *chessGame;
    std::string name;

    public:
        Computer(ChessGame *chessGame, std::string name);
        void notify();
        // we need to decide if we want these to simply be void functions or if we want to return something
        // This levels thing may also need to move the main.cc file??
        void level1(ChessGame *chessGame);
        void level2(ChessGame *chessGame);
        void level3(ChessGame *chessGame);
        void level4(ChessGame *chessGame);
        ~Computer();
};

#endif
