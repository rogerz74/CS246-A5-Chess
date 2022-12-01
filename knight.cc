#include "knight.h"

Knight::Knight(std::string name, std::vector<std::vector<Piece *>> *board, bool whitePlayer, int xCoord, int yCoord):
    Piece{name, board, whitePlayer, xCoord, yCoord} {}

bool Knight::isLegal(Box &targetBox) {

    // if location is EMPTY OR WHITE CAPTURE BLACK OR BLACK CAPTURE WHITE
    if (!((*(this->getBoard()))[targetBox.getX()][targetBox.getY()]) || 
        (((*(this->getBoard()))[targetBox.getX()][targetBox.getY()]) && 
        ((checkWhitePlayer() && !(((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ||
         (!checkWhitePlayer() && (((*(this->getBoard()))[targetBox.getX()][targetBox.getY()])->checkWhitePlayer())) ) )) {
        return true;
    }
    return false;
}

void Knight::updateLegalMoves() {
    std::vector<Box> legalMoves;

    int x = this->getX();
    int y = this->getY();

    // if move is capturable (opposite colour) or if box is unoccupied then add to possible moves
    Box move1(x+2, y+1);
    Box move2(x-2, y-1);
    Box move3(x+2, y-1);
    Box move4(x-2, y+1);
    Box move5(x+1, y+2);
    Box move6(x-1, y-2);
    Box move7(x+1, y-2);
    Box move8(x-1, y+2);

    if (isLegal(move1)) {
        legalMoves.push_back(move1);
    }

    if (isLegal(move2)) {
        legalMoves.push_back(move2);
    }

    if (isLegal(move3)) {
        legalMoves.push_back(move3);
    }

    if (isLegal(move4)) {
        legalMoves.push_back(move4);
    }

    if (isLegal(move5)) {
        legalMoves.push_back(move5);
    }

    if (isLegal(move6)) {
        legalMoves.push_back(move6);
    }

    if (isLegal(move7)) {
        legalMoves.push_back(move7);
    }

    if (isLegal(move8)) {
        legalMoves.push_back(move8);
    }

    this->getLegalMoves() = &legalMoves;
}
