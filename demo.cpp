#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "TEST";

void moving(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Rect &abcd);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(ostream& os, const string &msg, bool fatal);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    initSDL(window, renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    SDL_Rect abcd;
    abcd.x=0;
    abcd.y=0;
    abcd.w=120;
    abcd.h=80;
    SDL_RenderFillRect(renderer, &abcd);
    SDL_RenderPresent(renderer);
    moving(window,renderer,abcd);
    quitSDL(window, renderer);
    waitUntilKeyPressed();

    return 0;
}

void moving(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Rect &abcd)
{
    bool isRunning = true;
    SDL_Event e;
    while(isRunning){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT) isRunning = false;
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym)
                {
                case SDLK_DOWN:
                    if(abcd.y+10+abcd.h<=SCREEN_HEIGHT){
                        abcd.y+=10;

                    }
                    else abcd.y=0;
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                    SDL_RenderFillRect(renderer, &abcd);
                    SDL_RenderPresent(renderer);
                    break;
                case SDLK_RIGHT:
                    if(abcd.x+10+abcd.w<=SCREEN_WIDTH){
                        abcd.x+=10;
                    }
                    else abcd.x=0;

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                    SDL_RenderFillRect(renderer, &abcd);
                    SDL_RenderPresent(renderer);
                    break;
                case SDLK_UP:
                    if(abcd.y-10>=0){
                        abcd.y-=10;
                    }
                    else abcd.y = SCREEN_HEIGHT - abcd.h;
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                    SDL_RenderFillRect(renderer, &abcd);
                    SDL_RenderPresent(renderer);
                    break;
                case SDLK_LEFT:
                    if(abcd.x-10>=0){
                        abcd.x-=10;
                    }
                    else abcd.x = SCREEN_WIDTH - abcd.w;
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                    SDL_RenderFillRect(renderer, &abcd);
                    SDL_RenderPresent(renderer);
                    break;
                }
            }
        }
    }
}

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(10);
    }
}
