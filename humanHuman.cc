/* Details:
- takes in Human *white, Human *black
- only works with the commands 'move a b' and 'resign'
- accesses the board for whose turn it is i.e. gameBoard->getplayerTurn();
- after turn, switchTurn() to other;
- will probably have to define board first i.e. ChessGame *gameBoard = white->chessGame;
- cin >> command for both people's turns (check if piece of their color moved?)
- for "move a b", executes (gameBoard->board[a[1]][a[0]]->piece)->move(b); i.e. (ptr to piece at a)->move(b);?
- rest will be handled within piece but if unsuccessful, returns -1 & error message output
- for "resign", just returns 1 if playerTurn = 0, 0 if playerTurn = 1;
*/

#include "humanHuman.h"


int strToCoord(char c);

int humanHuman(Human *white, Human *black, ChessGame *gameBoard) {
    int turn = gameBoard->getplayerTurn();
    int toReturn = INT_MAX;
    std::string comm = "";
    std::string a = "";
    std::string b = "";

    while (std::cin >> comm) {

        if (turn == 1) {
            std::cout << "White";
        } else {
            std::cout << "Black";
        }
        std::cout << "'s Turn: '";

        if (comm == "move") {   //could define pickmove() for human with these steps?
            std::cin >> a >> b;
            success = (gameBoard->getBoard()[strToCoord(a[1])][strToCoord(a[0])]->getpiece())->move(board[strToCoord(b[1])][strToCoord(b[0])]);
            if (success != 1) {
                std::cout << "Invalid move! Please try again!" << std::endl;
            } else {
                if (gameBoard->isStalemate == 1) {
                    toReturn = 0;
                    break;
                } else if (gameBoard->isCheckmate == 1) {
                    if (turn == 0) {
                        toReturn = -1;
                    } else {
                        toReturn = 1;
                    }
                    break;
                } else {
                    gameBoard->switchTurn();
                    turn = gameBoard->getplayerTurn();
                    std::cout << std::endl;
                }
            }
        } 
        
        else if (comm == "resign") {
            if (turn == 0) {
                toReturn = 1;
            } else {
                toReturn = -1;
            }
            break;
        } 
        
        else {
            std::cout << "Invalid command! Please try again!" << std::endl;
        }
    }
    return toReturn;
}


int strToCoord(char c) {
    if (c == 'a' || c == '8') {
        return 0;
    } else if (c == 'b' || c == '7') {
        return 1;
    } else if (c == 'c' || c == '6') {
        return 2;
    } else if (c == 'd' || c == '5') {
        return 3;
    } else if (c == 'e' || c == '4') {
        return 4;
    } else if (c == 'f' || c == '3') {
        return 5;
    } else if (c == 'g' || c == '2') {
        return 6;
    } else {
        return 7;
    }
}
