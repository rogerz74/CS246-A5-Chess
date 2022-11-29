#ifndef _SETUP_H_
#define _SETUP_H_

#include <string>
#include <iostream>
#include <algorithm>
#include "chessGame.h"
#include "subject.h"
#include "observer.h"
#include "box.h"
#include "piece.h"

void userSetup(ChessGame *setupGame, std::vector<Piece *> &wPieces, std::vector<Piece *> &bPieces);
//void defaultSetup(ChessGame *setupGame, std::vector<Piece *> &wPieces, std::vector<Piece *> &bPieces);

#endif