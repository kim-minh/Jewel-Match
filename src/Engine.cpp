#include "Engine.h"
#include "Log.h"
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
        Error("Unable to load Fonts!");
        exit();
    }
    else if(!initSound()) {
        Error("Unable to load Sounds!");
        exit();
    }
    else initSave();
}

Engine::~Engine()
{
    if(!save()) {
        Error("Your data will not be saved!");
    }
    exit();
}

bool Engine::init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
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

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
        LogMixer("Mixer_OpenAudio");
        success = false;
    }

    window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        LogSDL("CreateWindow");
        success = false;
    }

    icon = IMG_Load("assets/gemBlue.png");
    if(icon == NULL) {
        LogIMG("IMG_Load");
        success = false;
    }
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        LogSDL("CreateRenderer");
        success = false;
    }

    cursorSurface = IMG_Load("assets/cursor.png");
    if(cursorSurface == NULL) {
        LogIMG("IMG_Load");
        success = false;
    }
    cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
    if (cursor == NULL) {
        LogSDL("CreateColorCursor");
        success = false;
    }
    SDL_FreeSurface(cursorSurface);
    SDL_SetCursor(cursor);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    if( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		Error("Warning: Linear texture filtering not enabled!");
	}
    
    return success;
}

bool Engine::initTexture()
{
    if( boardTexture.loadFile("assets/Background.png") &&
        jewelTexture[Red].loadFile("assets/gemRed.png") &&
        jewelTexture[Green].loadFile("assets/gemGreen.png") &&
        jewelTexture[Blue].loadFile("assets/gemBlue.png") &&
        jewelTexture[Orange].loadFile("assets/gemOrange.png") &&
        jewelTexture[Yellow].loadFile("assets/gemYellow.png") &&
        jewelTexture[Purple].loadFile("assets/gemPurple.png") &&
        jewelTexture[White].loadFile("assets/gemWhite.png") &&
        selectorTexture.loadFile("assets/selector.png") &&
        hintTexture.loadFile("assets/hint.png") &&
        scoreTexture.loadFile("assets/scoreBackground.png") &&
        timerTexture.loadFile("assets/timeBackground.png") &&
        startTexture.loadFile("assets/startBackground.png") &&
        endTexture.loadFile("assets/endBackground.png"))
    return true;

    else return false;
}

bool Engine::initFont()
{
    //Open font
    if( !scoreText.openFont(30) || !highscoreText.openFont(30) || !timeText.openFont(30) ||
        !scores.openFont(35) || !highscores.openFont(35) || !times.openFont(75) || !startNotice.openFont(100))
    return false;

    //Load static text
    else if(!scoreText.loadText("score") || !highscoreText.loadText("high score") || 
            !timeText.loadText("time") || !startNotice.loadText("START"))
        return false;

    else return true;
}

bool Engine::initSound()
{
    if( !music.loadMusic("assets/music.ogg") || !matchSFX[0].loadSFX("assets/match1.ogg") ||
        !matchSFX[1].loadSFX("assets/match2.ogg") || !matchSFX[2].loadSFX("assets/match3.ogg") ||
        !startSFX.loadSFX("assets/gamestart.ogg") || !endSFX.loadSFX("assets/gameover.ogg"))
    return false;

    else return true;
}

void Engine::initSave()
{
    SDL_RWops* save = SDL_RWFromFile("save.bin", "r+b");
    if(save == NULL) {
        Error("Warning: Unable to open save file!");
        //Initialize data
        savedHighscore = 0;    
    }
    //File exists
    else {
        //Load data
        SDL_RWread(save, &savedHighscore, sizeof(Sint32), 1);

        //Close file handler
        SDL_RWclose(save);
    }
}

bool Engine::save()
{
    SDL_RWops* save = SDL_RWFromFile("save.bin", "r+b");
    if(save == NULL) {
        //Create file for writing
        save = SDL_RWFromFile("save.bin", "w+b");
    }
    if(save != NULL ) {
        //Write to save file
        SDL_RWwrite(save, &highscore, sizeof(Sint32), 1 );

        //Close file handler
        SDL_RWclose(save);
    }
    else {
        LogSDL("Save");
        return false;
    }
    return true;
}

void Engine::exit()
{
    SDL_FreeCursor(cursor);
    cursor = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Engine::render()
{
    SDL_RenderPresent(renderer);
}