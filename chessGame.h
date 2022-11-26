#ifndef _CHESSGAME_H_
#define _CHESSGAME_H_
#include <iostream>
#include <string>
#include "subject.h"
#include <vector>
#include "record.h"

/*

Note: This ChessGame class acts as our Concrete Subject for now. This class is originally known
as board but is changed to "ChessGame" b/c we have a field in this class already called board. 
In addition, this class is a concrete subject and having a concrete subject as Board with a 
board field seems weird. Hence, it has been RENAMED!!!

*/


class ChessGame: public Subject {
    // std::vector< vector <Box *>> board; (waiting on Box to be implemented)
    std::vector <Record>

    public:
        // the function that sets the board in the right configuration?? not sure exactly what this function referred to
        void draw(); 
        // question: how are we going to check if there's stalemate again? is it when we find a possible AND legal move?
        bool isStalemate();
}


#endif
