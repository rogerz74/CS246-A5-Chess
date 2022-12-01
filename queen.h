#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"

class Queen: public Piece {
    // isLegal() checks if move is capturable (opposite colour)
    bool isLegal(Box targetBox) override;

    public:
        Queen(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord);
        void updateLegalMoves() override;
};

#endif
