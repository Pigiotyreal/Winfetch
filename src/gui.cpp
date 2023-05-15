#define SDL_MAIN_HANDLED

#include "inc/SDL2/SDL.h"
#include "inc/SDL2/SDL_ttf.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0) {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Winfetch", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (ren == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 24);

    if (font == nullptr) {
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Hello World", color);

    if (surface == nullptr) {
        std::cout << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);

    if (texture == nullptr) {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Rect dest = {5, 5, surface->w, surface->h};

    SDL_RenderCopy(ren, texture, NULL, &dest);
    SDL_RenderPresent(ren);

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

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}