#ifndef _SETUP_H_
#define _SETUP_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "chessGame.h"
#include "subject.h"
#include "observer.h"
#include "box.h"
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

void userSetup(ChessGame *setupGame, std::vector<Piece *> &wPieces, std::vector<Piece *> &bPieces);
void defaultSetup(ChessGame *setupGame, std::vector<Piece*> &wPieces, std::vector<Piece *> &bPieces);

#endif
