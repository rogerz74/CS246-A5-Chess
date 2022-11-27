#ifndef _PIECE_H_
#define _PIECE_H_
#include <string>
#include <vector>
#include "box.h"

class Piece {
    std::string name;
    bool whitePlayer;
    bool captured;
    Box *box;
    std::vector<std::vector<Box *>> board;

    protected:
    virtual bool isLegal() = 0;

    public:
        Piece(std::string name, std::vector<std::vector<Box *>> board, Box *box, bool whitePlayer);
        std::string getName();
        bool checkWhitePlayer();
        bool isCaptured();
        void move(Box *targetBox);
        virtual std::vector<Box *> possibleMoves() = 0;
        ~Piece();
};

#endif
