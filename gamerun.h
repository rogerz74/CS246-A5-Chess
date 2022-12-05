#ifndef _GAMERUN_H_
#define _GAMERUN_H_

#include <string>
#include <iostream>
#include "chessGame.h"
#include "subject.h"
#include "observer.h"
#include "human.h"
#include "computer.h"
//#include "level1.h"
//#include "level2.h"
#include "level3.h"

int gameRun(Observer *white, Observer *black, ChessGame *gameBoard);

#endif
