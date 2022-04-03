#include "Engine.h"
#include <cstdlib>
#include <ctime>

Engine::Engine() : WINDOW_WIDTH(800), WINDOW_HEIGHT(600), TITLE("Jewel Match")
{
    srand(time(NULL));
    success = true;
    if( !init() ) {
        Error("Unable to initialize Engine!");
        exit();
    }
    else if(!initTexture()) {
        Error("Unable to load Textures!");
        exit();
    }
    else if(!initFont()) {
        Error("Unable to load Font!");
        exit();
    }
}

Engine::~Engine()
{
    exit();
}

bool Engine::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        LogSDL("SDL_Init");
        success = false;
    }

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
        LogIMG("IMG_Init");
        success = false;
    }

    if(TTF_Init() == -1) {
        LogTTF("TTF_Init");
        success = false;
    }

    window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        LogSDL("CreateWindow");
        success = false;
    }

    icon = IMG_Load("assets/icon.png");
    if(icon == NULL){
        LogIMG("IMG_Load");
        success = false;
    }
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        LogSDL("CreateRenderer");
        success = false;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    return success;
}

bool Engine::initTexture()
{
    if( boardTexture.loadFile("assets/Background.png") && //Initialize board texture
        jewelTexture[Red].loadFile("assets/gemRed.png") && //Initialize jewels texture
        jewelTexture[Green].loadFile("assets/gemGreen.png") &&
        jewelTexture[Blue].loadFile("assets/gemBlue.png") &&
        jewelTexture[Orange].loadFile("assets/gemOrange.png") &&
        jewelTexture[White].loadFile("assets/gemWhite.png") &&
        selectorTexture.loadFile("assets/selector.png") && //Initialize selector texture
        scoreTexture.loadFile("assets/scoreBackground.png")) //Initialize score texture
    return true;
    else return false;
}

bool Engine::initFont()
{
    letterFont.font = TTF_OpenFont("assets/fuenteNormal.ttf", 40);
    if(letterFont.font == NULL) {
        LogTTF("TTF_OpenFont");
        success = false;
    }
    numberFont.font = TTF_OpenFont("assets/fuentelcd.ttf", 35);
    if(numberFont.font == NULL) {
        LogTTF("TTF_OpenFont");
        success = false;
    }
    return success;
}

void Engine::exit()
{
    TTF_CloseFont(letterFont.font);
    TTF_CloseFont(numberFont.font);
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Engine::render()
{
    SDL_RenderPresent(renderer);
}

void Engine::renderClear()
{
    SDL_RenderClear(renderer);
}