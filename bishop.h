#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "piece.h"

class Bishop: public Piece {
    // isLegal() checks if move is capturable (opposite colour)
    bool isLegal(Box &targetBox) override;

    public:
        Bishop(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord);
        void updateLegalMoves() override;

};

#endif
