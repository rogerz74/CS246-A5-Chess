#include "observer.h"
#include "queen.h"
#include "chessGame.h"
#include <algorithm>

void Observer::promotePawn(ChessGame *subject,std::vector<Piece*> * pieceArray, Piece * p) {
    Piece *pawnPromoPiece;
    if (p->getName() == "P" && p->getX() == 0) {
        pawnPromoPiece = new Queen {"Q", subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
    }  else if (p->getName() == "p" && p->getX() == 7) {
        pawnPromoPiece = new Queen {"q", subject->getBoard(), p->checkWhitePlayer(), p->getX(), p->getY()};
    }

    // look for pawn and delete it
    pieceArray->erase(find(pieceArray->begin(), pieceArray->end(), p));

    // add queen to vector and board
    pieceArray->push_back(pawnPromoPiece);
    (*(subject->getBoard()))[p->getX()][p->getY()] = pawnPromoPiece;

    delete p;
}
