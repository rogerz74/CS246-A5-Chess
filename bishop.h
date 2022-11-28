#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "piece.h"

class Bishop: public Piece {
    public:
        Bishop(std::string name, std::vector<std::vector<Box *>> &board, Box *box, bool whitePlayer);
        void updateLegalMoves();

};

#endif
