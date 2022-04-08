#include "Game.h"

Game::Game(const int &nRows, const int &nCols, int time) : jewel(nRows, nCols, time), nRows(nRows), nCols(nCols)
{
    gameStarted = false;
    running = true;

    startGame();

    x = y = 0;
    run();
}

void Game::startGame()
{
    while(!gameStarted && running && SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT)
            running = false;
        else {
            jewel.renderStart();
            if(e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE)) {
                start();
            }
        }
    }
}

void Game::endGame()
{
    if(gameStarted) {
        gameStarted = false;
        jewel.renderEnd();
        jewel.engine.endSFX.playSFX();
        jewel.engine.music.stopMusic();
    }
    if(e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_SPACE)) {
        gameover = false;
        start();
    }
}

void Game::start()
{
    jewel.engine.startSFX.playSFX();
    while(delay.countdown(1000));
    jewel.startNotice();
    while(delay.countdown(1000));
    gameStarted = true;
    jewel.engine.music.playMusic();
    timerID = SDL_AddTimer(1000, callback, NULL);
    jewel.randomize();
    jewel.updateJewel();
}

void Game::updateGame()
{
    int count = 0;
    while(jewel.existMatch()) {
        //Stop hint timer because matched
        hint.stop();
        jewel.hint = false;

        //Choose which sfx to play
        count++;
        if(count == 1) {
            jewel.engine.matchSFX[0].playSFX();
        }
        else if(count == 2) {
            jewel.engine.matchSFX[1].playSFX();
        }
        else jewel.engine.matchSFX[2].playSFX();

        //Matching actions
        jewel.clear();
        jewel.updateJewel();
        while(delay.countdown(700));
        jewel.refill();
        jewel.updateJewel();
    }
}

void Game::run()
{
    while(running && SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT)
            running = false;
        if(!jewel.existHint()) {
            jewel.randomize();
        }
        if(gameover) {
            SDL_RemoveTimer(timerID);
            hint.stop();
            if(!jewel.existMatch())
                endGame();
        }
        else {
            //Start hint timer, display hint if return false
            if(!hint.countdown(9000)) {
                jewel.hint = true;
            }
            if(e.type == SDL_KEYDOWN) {
                if(!pressed) {
                    pressed = true;
                }
                else keyControl();
                jewel.renderSelector(selectedX, selectedY, x, y);
                updateGame();
            }
            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                pressed = true;
                SDL_GetMouseState(&pos.x, &pos.y);
                for(int x_ = 0; x_ < nRows; x_++) {
                    for(int y_ = 0; y_ < nCols; y_++) {
                        if(SDL_PointInRect(&pos, &jewel.square[x_][y_])) {
                            x = x_;
                            y = y_;
                            mouseControl();
                            jewel.renderSelector(selectedX, selectedY, x, y);
                            updateGame();
                        }
                    }
                }
            }
            //TimerID event
            else jewel.renderSelector(selectedX, selectedY, x, y);
        }
    }
    SDL_RemoveTimer(timerID);
}

void Game::keyControl()
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
                x = nRows - x - 2;
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
            else if(x == nRows)
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
                y = nCols - y - 2;
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
            else if(y == nRows)
                y = 0;
            break;
            
        case SDLK_RETURN: case SDLK_SPACE:
            swapJewels();
            break;
        
    }
}

void Game::mouseControl()
{
    switch(e.type) {
        case SDL_MOUSEMOTION:
            if(selected) {
                if(!swapCheck())
                    pressed = false;
                if(click)
                    drag = true;
                else drag = false;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            click = true;
            if(drag) {
                selectedX = x;
                selectedY = y;
                selected = true;
            }
            else swapJewels();
            break;

        case SDL_MOUSEBUTTONUP:
            if(drag) {
                swapJewels();
            }
            else click = false;
            drag = false;
            break;
    }
}

void Game::swapJewels()
{
    if(!selected) {
        selectedX = x;
        selectedY = y;
        selected = true;
    }
    else {
        if(swapCheck()) {
            std::swap(jewel.board[selectedX][selectedY], jewel.board[x][y]);
            jewel.updateJewel();
            while(delay.countdown(300));
            if(!jewel.existMatch()) {
                std::swap(jewel.board[selectedX][selectedY], jewel.board[x][y]);
                jewel.updateJewel();
                while(delay.countdown(300));
            }
            else x = y = 0;
            pressed = false;
        }
        else {
            x = selectedX;
            y = selectedY;
            pressed = true;
        }
        selected = false;
    }
}

bool Game::swapCheck()
{
    if( x > selectedX + 1 || x < selectedX - 1 || 
        y > selectedY + 1 || y < selectedY - 1 ||
        x > selectedX && y > selectedY || x < selectedX && y < selectedY ||
        x > selectedX && y < selectedY || x < selectedX && y > selectedY)
        return false;
    else return true;
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