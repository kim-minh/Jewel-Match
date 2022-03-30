#ifndef JEWELS_H
#define JEWELS_H
#include "GameBoard.h"

class Jewel : protected GameBoard
{
    protected:
        //Jewels textures
        SDL_Texture* jewelTexture[Total];

        //Squares that hold jewel
        vector<vector<SDL_Rect> > square;

        //Render jewels
        void renderJewel();

        //Update jewels state
        void updateJewel();

    public:
        Jewel(const int rows, const int cols);
        ~Jewel();
};

#endif