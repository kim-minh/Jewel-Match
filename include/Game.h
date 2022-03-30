#ifndef GAME_H
#define GAME_H
#include "Jewels.h"

class Game : private Jewel
{
    private:
        SDL_Event e;
        SDL_Texture* selector;
        void renderSelector();
        void swapJewels();
        void loop();
        void updateGame();

        int x, y, selectedX, selectedY;
        bool pressed, running, selected;
    public:
        Game(const int rows, const int cols);
        ~Game();
};

#endif