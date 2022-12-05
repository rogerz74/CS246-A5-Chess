#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "piece.h"

class Knight: public Piece {
    
    public:
        Knight(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord);
        bool getIsFirstMove() override;
        void updateIsFirstMove() override;
        // isLegal() checks if move is capturable (opposite colour) or if box is unoccupied
        bool isLegal(Box &targetBox) override;
        std::map<Box, int> updateLegalMoves() override;
        ~Knight() {};
};

#endif
