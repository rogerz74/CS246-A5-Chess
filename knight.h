#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "piece.h"

class Knight: public Piece {
    // isLegal() checks if move is capturable (opposite colour) or if box is unoccupied
    bool isLegal(Box &targetBox) override;
    
    public:
        Knight(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord);
        void updateLegalMoves() override;
};

#endif
