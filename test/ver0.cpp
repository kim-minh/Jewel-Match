/*
Version 0.5
Bare-bones version without graphics
*/
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

const int row = 8;
const int col = 8;

//Initialize 8x8 board
int board[row][col];
int pendingRemoval[row][col];

enum Jewels{Destroyed, Red, Green, Blue, Orange, Yellow, Total};

//Display board
void display();

//Check match
bool matched(int x, int y, int stepX, int stepY);
bool existsMatch(){
    bool exist = false;
    //Horizontal match
    for(int x = 0; x < row; x++){
        for(int y = 0; y < col - 2; y++){
            if(matched(x, y, 0, 1)){
                exist = true;
            }
        }
    }
    //Vertical match
    for(int x = 0; x < row - 2; x++){
        for(int y = 0; y < col; y++){
            if(matched(x, y, 1, 0)){
                exist = true;
            }
        }    
    }
    return exist;
}

//Remove matching jewels
void remove();

//Fill destroyed jewel
void fill();

int main(){
    srand(time(0));
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            board[i][j] = rand() % (Total-1) + 1;
        }
    }
    display();
    bool running = true;
    int x1, y1, x2, y2;
    while(running){
        while(existsMatch()){
            remove();
            display();
            fill();
            display();
        }
        cout << "Select first square: ";
        cin >> x1 >> y1;
        cout << "Select second square: ";
        cin >> x2 >> y2;
        swap(board[x1][y1], board[x2][y2]);
        if(!existsMatch()){
            swap(board[x1][y1], board[x2][y2]);
            cout << "Invalid move!\n";
        }
    }
}

void display(){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << setfill('_') << setw(15) << '_' << "\n\n";
}

bool matched(int x, int y, int stepX, int stepY){
    //Starting value
    const int start = board[x][y];
    for(int i = 1; i < 3; i++){
        if(board[x + i*stepX][y + i*stepY] != start){
            return false;
        }
    }
    for(int i = 0; i < 3; i++){
        pendingRemoval[x + i*stepX][y + i*stepY] = 1;
    }
    return true;
}

void remove(){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(pendingRemoval[i][j] == 1){
                board[i][j] = Destroyed;
            }
        }
    }
}

void fill(){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(board[i][j] == Destroyed){
                board[i][j] = rand() % (Total-1) + 1;
            }
        }
    }
    memset(pendingRemoval, 0, sizeof(pendingRemoval));
}
