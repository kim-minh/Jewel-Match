#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include "Engine.h"
#include <vector>

using namespace std;

class GameBoard : protected Engine
{
    protected:
        const int nRows, nCols;

        //Jewels to be removed
        vector<vector<bool> > pendingRemoval;

        //n*n board
        vector<vector<int> > board;
        SDL_Texture* boardTexture;

        void randomize();

        //Render board
        void updateBoard();

        //Clear matching jewels
        void clear();

        //Refill jewels
        void refill();

        //Check if 3 jewels are matching
        bool match3(int row, int col, const std::string& direction);
        
        //Check if exists at least 3 jewels matching
        bool existMatch();


    public:

        GameBoard(const int rows, const int cols);
        ~GameBoard();
};

#endif