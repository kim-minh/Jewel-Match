#include "Game.h"
#define VERSION 2.0

/* 
    v2.0 changelog:
    - Update game font
    - Remove unused fonts and images
    - Add start screen and game over screen
    - Split Texture into another Text class
    - Replace SDL_Delay with SDL_GetTick
    - Add additional jewels
    - Other optimizations
*/

int main(int argc, char* args[])
{
    Game game(8, 8);
    return 0;
}