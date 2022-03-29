#include "Jewels.h"

Jewel::Jewel(const int rows, const int cols) : GameBoard(rows, cols)
{
    //Initialize squares
    square.resize(nRows, vector<SDL_Rect>(nCols));
    int startX = 240, startY = 35;
    for(int row = 0; row < nRows; row++){
        for(int col = 0; col < nCols; col++){
            square[row][col].x = col * 65 + startX;
            square[row][col].y = row * 65 + startY;
            square[row][col].w = 65;
            square[row][col].h = 65;
        }
    }
    //Initialize texture
    jewelTexture[Destroyed] = NULL;
    jewelTexture[Red] = IMG_LoadTexture(renderer, "assets/gemRed.png");
    jewelTexture[Green] = IMG_LoadTexture(renderer, "assets/gemGreen.png");
    jewelTexture[Blue] = IMG_LoadTexture(renderer, "assets/gemBlue.png");
    jewelTexture[Orange] = IMG_LoadTexture(renderer, "assets/gemOrange.png");
    jewelTexture[White] = IMG_LoadTexture(renderer, "assets/gemWhite.png");
    for(int i = 1; i < Total; i++){
        if(jewelTexture[i] == NULL){
            LogIMG("IMG_Load");
        }
    }
}

Jewel::~Jewel()
{
    for(int i = 0; i < Total; i++){
        SDL_DestroyTexture(jewelTexture[i]);
        jewelTexture[i] = NULL;
    }
}

void Jewel::renderJewel()
{
    updateBoard();
    for(int x = 0; x < nRows; x++) {
        for(int y = 0; y < nCols; y++) {
            int COLOR = board[x][y];
            SDL_RenderCopy(renderer, jewelTexture[COLOR], NULL, &square[x][y]);
        }
    }
}

void Jewel::updateJewel()
{   
    renderJewel();
    SDL_RenderPresent(renderer);
}