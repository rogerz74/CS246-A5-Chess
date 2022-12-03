#ifndef _KING_H_
#define _KING_H_

#include "piece.h"
#include "chessGame.h"

class King: public Piece {
    bool isFirstMove;
    bool isLegal(Box &targetBox) override;

    public:
        King(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord);
        bool getIsFirstMove() override;
        std::map<Box, int> updateLegalMoves() override;
};

#endif
