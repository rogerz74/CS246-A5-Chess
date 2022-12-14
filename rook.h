#ifndef _ROOK_H_
#define _ROOK_H_

#include "piece.h"

class Rook: public Piece {
    bool isFirstMove;

    public:
        Rook(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord);
        // isLegal() checks if move is capturable (opposite colour)
        bool isLegal(Box &targetBox) override;
        bool getIsFirstMove() override;
        void updateIsFirstMove() override;
        std::map<Box, int> updateLegalMoves() override;
        ~Rook() {};

};

#endif
