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
        // this will return the winner of the game, ie. "Black", "White" or "Draw"
        std::string level1(ChessGame *chessGame);
        std::string level2(ChessGame *chessGame);
        std::string level3(ChessGame *chessGame);
        std::string level4(ChessGame *chessGame);
        ~Computer();
};

#endif
