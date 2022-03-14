#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int main(){
    srand(time(0));
    enum Jewels{Red, Green, Blue, Orange, Yellow, Total};
    int board[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = rand() % Total;
        }
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
}