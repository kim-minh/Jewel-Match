#ifndef JEWELS_H
#define JEWELS_H
#include "GameBoard.h"

class Jewel : private GameBoard
{
    private:
        friend class Game;

        Jewel(const int &nRows, const int &nCols, int time);

        //Render jewels
        void renderJewel();

        //Update jewels state
        void updateJewel();

        //Randomize jewels
        void randomize();

        //Check if 3 jewels are matching
        bool match3(const int &row, const int &col, const std::string &direction);
        
        //Check if exists at least 3 jewels matched
        bool existMatch();
        
        //Hint handle
        bool existHint(); //Check if exist jewels that can be matched
        int hintX, hintY, hintX_, hintY_; //Hint position
        bool hint; //Check if hint is needed
        void displayHint(); //Display hint

        //Draw selector
        void renderSelector(int selectedX, int selectedY, int x, int y);
};

#endif