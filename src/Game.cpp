#include "Game.h"

Game::Game(const int& nRows, const int& nCols) : jewel(nRows, nCols)
{
    gameStarted = false;
    running = true;

    startGame();
    jewel.randomize();
    jewel.updateJewel();

    x = y = 0;
    loop();
}

void Game::startGame()
{
    while(!gameStarted && running && SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT)
            running = false;
        else {
            jewel.renderStart();
            if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_RETURN)
                    gameStarted = true;
            }
        }
    }
}

void Game::endGame()
{
    jewel.renderEnd();
    if(e.type == SDL_KEYDOWN) {
        if(e.key.keysym.sym == SDLK_RETURN) {
            jewel.randomize();
            jewel.gameOver = false;
            timerID = SDL_AddTimer(1000, callback, NULL);
            while(delay.countdown(750));
        }
    }
}

void Game::updateGame()
{
    while(jewel.existMatch()) {
        jewel.clear();
        jewel.updateJewel();
        while(delay.countdown(500));
        jewel.refill();
        jewel.updateJewel();
    }
}

Uint32 Game::callback(Uint32 interval, void* param)
{
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

void Game::loop()
{
    timerID = SDL_AddTimer(1000, callback, NULL);
    while(running && SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT)
            running = false;
        if(jewel.gameOver) {
            SDL_RemoveTimer(timerID);
            endGame();
        }
        else {
            if(e.type == SDL_KEYDOWN) {
                if(!jewel.pressed) {
                    jewel.pressed = true;
                }
                else swapJewels();
                jewel.renderSelector(selectedX, selectedY, x, y);
                updateGame();
            }
            else jewel.renderSelector(selectedX, selectedY, x, y);
        }
    }
    SDL_RemoveTimer(timerID);
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
                    while(delay.countdown(300));
                    if(!jewel.existMatch()) {
                        std::swap(jewel.board[selectedX][selectedY], jewel.board[x][y]);
                        jewel.updateJewel();
                        while(delay.countdown(300));
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