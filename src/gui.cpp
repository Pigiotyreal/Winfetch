#define SDL_MAIN_HANDLED

#include "inc/SDL2/SDL.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Winfetch", 100, 100, 1080, 720, SDL_WINDOW_SHOWN);

    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(win);

    if (surface == nullptr) {
        std::cout << "SDL_GetWindowSurface Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_UpdateWindowSurface(win);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
        }
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}