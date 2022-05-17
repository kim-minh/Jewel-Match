#ifndef ENGINE_H
#define ENGINE_H
#include "Timer.h"
#include "Texture.h"
#include "Text.h"
#include "Sound.h"

//Jewels in squares
enum Jewels {Destroyed, Red, Green, Blue, Orange, Yellow, Purple, White, Total};

//Game modes
enum GameModes {Time, Zen, Endless, Total_Mode};
//Time modes
enum TimeModes {OneMinute, TwoMinutes, FiveMinutes, Total_Time};

class Engine
{
    private:
        //Window size
        const int WINDOW_WIDTH, WINDOW_HEIGHT;

        //Window title
        const std::string TITLE;

        //Custom mouse cursor
        SDL_Cursor *cursor;

        bool success;

        //Initialize Engine
        bool init();
        //Initialize Texture
        bool initTexture();
        //Initialize Font
        bool initFont();
        //Initialiize Sound
        bool initSound();

        //Read save data
        void initSave();
        //Save high score to disk
        bool save();

        void exit();

    public:
        Engine();
        ~Engine();

        //Saved high score from disk
        Sint32 savedHighscore[Total_Mode][Total_Time];

        Timer timer;
        
        //Textures
        Texture boardTexture; //Board texture
        Texture jewelTexture[Total]; //Jewels textures
        Texture selectorTexture; //Selector texture
        Texture hintTexture; // Hint texture
        Texture scoreTexture; //Score texture
        Texture timerTexture; //Timer texture
        Texture highlightTexture; //Highlight selection texture
        Texture exitTexture; //Exit texture
        Texture startTexture; //Start screen texture
        Texture endTexture; //End screen texture

        //Texts
        Text gameModeText; //Game modes
        Text timeModeText; //Time modes
        Text scores; //Score
        Text highscores; //High score
        Text times; //Remaing time
        Text scoreText; // "score" text
        Text highscoreText; //"high score" text
        Text timeText; // "time" text
        Text startNotice; // "START" notice text
        
        //Sounds
        Sound music;
        Sound startSFX;
        Sound endSFX;
        Sound matchSFX[3];

        //Generate random number
        int getRandom();

        //Update screen
        void render();
};

#endif