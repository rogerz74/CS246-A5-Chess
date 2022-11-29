#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "piece.h"

class Knight: public Piece {
    // isLegal() checks if move is capturable (opposite colour) or if box is unoccupied
    bool isLegal(Box *targetBox);
    
    public:
        Knight(std::string name, std::vector<std::vector<Box *>> &board, Box *box, bool whitePlayer);
        void updateLegalMoves();
};

#endif
