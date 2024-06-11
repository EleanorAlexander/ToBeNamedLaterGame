#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#define W_HEIGHT 500
#define W_WIDTH 700
#define GAME_NAME "to be named later"

// GLOBALS
SDL_Window *WINDOW;
SDL_Renderer *RENDERER;

int init(void) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failure. SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    WINDOW = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_WIDTH, W_HEIGHT, SDL_WINDOW_SHOWN);

    if (WINDOW == NULL) {
        printf("Window was not created. SDL Error %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
    if(RENDERER == NULL) {
        printf("Renderer was not created. SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) && imgFlags)) {
        printf("SDL_image could not be initialized. SDL Image Error: %s\n", IMG_GetError());
        return 1;
    }

    return 0;
}

void cleanup(void) {
    if(RENDERER)
        SDL_DestroyRenderer(RENDERER);
    if(WINDOW)
        SDL_DestroyWindow(WINDOW);
    IMG_Quit();
    SDL_Quit();
}

void gameLoop(void) {
    SDL_bool running = SDL_TRUE;
    
    while(running) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = SDL_FALSE;
            }
        }
        SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 0);
        SDL_RenderClear(RENDERER);
        SDL_RenderPresent(RENDERER);
    }

}

int main(void) {
    init();
    gameLoop();
    cleanup();
   return 0;
}