#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "observer.h"
#include "chessGame.h"

class Human: public Observer {
    ChessGame *subject;
    std::string name;

    public:
        Human(ChessGame *subject, std::string name);
        bool pickMove();
        void notify(); // will print out the board;
        ~Human();
};

#endif

