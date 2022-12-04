#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"

class Queen: public Piece {
    // isLegal() checks if move is capturable (opposite colour)

    public:
        Queen(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord);
        bool getIsFirstMove() override;
        void updateIsFirstMove() override;
        bool isLegal(Box &targetBox) override;
        std::map<Box, int> updateLegalMoves() override;
        ~Queen() {};
};

#endif
