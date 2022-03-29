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
        const int WINDOW_WIDTH, WINDOW_HEIGHT;
        const std::string TITLE;
        SDL_Surface* icon;
        bool init();
    public:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Engine();
        ~Engine();
};

#endif