#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include "observer.h"
#include "chessGame.h"
#include "piece.h"
#include "queen.h"
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <random>
#include <iterator>
#include "computer.h"
#include "box.h"
#include "pawn.h"
#include "rook.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"

class Computer: public Observer {
    ChessGame *subject;
    std::string name; // this is can acc probably be a str being either "Black" or "White"
    std::vector<Piece*> * pieceArray; //vector array of pieces for the computer
    std::vector<Piece*> * oppArray; //opponent pieces array
    
    public:
        Computer(ChessGame *subject, std::string name, std::vector <Piece*> * pieceArray, std::vector<Piece*> * oppArray);
        void notify() override;
        std::string getName();
        int pickMove() override;
        void promotePawn(Piece * p);
        ~Computer();
};

#endif
