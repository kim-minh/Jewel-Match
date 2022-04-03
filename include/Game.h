#ifndef GAME_H
#define GAME_H
#include "Jewels.h"

class Game
{
    private:
        SDL_Event e;

        Jewel jewel;

        //Coordinate
        int x, y;
        //Selected coordinate
        int selectedX, selectedY;

        //Swap 2 jewels
        void swapJewels();

        //Game loop
        void loop();

        //Update game state
        void updateGame();
        
        //Check if application is running
        bool running;

    public:
        Game(const int& nRows, const int& nCols);
};

#endif