#include "box.h"
#include <iostream>

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

Box::~Box() {}
