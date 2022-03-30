#include "Game.h"

Game::Game(const int& rows, const int& cols) : jewel(rows, cols)
{
    x = y = 0;
    running = true;
    selected = pressed = false;

    //Initialize selector
    selector = IMG_LoadTexture(jewel.renderer, "assets/selector.png");
    if(selector == NULL) {
        LogIMG("IMG_Load");
    }

    jewel.randomize();
    jewel.updateJewel();
    loop();
}

Game::~Game()
{
    SDL_DestroyTexture(selector);
    selector = NULL;
    IMG_Quit();
    SDL_Quit();
}

void Game::renderSelector()
{
    jewel.renderJewel();
    if(selected){
        SDL_RenderCopy(jewel.renderer, selector, NULL, &jewel.square[selectedX][selectedY]);
    }
    if(pressed) {
        SDL_RenderCopy(jewel.renderer, selector, NULL, &jewel.square[x][y]);
    }
    SDL_RenderPresent(jewel.renderer);
}

void Game::swapJewels()
{
    switch(e.key.keysym.sym){
        case SDLK_UP: case SDLK_w:
            x--;
            if(selected) {
                y = selectedY;
                if(x < 0)
                    x = selectedX;
                if(x != selectedX)
                    x = selectedX - 1;
            }
            else if(x == -1)
                x = jewel.nRows - x - 2;
            break;
        case SDLK_DOWN: case SDLK_s:
            x++;
            if(selected) {
                y = selectedY;
                if(x < 0)
                    x = selectedX;
                if(x != selectedX)
                    x = selectedX + 1;
            }
            else if(x == jewel.nRows)
                x = 0;
            break;
        case SDLK_LEFT: case SDLK_a:
            y--;
            if(selected) {
                x = selectedX;
                if(y < 0)
                    y = selectedY;
                if(y != selectedY)
                    y = selectedY - 1;
            }
            else if(y == -1)
                y = jewel.nCols - y - 2;
            break;
        case SDLK_RIGHT: case SDLK_d:
            y++;
            if(selected) {
                x = selectedX;
                if(y < 0)
                    y = selectedY;
                if(y != selectedY)
                    y = selectedY + 1;
            }
            else if(y == jewel.nRows)
                y = 0;
            break;
        case SDLK_RETURN: case SDLK_SPACE:
            if(!selected) {
                selectedX = x, selectedY = y;
                selected = true;
            }
            else {
                if(x != selectedX || y != selectedY) {
                    swap(jewel.board[selectedX][selectedY], jewel.board[x][y]);
                    jewel.updateJewel();
                    SDL_Delay(300);
                    if(!jewel.existMatch()) {
                        swap(jewel.board[selectedX][selectedY], jewel.board[x][y]);
                        jewel.updateJewel();
                        SDL_Delay(300);
                    }
                    x = y = 0;
                    pressed = false;
                }
                else {
                    x = selectedX;
                    y = selectedY;
                    pressed = true;
                }
                selected = false;
            }
            break;
        
    }
}

void Game::updateGame()
{
    while(jewel.existMatch()) {
        jewel.clear();
        jewel.updateJewel();
        SDL_Delay(500);
        jewel.refill();
        jewel.updateJewel();
    }
}

void Game::loop()
{
    while(running && SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT)
            running = false;
        if(e.type == SDL_KEYDOWN) {
            if(!pressed){
                pressed = true;
            }
            else swapJewels();
            renderSelector();
            updateGame();
        }
    }
}

