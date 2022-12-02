#ifndef _PIECE_H_
#define _PIECE_H_
#include <string>
#include <vector>
#include "box.h"

class Piece {
    std::string name;
    std::vector<std::vector<Piece *>> *board;
    bool whitePlayer;
    int xCoord;
    int yCoord;

    std::vector<Box> * legalMovesArr;
    std::vector<int> * legalMoveStates;

    protected:
    virtual bool isLegal(Box &targetBox) = 0;

    public:
        Piece(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, const int xCoord, const int yCoord);

        int getX();
        int getY();

        std::string getName();
        bool checkWhitePlayer();
        virtual bool getIsFirstMove() = 0;
        // if move is completed move will return 1
        int move(Piece *currentTile, Piece *targetTile, int newX, int newY);
        void print();

        std::vector<Box> *& getLegalMoves() {
            return legalMovesArr;
        };

        std::vector<int> *& getMoveStates() {
            return legalMoveStates;
        };

        std::vector<std::vector<Piece *>> *& getBoard() {
            return board;
        };
        virtual void updateLegalMoves() = 0;
        
        ~Piece();
};

#endif
