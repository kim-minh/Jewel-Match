#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include "Engine.h"
#include <vector>

using namespace std;

class GameBoard : protected Engine
{
    private:
        //Board texture
        SDL_Texture* boardTexture;

    protected:
        //Board size
        const int nRows, nCols;

        //n*n board
        vector<vector<int> > board;

        //Squares that hold jewel
        vector<vector<SDL_Rect> > square;

        //Jewels to be removed
        vector<vector<bool> > pendingRemoval;

        GameBoard(const int& rows, const int& cols);
        ~GameBoard();

        //Render board
        void updateBoard();

        //Clear matching jewels
        void clear();

        //Refill jewels
        void refill();
};

#endif