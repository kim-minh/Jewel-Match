#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Log.h"

void LogSDL(const char* msg){
    std::cout << msg << " Error: " << SDL_GetError() << '\n';
}
void LogIMG(const char* msg){
    std::cout << msg << " Error: " << IMG_GetError() << '\n';
}

void Error(const char* msg){
    std::cout << msg;
}