#ifndef ENGINE_H
#define ENGINE_H
#include "Timer.h"
#include "Texture.h"
#include "Text.h"
#include "Sound.h"

//Jewels in squares
enum Jewels{Destroyed, Red, Green, Blue, Orange, Yellow, Purple, White, Total};

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

        //Initialiize Sound
        bool initSound();

        void exit();

    public:
        Engine();
        ~Engine();

        Timer timer;
        
        //Textures
        Texture boardTexture; //Board texture
        Texture jewelTexture[Total]; //Jewels textures
        Texture selectorTexture; //Selector texture
        Texture hintTexture; // Hint texture
        Texture scoreTexture; //Score texture
        Texture timerTexture; //Timer texture
        Texture startTexture; //Start screen texture
        Texture endTexture; //End screen texture

        //Texts
        Text score; //Score
        Text times; //Remaing time
        Text scoreText; // "score" text
        Text timeText; // "time" text
        
        //Sounds
        Sound music;
        Sound startSFX;
        Sound endSFX;
        Sound matchSFX[3];

        //Update screen
        void render();
};

#endif