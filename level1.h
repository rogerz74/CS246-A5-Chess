#ifndef _LEVEL1_H_
#define _LEVEL1_H_

#include <string>
#include <iostream>
#include <vector>
#include "chessGame.h"
#include "observer.h"
#include "computer.h"
#include "piece.h"

class Level1: public Computer {
    ChessGame *subject;
    std::string name;
    std::vector<Piece> *pieceArray;

    public:
        Level1(ChessGame *subject, std::string name, std::vector<Piece> *pieceArray);
        //void notify(); (no need to override)
        bool pickMove();    
};

#endif
