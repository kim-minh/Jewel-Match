#ifndef ENGINE_H
#define ENGINE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Log.h"

//Jewels in squares
enum Jewels{Destroyed, Red, Green, Blue, Orange, White, Total};

class Engine
{
    private:
        //Window size
        const int WINDOW_WIDTH, WINDOW_HEIGHT;

        //Window title
        const std::string TITLE;

        //Window icon
        SDL_Surface* icon;

        //Initialize Engine
        bool init();

    protected:
        SDL_Window* window;
        SDL_Renderer* renderer;
    
    public:
        Engine();
        ~Engine();
};

#endif