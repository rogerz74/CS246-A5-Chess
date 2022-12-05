#ifndef _LEVEL3_H_
#define _LEVEL3_H_

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <random>
#include "chessGame.h"
#include "observer.h"
#include "computer.h"
#include "box.h"
#include "piece.h"

class Level3: public Computer {
    ChessGame *subject;
    std::string name;
    std::vector<Piece*> *pieceArray;
    std::vector<Piece*> *oppArray;

    public:
        Level3(ChessGame *subject, std::string name, std::vector<Piece*> *pieceArray, std::vector<Piece*> *oppArray);
        bool pickMove();    
};

#endif
