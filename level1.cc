#include "level1.h"

Level1::Level1(ChessGame *subject, std::string name, std::vector<Piece> *pieceArray):    //piece * to piece - make changes!!
                Computer{subject, name, pieceArray} {}

bool Level1::pickMove() {
    int size = 0;
    std::cout << "Level 1 Computer makes its move." << std::endl;
    std::vector<Piece> pieces = *pieceArray;
    std::vector<Piece> chosenP;
    Piece *p;

    while (size == 0) {
        std::sample(pieces.begin(), pieces.end(), std::back_inserter(chosenP), 1, std::mt19937{std::random_device{}()});
        p = &(chosenP[0]);
        size = (*(p->getLegalMoves())).size();
    }
    
    std::vector<Box> lm = *(p->getLegalMoves());
    std::vector<Box> prefMove;
    std::sample(lm.begin(), lm.end(), std::back_inserter(prefMove), 1, std::mt19937{std::random_device{}()});
    Box b = prefMove[0];   //not ptr
    int bX = b.getX();
    int bY = b.getY();

    p->move(p, (*(gameBoard->getBoard()))[bX][bY], bX, bY);
    return 0;
}
