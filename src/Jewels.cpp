#include "Jewels.h"

Jewel::Jewel(const int &nRows, const int &nCols, int time) : GameBoard(nRows, nCols, time) 
{
    selected = pressed = hint = false;
    highscore = engine.savedHighscore;
}

void Jewel::randomize()
{
    randomized = true;
    //Board creation
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            board[i][j] = engine.getRandom();
        }
    }
    while(existMatch()){
        clear();
        refill();
    }
    randomized = false;
}

void Jewel::renderJewel()
{
    renderBoard();
    for(int x = 0; x < nRows; x++) {
        for(int y = 0; y < nCols; y++) {
            int COLOR = board[x][y];
            engine.jewelTexture[COLOR].renderTexture(&square[x][y]);
        }
    }
}

void Jewel::updateJewel()
{   
    renderJewel();
    engine.render();
}

bool Jewel::match3(const int &row, const int &col, const std::string &direction)
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

bool Jewel::existHint()
{
    vector<vector<int> > tempBoard = board;
    vector<vector<bool> > tempPending = pendingRemoval;
    for(int x = 0; x < nRows - 1; x++) {
        for(int y = 0; y < nCols - 1; y++) {
            //Horizontal check
            std::swap(board[x][y], board[x+1][y]);
            if(existMatch()) {
                //Set hint position
                hintX = x; hintY = y; hintX_ = x+1; hintY_ = y;
                board = tempBoard;
                pendingRemoval = tempPending;
                return true;
            }
            else board = tempBoard;
            
            //Vertical check
            std::swap(board[x][y], board[x][y+1]);
            if(existMatch()) {
                //Set hint position
                hintX = x; hintY = y; hintX_ = x; hintY_ = y+1;
                board = tempBoard;
                pendingRemoval = tempPending;
                return true;
            }
            else board = tempBoard;
        }
    }
    return false;
}

void Jewel::displayHint()
{
    engine.hintTexture.renderTexture(&square[hintX][hintY]);
    engine.hintTexture.renderTexture(&square[hintX_][hintY_]);
}

void Jewel::renderSelector(int selectedX, int selectedY, int x, int y)
{
    renderJewel();
    if(hint) {
        displayHint();
    }
    if(selected) {
        engine.selectorTexture.renderTexture(&square[selectedX][selectedY]);
    }
    if(pressed) {
        engine.selectorTexture.renderTexture(&square[x][y]);
    }
    engine.render();
}