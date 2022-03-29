#include "Engine.h"
#include <cstdlib>
#include <ctime>

Engine::Engine() : WINDOW_WIDTH(800), WINDOW_HEIGHT(600), TITLE("Jewel Match")
{
    time_t current = time(NULL);
    srand(current);
    if(!init()){
        Error("Unable to initialize Engine");
    }
}

Engine::~Engine()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
}

bool Engine::init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        LogSDL("SDL_Init");
        success = false;
    }

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        LogIMG("IMG_Init");
        success = false;
    }

    window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        LogSDL("CreateWindow");
        success = false;
    }

    icon = IMG_Load("assets/gemBlue.png");
    if(icon == NULL){
        LogIMG("IMG_Load");
        success = false;
    }
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if(renderer == NULL){
        LogSDL("CreateRenderer");
        success = false;
    }
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    return success;
}