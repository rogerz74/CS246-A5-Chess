#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"

class Queen: public Piece {
    // isLegal() checks if move is capturable (opposite colour)
    bool isLegal(Box *targetBox);

    public:
        Queen(std::string name, std::vector<std::vector<Box *>> *board, Box *box, bool whitePlayer);
        void updateLegalMoves();
};

#endif
