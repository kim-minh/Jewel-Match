#include "Game.h"

Game::Game(const int& nRows, const int& nCols) : jewel(nRows, nCols)
{
    x = y = 0;
    running = true;

    jewel.randomize();
    jewel.updateJewel();
    loop();
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
            if(!jewel.pressed){
                jewel.pressed = true;
            }
            else swapJewels();
            jewel.renderSelector(selectedX, selectedY, x, y);
            updateGame();
        }
    }
}

void Game::swapJewels()
{
    switch(e.key.keysym.sym){
        case SDLK_UP: case SDLK_w:
            x--;
            if(jewel.selected) {
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
            if(jewel.selected) {
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
            if(jewel.selected) {
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
            if(jewel.selected) {
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
            if(!jewel.selected) {
                selectedX = x, selectedY = y;
                jewel.selected = true;
            }
            else {
                if(x != selectedX || y != selectedY) {
                    std::swap(jewel.board[selectedX][selectedY], jewel.board[x][y]);
                    jewel.updateJewel();
                    SDL_Delay(300);
                    if(!jewel.existMatch()) {
                        std::swap(jewel.board[selectedX][selectedY], jewel.board[x][y]);
                        jewel.updateJewel();
                        SDL_Delay(300);
                    }
                    x = y = 0;
                    jewel.pressed = false;
                }
                else {
                    x = selectedX;
                    y = selectedY;
                    jewel.pressed = true;
                }
                jewel.selected = false;
            }
            break;
        
    }
}