#ifndef _PAWN_H_
#define _PAWN_H_

#include "piece.h"

class Pawn: public Piece {

    public:
        Pawn(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord);
        bool getIsFirstMove() override;
        void updateIsFirstMove() override;
        bool isLegal(Box &targetBox) override;
        std::map<Box, int> updateLegalMoves() override;
        ~Pawn() {};
};

#endif
