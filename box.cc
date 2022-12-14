#include "box.h"

Box::Box(const int & xCoord, const int & yCoord): 
    xCoord{xCoord}, yCoord{yCoord} {
}

int Box::getX() const{ 
    return xCoord; 
}

int Box::getY() const{
    return yCoord;
}

bool Box::operator== (const Box & b1) const {
    if (b1.getX() == xCoord && b1.getY() == yCoord) {
        return true;
    }
    return false;
}

 bool Box::operator< (const Box & b1) const {

    if (xCoord < b1.getX() && yCoord < b1.getY()) {
        return true;
    } else if (xCoord >= b1.getX() && yCoord >= b1.getY()) {
        return false;
    }
    return true;
 }

Box::~Box() {}
