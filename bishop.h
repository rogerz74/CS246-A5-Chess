#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "piece.h"

class Bishop: public Piece {


    public:
        Bishop(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord);
        bool getIsFirstMove() override;
        void updateIsFirstMove() override;
        // isLegal() checks if move is capturable (opposite colour)
        bool isLegal(Box &targetBox) override;
        std::map<Box, int> updateLegalMoves() override;

        ~Bishop() {};

};

#endif
