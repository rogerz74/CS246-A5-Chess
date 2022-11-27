#ifndef _BOX_H_
#define _BOX_H_

#include "piece.h"

class Box {
    // For xCoord, we are going to use enums and assign each alphabet a value from 0-8 
    //    ("a" = 0, "b" = 1, ..., "h"=7).
    // For xCoord, we are going to use enums and assign "8" = 0, "7" = 1, ..., "1"=7.
    // This will allow us to match the coordinates to the index of our board.
    int xCoord, yCoord;
    Piece *currentPiece;
    bool isBlackTile;

    public:
        // If creating an empty box (with no piece) currentPiece = nullptr
        Box(int xCoord, int yCoord, Piece *currentPiece);
        int getX();
        int getY();
        Piece *getPiece();
        Piece *setPiece(Piece *currentPiece);
        bool isOccupied();
        void print();
        ~Box();
};

#endif
