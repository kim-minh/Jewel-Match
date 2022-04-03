#ifndef ENGINE_H
#define ENGINE_H
#include "Texture.h"

class Engine
{
    private:
        //Window size
        const int WINDOW_WIDTH, WINDOW_HEIGHT;

        //Window title
        const std::string TITLE;

        //Window icon
        SDL_Surface* icon;

        //Font
        TTF_Font* gFont;

        //Initialize Engine
        bool init();

        //Initialize Texture
        bool initTexture();

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

        //Font texture;
        Texture font;

        void render();

        void renderClear();
};

#endif