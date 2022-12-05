#include <string>
#include <iostream>
#include <vector>

#include "chessGame.h"
#include "subject.h"
#include "observer.h"
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
#include "human.h"
//#include "level1.h"
//#include "level2.h"
//#include "level3.h"

using namespace std;

struct scoreBoard {
    float whitePoints;
    float blackPoints;
    void print();
};

void scoreBoard::print() {
    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << whitePoints << std::endl;
    std::cout << "Black: " << blackPoints << std::endl;
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


Observer * constructPlayer(ChessGame *theGame, std::string player, std::vector<Piece *> *pieceSet) {


    if (player == "human") {
        Human * humanPlayer = new Human {theGame, "human"};
        return humanPlayer; 
    } else if (player == "computer[1]") {
        Level1 level1Player = new level1Player {theGame, "level1", pieceSet};
        Human * observerPtr = &level1Player;
        return observerPtr;
    } else if (player == "computer[2]") {
        Level2 level2Player = new Level2 {theGame, "level2", pieceSet};
        Human * observerPtr = &level2Player;
        return observerPtr;
    } else if (player == "computer[3]") {
        Level3 level3Player = new Level3 {theGame, "level3", pieceSet};
        Human * observerPtr = &level3Player;
        return observerPtr;
    }else {
        std::cout << "Invalid Player Given!" << std::endl;      //make it ask again?
        return nullptr;
    }
}


void gameInstance(scoreBoard & tracker) {

    //iterate over vector of vectors and build base board - possibility of keeping in main
    std::vector<std::vector<Piece *>> ChessBoard;
    buildBoard(ChessBoard);
    std::vector<std::vector<Piece *>> emptyBoard;
    buildBoard(emptyBoard);

    ChessGame game{&ChessBoard};        //constructor takes in ptr to board
    std::vector<Piece *> whitePieces;     //changing this back to pointer to pieces b/c using just pieces will cause compilation issues in setup.cc
    std::vector<Piece *> blackPieces;

    std::vector<Observer *> observerArr;

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

            if (!(setupFlag)) {
                game.setBoard(&emptyBoard);
                defaultSetup(&game, whitePieces, blackPieces);
            }

            Observer * whitePlayer = constructPlayer(&game, wPlayer, &whitePieces);
            observerArr.emplace_back(whitePlayer);
            Observer * blackPlayer = constructPlayer(&game, bPlayer, &blackPieces);
            observerArr.emplace_back(blackPlayer);

            int whoWon = gameRun(whitePlayer, blackPlayer, &game);
            if (whoWon == 1) {
                tracker.whitePoints += 1;
            } else if (whoWon == -1) {
                tracker.blackPoints += 1;
            } else if (whoWon == 0) {
                tracker.whitePoints += 0.5;
                tracker.blackPoints += 0.5;
            } else {
                std::cout << "Game left unfinished!" << std::endl;      //can be accounted for later
            }
            gameRunFlag = 1;
        } else {
            std::cout << "Invalid command! Please try again!" << std::endl;
        }
    }

    // these 3 loops free up all the heap-allocate memory for the piece vectors and observers
    for (std::size_t i = 0; i < whitePieces.size(); ++i) {
        Piece * tmp = whitePieces[i];
        delete tmp;
    }  

    for (std::size_t i = 0; i < blackPieces.size(); ++i) {
        Piece * tmp = blackPieces[i];
        delete tmp;
    }  

    for (std::size_t i = 0; i < observerArr.size(); ++i) {
        Observer * tmp = observerArr[i];
        delete tmp;
    }  


}

int main() {
    scoreBoard tracker{0,0};
    while (true) {
        gameInstance(tracker);
    }
    tracker.print();
}