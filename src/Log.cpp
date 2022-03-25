#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Log.h"

void Log::SDL(const std::string& msg){
    std::cout << msg << " Error: " << SDL_GetError();
}
void Log::IMG(const std::string& msg){
    std::cout << msg << " Error: " << IMG_GetError();
}