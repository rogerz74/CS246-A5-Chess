#ifndef _PAWN_H_
#define _PAWN_H_

#include "piece.h"

class Pawn: public Piece {
    bool isLegal(Box &targetBox) override;

    public:
        Pawn(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord);
        std::map<Box, int> updateLegalMoves() override;
};

#endif
