#ifndef _LEVEL2_H_
#define _LEVEL2_H_

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <random>
#include <iterator>
#include "chessGame.h"
#include "observer.h"
#include "computer.h"
#include "box.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"

class Level2: public Computer {
    ChessGame *subject;
    std::string name;
    std::vector<Piece *> *pieceArray;
    std::vector<Piece *> *opponentArray;

    public:
        Level2(ChessGame *subject, std::string name, std::vector<Piece *> *pieceArray, std::vector<Piece *> *opponentArray);
        int pickMove();    
};
#endif
