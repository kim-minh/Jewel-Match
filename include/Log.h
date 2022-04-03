#ifndef LOG_H
#define LOG_H
#include <string>

//Log SDL error
void LogSDL(const std::string msg);

//Log SDL_Image error
void LogIMG(const std::string msg);

//Log SDL_ttf error
void LogTTF(const std::string msg);

//Error message
void Error(const std::string msg);

#endif