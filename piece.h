#ifndef _PIECE_H_
#define _PIECE_H_
#include <string>
#include <vector>
#include "box.h"

class Piece {
    std::string name;
    bool whitePlayer;
    bool captured;

    protected:
    Box *box;
    std::vector<std::vector<Box *>> &board;
    std::vector<Box*> legalMoves;
    // commenting this out cause I'm not so sure if we will need isLegal() function at all cause im
    // trying to check for legality while generating possible moves (which is now called updateLegalMoves)
    // virtual bool isLegal(Box *targetBox) = 0;

    public:
        Piece(std::string name, std::vector<std::vector<Box *>> &board, Box *box, bool whitePlayer);
        std::string getName();
        bool checkWhitePlayer();
        bool isCaptured();
        // if move is completed move will return 1
        int move(Box *targetBox);
        virtual void updateLegalMoves() = 0;
        ~Piece();
};

#endif
