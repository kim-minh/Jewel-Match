#include "Jewels.h"

Jewel::Jewel(const int& nRows, const int& nCols) : GameBoard(nRows, nCols) 
{
    selected = pressed = false;
}

void Jewel::randomize(){
    //Board creation
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            board[i][j] = rand() % (Total-1) + 1;
        }
    }
    while(existMatch()){
        clear();
        refill();
        score = 0;
    }
}

void Jewel::renderJewel()
{
    renderBoard(score);
    for(int x = 0; x < nRows; x++) {
        for(int y = 0; y < nCols; y++) {
            int COLOR = board[x][y];
            engine.jewelTexture[COLOR].render(&square[x][y]);
        }
    }
}

void Jewel::updateJewel()
{   
    renderJewel();
    engine.render();
}

bool Jewel::match3(const int& row, const int& col, const std::string& direction)
{
    int stepX, stepY;
    if(direction == "HORIZONTAL") {
        stepX = 0, stepY = 1;
    }
    else if(direction == "VERTICAL") {
        stepX = 1, stepY = 0;
    }
    
    //Starting value
    const int start = board[row][col];
    for(int i = 1; i < 3; i++) {
        if(board[row + i*stepX][col + i*stepY] != start) {
            return false;
        }
    }

    //Mark jewels to be removed
    for(int i = 0; i < 3; i++) {
        pendingRemoval[row + i*stepX][col + i*stepY] = true;
    }
    return true;
}

bool Jewel::existMatch()
{
    bool exist = false;

    //Horizontal match
    for(int row = 0; row < nRows; row++) {
        for(int col = 0; col < nCols - 2; col++) {
            if(match3(row, col, "HORIZONTAL")) {
                exist = true;
            }
        }
    }

    //Vertical match
    for(int row = 0; row < nRows - 2; row++) {
        for(int col = 0; col < nCols; col++) {
            if(match3(row, col, "VERTICAL")) {
                exist = true;
            }
        }    
    }
    return exist;
}

void Jewel::renderSelector(int selectedX, int selectedY, int x, int y)
{
    renderJewel();
    if(selected){
        engine.selectorTexture.render(&square[selectedX][selectedY]);
    }
    if(pressed) {
        engine.selectorTexture.render(&square[x][y]);
    }
    engine.render();
}