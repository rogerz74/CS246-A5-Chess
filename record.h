#ifndef _RECORD_H_
#define _RECORD_H_
#include "piece.h"

// class Piece; (this will need to be added once Piece.h is finished)

class Record {
    int xOriginCoord;
    int yOriginCoord;
    int xTargetCoord;
    int yTargetCoord;
    Piece* recordPiece;

    public:
        int getXOrigin() {
            return xOriginCoord;
        };
        int getYOrigin() {
            return yOriginCoord;
        };
        int getXTarget() {
            return xTargetCoord;
        };
        int getYTarget() {
            return yTargetCoord;
        };
        Piece* getPiece() {
            return recordPiece;
        }
};



#endif
