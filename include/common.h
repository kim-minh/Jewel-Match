#ifndef COMMON_H
#define COMMON_H
#include <SDL2/SDL.h>
#include <string>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

//Game state
extern bool gameover;

//Check if a jewel was selected
extern bool pressed, selected;

#endif