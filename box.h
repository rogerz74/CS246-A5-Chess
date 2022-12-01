#ifndef _BOX_H_
#define _BOX_H_

// a class that simply just stores and saves the grid tile locations, REALLY ONLY USED FOR LEGAL MOVES AND MOVEMENT OF PIECES

class Box {
    // For xCoord, we are going to use enums and assign each alphabet a value from 0-8 
    //    ("a" = 0, "b" = 1, ..., "h"=7).
    // For xCoord, we are going to use enums and assign "8" = 0, "7" = 1, ..., "1"=7.
    // This will allow us to match the coordinates to the index of our board.
    int xCoord, yCoord;

    public:
        Box(const int & xCoord, const int & yCoord);
        int getX() const;
        int getY() const;

        bool operator== (const Box & b1) const;

        virtual ~Box();
};

#endif
