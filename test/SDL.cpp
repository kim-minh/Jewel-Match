#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

/*
Version 0.8
Have graphic and can swap jewel
No matching algorithm yet
*/

const int HEIGHT = 600;
const int WIDTH = 800;
const char TITLE[] = "SDL_Test";

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture[5];
SDL_Rect rect[8][8];

void update(int board[8][8])
{
    SDL_RenderClear(renderer);
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            int color = board[i][j];
            SDL_RenderCopy(renderer, texture[color], NULL, &rect[i][j]);
        }
    }
    SDL_RenderPresent(renderer);
}

void quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    for(int i = 0; i < 5; i++){
        SDL_DestroyTexture(texture[i]);
        texture[i] = NULL;
    }
    renderer = NULL;
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(){
    srand(time(NULL));
    int n;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(renderer);
    texture[0] = IMG_LoadTexture(renderer, "assets/gemRed.png");
    texture[1] = IMG_LoadTexture(renderer, "assets/gemGreen.png");
    texture[2] = IMG_LoadTexture(renderer, "assets/gemBlue.png");
    texture[3] = IMG_LoadTexture(renderer, "assets/gemOrange.png");
    texture[4] = IMG_LoadTexture(renderer, "assets/gemWhite.png");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    int startX = 150, startY = 30;
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            rect[x][y].x = x * 65 + startX;
            rect[x][y].y = y * 65 + startY;
            rect[x][y].w = 65;
            rect[x][y].h = 65;
        }
    }

    int board[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = rand() % 5;
        }
    }
    update(board);

    SDL_Event e;
    bool running = true;
    int x = 0, y = 0;
    int* pos1 = NULL;
    int* pos2 = NULL;
    bool pressed = false;
    while(running){
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT)
                running = false;
            if(e.type == SDL_KEYDOWN) {
                if(!pressed){
                    std::cout << "Select coordinate: (" << x << ',' << y << ")\n";
                    pressed = true;
                }
                else {
                    switch(e.key.keysym.sym){
                        case SDLK_UP:
                            x--;
                            std::cout << "Select coordinate: (" << x << ',' << y << ")\n";
                            break;
                        case SDLK_DOWN:
                            x++;
                            std::cout << "Select coordinate: (" << x << ',' << y << ")\n";
                            break;
                        case SDLK_LEFT:
                            y--;
                            std::cout << "Select coordinate: (" << x << ',' << y << ")\n";
                            break;
                        case SDLK_RIGHT:
                            y++;
                            std::cout << "Select coordinate: (" << x << ',' << y << ")\n";
                            break;
                        case SDLK_RETURN:
                            if(pos1 == NULL){
                                pos1 = &board[y][x];
                                std::cout << "Selected 1st coordinate: (" << x << ',' << y << ")\n\n";
                            }
                            else if(pos2 == NULL){
                                pos2 = &board[y][x];
                                std::cout << "Selected 2nd coordinate: (" << x << ',' << y << ")\n\n";
                            }
                            else{
                                std::swap(*pos1, *pos2);
                                std::cout << "Swapped\n\n";
                                pos1 = pos2 = NULL;
                                x = y = 0;
                                pressed = false;
                            }
                            break;
                    }
                }
            }
        }
        update(board);
    }
    quit();
}