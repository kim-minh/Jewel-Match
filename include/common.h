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

//Check if forced to quit
extern bool forceQuit;

//Change mode selection
extern int selectChange;

//Game mode
extern int gameMode;
extern std::string game_mode[];
//Time mode
extern int timeMode;
extern int time_mode[];

//High score
extern Sint32* highscore;

#endif