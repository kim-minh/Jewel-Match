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

        SDL_Rect scoreBoard;

        GameBoard(const int& nRows, const int& nCols);

        //Render game boards
        void renderBoard(int score);

        //Clear matching jewels
        void clear();

        //Refill jewels
        void refill();
        
        int score;
        int scoreCalculate();
};

#endif