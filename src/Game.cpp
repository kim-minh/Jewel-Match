#include "Game.h"

Game::Game(const int &nRows, const int &nCols) : jewel(nRows, nCols), nRows(nRows), nCols(nCols)
{
    running = true;
    startGame();

    x = y = 0;
    run();
}

void Game::startGame()
{
    while(running && SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT)
            running = false;
        else {
            jewel.renderStart();
            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&mousePos.x, &mousePos.y);
                if(forceQuit) {
                    if(SDL_PointInRect(&mousePos, &jewel.continueSelect)) {
                        selectChange = ContinueSelection;
                        if(e.type == SDL_MOUSEBUTTONDOWN) {
                            start();
                            return;
                        }
                    }
                }
                if(SDL_PointInRect(&mousePos, &jewel.newGameSelect)) {
                    selectChange = NewGameSelection;
                    if(e.type == SDL_MOUSEBUTTONDOWN) {
                        forceQuit = false;
                        start();
                        return;
                    }
                }
                else if(SDL_PointInRect(&mousePos, &jewel.modeSelect)) {
                    selectChange = GameSelection;
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                        gameMode = (gameMode + 1) % Total_Mode;
                }
                else if(gameMode == Time && SDL_PointInRect(&mousePos, &jewel.timeSelect)) {
                    selectChange = TimeSelection;
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                        timeMode = (timeMode + 1) % Total_Time;
                }
            }
            else if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_s: case SDLK_DOWN:
                        selectChange = (selectChange + 1) % Total_Selection;
                        break;

                    case SDLK_w: case SDLK_UP:
                        selectChange = (Total_Selection + (selectChange - 1)) % Total_Selection;
                        break;

                    case SDLK_RIGHT: case SDLK_d:
                        if(selectChange == GameSelection)
                            gameMode = (gameMode + 1) % Total_Mode;
                        else if(selectChange == TimeSelection) 
                            timeMode = (timeMode + 1) % Total_Time;
                        break;
                    
                    case SDLK_LEFT: case SDLK_a:
                        if(selectChange == GameSelection)
                            gameMode = (Total_Mode + (gameMode - 1)) % Total_Mode;
                        else if(selectChange == TimeSelection)
                            timeMode = (Total_Time + (timeMode - 1)) % Total_Time;
                        break;
 
                    case SDLK_RETURN:
                        start();
                        return;
                }
            }
        }
    }
}

void Game::endGame()
{
    jewel.engine.music.stopMusic();
    if(forceQuit) {
        startGame();
        return;
    }
    else {
        jewel.renderEnd();
        jewel.engine.endSFX.playSFX();
    }
    while(SDL_WaitEvent(&e)) {
        if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_ESCAPE) {
                startGame();
                return;
            }
            else if(e.key.keysym.sym == SDLK_RETURN) {
                start();
                return;
            }
        }
    }
}

void Game::start()
{
    gameover = false;
    if(gameMode == Time)
        highscore = &jewel.engine.savedHighscore[Time][timeMode];
    else highscore = &jewel.engine.savedHighscore[gameMode][0];

    jewel.engine.startSFX.playSFX();
    jewel.startNotice();
    jewel.engine.music.playMusic();
    timerID = SDL_AddTimer(1000, callback, NULL);
    jewel.randomize();
    jewel.updateJewel();
}

void Game::run()
{
    while(running && SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT) {
            running = false;
            forceQuit = true;
            jewel.saveState();
        }
        if(gameover) {
            jewel.hint.stop();
            jewel.needHint = false;
            SDL_RemoveTimer(timerID);
            if(!jewel.existMatch()) {
                SDL_Delay(400);
            }
            endGame();
        }
        else if(!jewel.existHint()) {
            if(gameMode == Zen)
                gameover = true; 
            else jewel.randomize();
        }
        else {
            if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_ESCAPE)
                    gameover = true;
                else if(!pressed) {
                    pressed = true;
                }
                else keyControl();
                jewel.renderSelector(selectedX, selectedY, x, y);
                jewel.updateGame();
            }
            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                pressed = true;
                SDL_GetMouseState(&mousePos.x, &mousePos.y);
                if(e.type == SDL_MOUSEBUTTONDOWN && SDL_PointInRect(&mousePos, &jewel.exit)) {
                    gameover = forceQuit = true;
                    jewel.saveState();
                }
                for(int x_ = 0; x_ < nRows; x_++) {
                    for(int y_ = 0; y_ < nCols; y_++) {
                        if(SDL_PointInRect(&mousePos, &jewel.square[x_][y_])) {
                            x = x_;
                            y = y_;
                            mouseControl();
                            jewel.renderSelector(selectedX, selectedY, x, y);
                            jewel.updateGame();
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
    switch(e.key.keysym.sym) {
        case SDLK_UP: case SDLK_w:
            x--;
            if(selected) {
                y = selectedY;
                if(x < 0)
                    x = selectedX;
                if(x != selectedX)
                    x = selectedX - 1;
            }
            else x = (nRows + x) % nRows;
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
            else x = x % nRows;
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
            else y = (nCols + y) % nCols;
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
            else y = y % nCols;
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
            if(!jewel.existMatch()) {
                std::swap(jewel.board[selectedX][selectedY], jewel.board[x][y]);
                jewel.updateJewel();
            }
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
        (x > selectedX && y > selectedY) || (x < selectedX && y < selectedY) ||
        (x > selectedX && y < selectedY) || (x < selectedX && y > selectedY))
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