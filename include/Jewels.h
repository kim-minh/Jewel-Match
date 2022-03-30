#ifndef JEWELS_H
#define JEWELS_H
#include "GameBoard.h"

class Jewel : protected GameBoard
{
    private:
        //Jewels textures
        SDL_Texture* jewelTexture[Total];
        friend class Game;

        Jewel(const int& rows, const int& cols);
        ~Jewel();

        //Render jewels
        void renderJewel();

        //Update jewels state
        void updateJewel();

        //Randomize jewels
        void randomize();

        //Check if 3 jewels are matching
        bool match3(const int& row, const int& col, const std::string& direction);
        
        //Check if exists at least 3 jewels matched
        bool existMatch();
};

#endif