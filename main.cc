#include <string>
#include <iostream>
#include <vector>

#include "chessGame.h"
#include "subject.h"
#include "observer.h"
#include "human.h"
#include "computer.h"
#include "box.h"
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

#include "setup.h"
#include "gamerun.h"

/*
TO DO:
- constructPlayer()
*/

struct scoreBoard;
void gameInstance();

int main() {
    scoreBoard tracker{0,0};
    while (true) {
        gameInstance();
    }
    tracker.print();
}


struct scoreBoard {
    float whitePoints;
    float blackPoints;
    void print();
}

void scoreBoard::print() {
    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << scoreBoard.whitePoints << std::endl;
    std::cout << "Black: " << scoreBoard.blackPoints << std::endl;
}


void buildBoard(std::vector<std::vector<Piece *>> &board) {
    for (int row = 0; row < 8; ++row) {
        std::vector<Piece *> boardRow;
        for (int col = 0; col < 8; ++col) { 
            boardRow.push_back(nullptr);        //initializing all places to nullptrs
        } 
        board.push_back(boardRow);
    } 
}


void gameInstance() {

    //iterate over vector of vectors and build base board - possibility of keeping in main
    std::vector<std::vector<Piece *>> ChessBoard;
    buildBoard(ChessBoard);
    std::vector<std::vector<Piece *>> emptyBoard;
    buildBoard(emptyBoard);

    ChessGame game{&ChessBoard};        //constructor takes in ptr to board
    std::vector<Piece *> whitePieces;
    std::vector<Piece *> blackPieces;

    bool setupFlag = 0;         //changed to 1 if "setup" command executed (must be successful, else cannot leave mode)
    bool gameRunFlag = 0;       //changed to 1 if "game" command executed and when gameRun finishes
    std::string comm = "";
    while (!(gameRunFlag) && (cin >> comm)) {
        if (comm == "setup") {
            if (setupFlag) {
                ChessBoard.clear();
                buildBoard(ChessBoard);
                game.setBoard(&ChessBoard);    //create method to take in pointer to the board and change board in class
            }
            userSetup(&game, whitePieces, blackPieces);     //takes references to the vectors and changes them
            setupFlag = 1;
        } else if (comm == "game") {
            std::string wPlayer = "";
            std::string bPlayer = "";
            std::cin >> wPlayer >> bPlayer;

            //later, constructPlayer(player) will be defined to construct human/l1/l2/l3/l4
            //Human for now, till level subclasses are created and defined
            Human whitePlayer{&game, "human"};  //+ &whitePieces for computer
            Human blackPlayer{&game, "human"};  //+ &blackPieces for computer

            if (!(setupFlag)) {
                game.setBoard(&emptyBoard);
                defaultSetup(&game, whitePieces, blackPieces);
            }

            int whoWon = gameRun(&whitePlayer, &blackPlayer, &game);
            if (whoWon == 1) {
                tracker.whitePoints += 1;
            } else if (whoWon = -1) {
                tracker.blackPoints += 1;
            } else if (whoWon == 0) {
                tracker.whitePoints += 0.5;
                tracker.blackPoints += 0.5;
            } else {
                std::cout << "Game left unfinished!" << std::endl;
            }
            gameRunFlag = 1;
        } else {
            std::cout << "Invalid command! Please try again!" << std::endl;
        }
    }
}
