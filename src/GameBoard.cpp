#include "GameBoard.h"

GameBoard::GameBoard(const int rows, const int cols) : nRows(rows), nCols(cols)
{
    board.resize(nRows, vector<int>(nCols));
    pendingRemoval.resize(nRows, vector<bool>(nCols));
    boardTexture = IMG_LoadTexture(renderer, "assets/Background.png");
}

GameBoard::~GameBoard()
{
    SDL_DestroyTexture(boardTexture);
    boardTexture = NULL;
}

void GameBoard::randomize(){
    //Board creation
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            board[i][j] = rand() % (Total-1) + 1;
        }
    }
    while(existMatch()){
        clear();
        refill();
    }
}

void GameBoard::updateBoard()
{
    SDL_RenderClear(renderer);
    if(boardTexture == NULL){
        LogIMG("IMG_Load");
    }
    SDL_RenderCopy(renderer, boardTexture, NULL, NULL);
}

void GameBoard::clear()
{
    for(int row = 0; row < nRows; row++) {
        for(int col = 0; col < nCols; col++) {
            if(pendingRemoval[row][col]) {
                board[row][col] = Destroyed;
                pendingRemoval[row][col] = false;
            }
        }
    }
}

void GameBoard::refill()
{
    //Drop gems down
    for(int col = 0; col < nCols; col++) {
        for(int row = nRows - 1; row >=0; row--) {
            for(int _row = row - 1; _row >= 0; _row--) {
                if(board[row][col] == Destroyed && board[_row][col] != 0) {
                    swap(board[row][col], board[_row][col]);
                }
            }
        }
    }
    
    //Fill empty squares with new jewels
    for(int row = 0; row < nRows; row++) {
        for(int col = 0; col < nCols; col++) {
            if(board[row][col] == Destroyed) {
                board[row][col] = rand() % (Total-1) + 1;
            }
        }
    }
}

bool GameBoard::match3(int row, int col, const std::string& direction)
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
        pendingRemoval[row + i*stepX][col + i*stepY] = 1;
    }
    return true;
}

bool GameBoard::existMatch()
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