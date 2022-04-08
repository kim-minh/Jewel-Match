#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include "Engine.h"
#include <vector>
using std::vector;

class GameBoard
{
    protected:
        Engine engine;

        //Board size
        const int nRows, nCols;

        //n*n board
        vector<vector<int> > board;

        //Squares that hold jewel
        vector<vector<SDL_Rect> > square;

        //Jewels to be removed
        vector<vector<bool> > pendingRemoval;

        GameBoard(const int &nRows, const int &nCols, int time);

        //Game start screen
        void renderStart();
        //Game end screen
        void renderEnd();

        //Render game boards
        void renderBoard();

        //Notice game is starting
        void startNotice();

        //Render timer
        SDL_Rect timeBoard;
        Uint32 time;
        void renderTimer();

        //Render score
        SDL_Rect scoreBoard;
        SDL_Rect highscoreBoard;
        void renderScore();
        void renderHighScore();
        Sint32 score;
        Sint32 scoreCalculate();

        //Clear matching jewels
        void clear();

        //Refill jewels
        void refill();
};

#endif