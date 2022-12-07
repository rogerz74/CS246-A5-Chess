#ifndef _LEVEL1_H_
#define _LEVEL1_H_

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <random>
#include <iterator>
#include "chessGame.h"
//#include "observer.h"
#include "computer.h"
//#include "box.h"
//#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"

class Level1: public Computer {

    public:
        Level1(ChessGame *subject, std::string name, std::vector <Piece*> * pieceArray, std::vector<Piece*> * oppArray);
        int pickMove();    
};
#endif
