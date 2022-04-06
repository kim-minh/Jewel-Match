#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Log.h"

void LogSDL(const std::string msg) {
    std::cerr << msg << " Error: " << SDL_GetError() << '\n';
}

void LogIMG(const std::string msg) {
    std::cerr << msg << " Error: " << IMG_GetError() << '\n';
}

void LogTTF(const std::string msg) {
    std::cerr << msg << " Error: " << TTF_GetError() << '\n';
}

void LogMixer(const std::string msg) {
    std::cerr << msg << " Error: " << Mix_GetError() << '\n';
}

void Error(const std::string msg) {
    std::cerr << msg << '\n';
}