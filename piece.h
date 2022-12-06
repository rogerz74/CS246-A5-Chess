#ifndef _PIECE_H_
#define _PIECE_H_
#include <string>
#include <vector>
#include <map>
#include "box.h"

class Piece {
    std::string name;
    std::vector<std::vector<Piece *>> *board;
    bool whitePlayer;
    int xCoord;
    int yCoord;

    std::map<Box, int> legalMovesMap;

    public:
        Piece(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, const int xCoord, const int yCoord);

        int getX();
        int getY();

        virtual bool isLegal(Box &targetBox) = 0;

        virtual bool getIsFirstMove() = 0;
        virtual void updateIsFirstMove() = 0;

        std::string getName();
        bool checkWhitePlayer();
        // if move is completed move will return 1
        void move(Piece *currentTile, Piece *targetTile, int newX, int newY);

        void setLegalMoves(std::map<Box, int> newMap) { //function to change legalMovesMap
            legalMovesMap = newMap;
        }

        std::map<Box, int> getLegalMoves() {
            return legalMovesMap;
        };

        std::vector<std::vector<Piece *>> *& getBoard() {
            return board;
        };
        virtual std::map<Box, int> updateLegalMoves() = 0;
        
        virtual ~Piece() {};
};

#endif
