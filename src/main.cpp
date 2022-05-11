#include "Game.h"
#define VERSION 2.5.10

/* 
    v2.5.10 changelog:
    - Revert back to SDL_Delay and fix some warnings
*/

int main(int argc, char* args[])
{
    Game game(8, 8, 120);
    return 0;
}