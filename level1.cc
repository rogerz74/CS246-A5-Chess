#include "level1.h"

Level1::Level1(ChessGame *subject, std::string name, std::vector<Piece> *pieceArray):
                Computer{subject, name, pieceArray} {}

bool Level1::pickMove() {
    int size = 0;
    std::cout << "Level 1 Computer makes its move." << std::endl;
    std::vector<Piece> pieces = *pieceArray;
    std::vector<Piece> chosenP;
    Piece *p;

    //picking random piece from vector
    while (size == 0) {
        std::sample(pieces.begin(), pieces.end(), std::back_inserter(chosenP), 1, std::mt19937{std::random_device{}()});
        p = &(chosenP[0]);
        size = (p->getLegalMoves())->size();      //legalMoves is a pointer to a map now
    }
    
    //picking random legalMove from map
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randompick(0, size-1);

    std::map<Box, int> lm = *(p->getLegalMoves());
    iterator item = lm.begin();
    std::advance( item, randompick(rng) );
    
    Box b = item->first;   //iterator points to {Box:value}
    int bX = b.getX();
    int bY = b.getY();

    p->move(p, (*(gameBoard->getBoard()))[bX][bY], bX, bY);
    return 0;
}
