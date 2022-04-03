#ifndef COMMON_H
#define COMMON_H
#include <SDL2/SDL.h>

//Jewels in squares
enum Jewels{Destroyed, Red, Green, Blue, Orange, White, Total};

extern SDL_Window* window;
extern SDL_Renderer* renderer;

#endif