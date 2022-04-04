#ifndef ENGINE_H
#define ENGINE_H
#include "Texture.h"
#include "Timer.h"

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

        bool success;

        //Initialize Engine
        bool init();

        //Initialize Texture
        bool initTexture();

        //Initialize Font
        bool initFont();

        void exit();

    public:
        Engine();
        ~Engine();
        
        //Board texture
        Texture boardTexture;

        //Jewels textures
        Texture jewelTexture[Total];
        
        //Selector texture
        Texture selectorTexture;

        //Score texture
        Texture scoreTexture;
        Texture scoreFont;

        //Timer
        Timer timer;
        Texture timerTexture;
        Texture timerFont;

        //Game font;
        Texture gFont[2];

        void render();

        void renderClear(SDL_Rect* rect);
};

#endif