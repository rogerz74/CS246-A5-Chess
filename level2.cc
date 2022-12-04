#include "level2.h"

Level2::Level2(ChessGame *subject, std::string name, std::vector<Piece> *pieceArray):
                Computer{subject, name, pieceArray} {}


//create second map (filteredMap)
//loop through whole of pieceArray with iterator p, loop through p->LegalMoves() with iterator i
//if i.second == 1 then add p:Box to second map and then randomly select from map

bool Level2::pickMove() {
    int size = 0;
    std::cout << "Level 2 Computer makes its move." << std::endl;
    std::map<Piece *, Box> filteredMap;
    std::vector<Piece> pieces = *pieceArray;
    int arraySize = pieces.size();

    for (int i = 0; i < arraySize; i++) {       //looping through all the pieces
        std::map<Box, int> lm = *((pieces[i])->getlegalMoves());
        int lmSize = lm.size();
        for (auto &k: lm) {                     //looping through all legal moves
            if (k.second == 1) {
                filteredMap[pieces[i]] = k.first;       //constructing a map to pick move from
            }
        }
    }
    
    int size = filteredMap.size();
    
    if (size == 0) {                //effectively choosing random move - level 1 algorithm
        int lmSize = 0;
        std::vector<Piece> chosenP;
        Piece *p;
        while (lmSize == 0) {
            std::sample(pieces.begin(), pieces.end(), std::back_inserter(chosenP), 1, std::mt19937{std::random_device{}()});
            p = &(chosenP[0]);
            lmSize = (p->getLegalMoves())->size();
        }
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randompick(0, lmSize-1);
        std::map<Box, int> lm = *(p->getLegalMoves());
        iterator item = lm.begin();
        std::advance( item, randompick(rng) );

        Box b = item->first;   //iterator points to {Box:value}
        int bX = b.getX();
        int bY = b.getY();
        p->move(p, (*(gameBoard->getBoard()))[bX][bY], bX, bY);
    } else {                                                //selecting random element from filteredMap
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randompick(0, size-1); //picks random index in filteredMap
        iterator item = filteredMap.begin();                //iterator points to {Piece*:Box}
        std::advance( item, randompick(rng) );
        
        Piece *p = item->first;
        Box b = item->second;   
        int bX = b.getX();
        int bY = b.getY();

        p->move(p, (*(gameBoard->getBoard()))[bX][bY], bX, bY);
    }
    return 0;
}
