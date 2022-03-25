#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include <vector>

using namespace std;

class GameBoard
{
    private:
        const int nRows, nCols;
        vector<vector<bool> > pendingRemoval;

    public:
        vector<vector<int> > board;
        //Initialize board
        GameBoard(const int rows, const int cols);

        void randomize();

        //Display board
        void display();

        //Clear matching jewels
        void clear();

        //Refill jewels
        void refill();

        //Check if 3 jewels are matching
        bool match3(int row, int col, const std::string& direction);
        
        //Check if exists at least 3 jewels matching
        bool existMatch();

};

#endif