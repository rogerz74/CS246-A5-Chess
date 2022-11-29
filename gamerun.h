#ifndef _GAMERUN_H_
#define _GAMERUN_H_

#include <string>
#include "chessGame.h"
#include "subject.h"
#include "observer.h"
#include "human.h"
#include "humanHuman.h"

int gameRun(Observer *white, Observer *black, ChessGame *gameBoard);

#endif
