#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Log.h"
using namespace std;
void Log::SDL(const string& msg){
    cout << msg << " Error: " << SDL_GetError();
}
void Log::IMG(const string& msg){
    cout << msg << " Error: " << IMG_GetError();
}