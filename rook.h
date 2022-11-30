#ifndef _ROOK_H_
#define _ROOK_H_

#include "piece.h"

class Rook: public Piece {
    bool isFirstMove;
    // isLegal() checks if move is capturable (opposite colour)
    bool isLegal(Box *targetBox);

    public:
        Rook(std::string name, std::vector<std::vector<Box *>> *board, Box *box, bool whitePlayer);
        void updateLegalMoves();

};

#endif
