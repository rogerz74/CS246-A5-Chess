#ifndef _ROOK_H_
#define _ROOK_H_

#include "piece.h"

class Rook: public Piece {
    bool isFirstMove;
    // isLegal() checks if move is capturable (opposite colour)
    bool isLegal(Box &targetBox) override;

    public:
        Rook(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord);
        bool getIsFirstMove() override;
        void updateIsFirstMove();
        std::map<Box, int> updateLegalMoves() override;

};

#endif
