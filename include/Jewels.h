#ifndef JEWELS_H
#define JEWELS_H
#include "GameBoard.h"

class Jewel : public GameBoard
{
    protected:
        //Jewel textures
        SDL_Texture* jewelTexture[Total];
        //Squares that hold jewel
        vector<vector<SDL_Rect> > square;
    public:
        Jewel(const int rows, const int cols);
        ~Jewel();

        //Render Jewels
        void renderJewel();
        void updateJewel();
};

#endif