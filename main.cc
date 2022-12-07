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
#include "level1.h"
#include "level2.h"
#include "level3.h"

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

/*
Observer * constructPlayer(ChessGame *theGame, std::string player, std::vector<Piece *> *&pieceSet, std::vector<Piece *> *&oppPiecesArr) {

    if (player == "human") {
        Human * humanPlayer = new Human {theGame, "human", pieceSet, oppPiecesArr};
        return humanPlayer; 
    } else if (player == "computer[1]") {
        Level1 * level1Player = new Level1 {theGame, "level1", pieceSet, oppPiecesArr};
        Computer * observerPtr = level1Player;
        return observerPtr;
    } else if (player == "computer[2]") {
        Level2 * level2Player = new Level2 {theGame, "level2", pieceSet, oppPiecesArr};
        Computer * observerPtr = level2Player;
        return observerPtr;
    } else if (player == "computer[3]") {
        Level3 * level3Player = new Level3 {theGame, "level3", pieceSet, oppPiecesArr};
        Computer * observerPtr = level3Player;
        return observerPtr;
    }else {
        std::cout << "Invalid Player Given!" << std::endl;      //make it ask again?
        return nullptr;
    }
}*/


void gameInstance(scoreBoard & tracker) {

    //iterate over vector of vectors and build base board - possibility of keeping in main

    std::vector<std::vector<Piece *>> ChessBoard;
    buildBoard(ChessBoard);
    std::vector<std::vector<Piece *>> emptyBoard;
    buildBoard(emptyBoard);

    tracker.blackPoints += 0; //ignore this line
    
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

            //std::cout << whitePieces.size() << ", " << blackPieces.size() <<std::endl;

            if (wPlayer == "human") {
                Human * humanPlayer = new Human {&game, "human", &whitePieces, &blackPieces};
                observerArr.emplace_back(humanPlayer);
            } else if (wPlayer == "computer[1]") {
                Computer * level1Player = new Computer {&game, "level1", &whitePieces, &blackPieces};
                observerArr.emplace_back(level1Player);
            } else if (wPlayer == "computer[2]") {
                Computer * level2Player = new Computer {&game, "level2", &whitePieces, &blackPieces};
                observerArr.emplace_back(level2Player);
            } else if (wPlayer == "computer[3]") {
                Computer * level3Player = new Computer {&game, "level3", &whitePieces, &blackPieces};
                observerArr.emplace_back(level3Player);
            }else {
                std::cout << "Invalid Player Given!" << std::endl;
            }

            if (bPlayer == "human") {
                Human * humanPlayer = new Human {&game, "human", &blackPieces, &whitePieces};
                observerArr.emplace_back(humanPlayer);
            } else if (bPlayer == "computer[1]") {
                Computer * level1Player = new Computer {&game, "level1", &blackPieces, &whitePieces};
                observerArr.emplace_back(level1Player);
            } else if (bPlayer == "computer[2]") {
                Computer * level2Player = new Computer {&game, "level2", &blackPieces, &whitePieces};
                observerArr.emplace_back(level2Player);
            } else if (bPlayer == "computer[3]") {
                Computer * level3Player = new Computer {&game, "level3", &blackPieces, &whitePieces};
                observerArr.emplace_back(level3Player);
            }else {
                std::cout << "Invalid Player Given!" << std::endl;      
            }

            /*
            Observer * whitePlayer = constructPlayer(&game, wPlayer, whtPtr, blkPtr);
            observerArr.emplace_back(whitePlayer);
            Observer * blackPlayer = constructPlayer(&game, bPlayer, blkPtr, whtPtr);
            observerArr.emplace_back(blackPlayer);
            */

            int whoWon = gameRun(observerArr[0], observerArr[1], &game);
            if (whoWon == 1) {
                tracker.whitePoints += 1;
            } else if (whoWon == -1) {
                tracker.blackPoints += 1;
            } else if (whoWon == 0) {
                tracker.whitePoints += 0.5;
                tracker.blackPoints += 0.5;
            } else {
                std::cout << "Game left unfinished!" << std::endl;      //if whoWon = -9999, then the game is incomplete
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

    // just running gameInstance Once FOR NOW
    gameInstance(tracker);
    tracker.print();
}
