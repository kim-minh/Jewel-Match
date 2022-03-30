#ifndef GAME_H
#define GAME_H
#include "Jewels.h"

class Game
{
    private:
        SDL_Event e;

        //Selector texture
        SDL_Texture* selector;

        //Draw selector
        void renderSelector();

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

        //Check if key was pressed
        bool pressed;
        
        //Check if application is running
        bool running;

        //Check if a jewel was selected
        bool selected;

    public:
        Game(const int& rows, const int& cols);
        ~Game();
};

#endif