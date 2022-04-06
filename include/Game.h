#ifndef GAME_H
#define GAME_H
#include "Jewels.h"

class Game
{
    private:
        SDL_Event e;
        SDL_TimerID timerID;
        Timer delay;

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

        //Check if game has started
        bool gameStarted;
        
        //Game state
        void startGame();
        void endGame();
        bool gameEnded;
        
        //Check if game is running
        bool running;

        static Uint32 callback(Uint32 interval, void* param);

    public:
        Game(const int& nRows, const int& nCols, int time);
};

#endif