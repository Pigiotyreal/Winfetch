#define SDL_MAIN_HANDLED

#include "inc/SDL2/SDL.h"
#include "inc/SDL2/SDL_ttf.h"
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <intrin.h>
#include <iomanip>
#include <vector>
#include <chrono>
#include <d3d9.h>
#include <tlhelp32.h>
#include <iphlpapi.h>
#include <dxgi.h>
#include <string>

SYSTEM_INFO sysinfo;

std::string cpuArch() {
    GetSystemInfo(&sysinfo);

    switch(sysinfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            std::cout << "x64\n";
            return "x64";
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            std::cout << "x86\n";
            return "x86";
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            return "ARM";
            break;
        default:
            return "Unknown";
            break;
    }
}

std::string cpuName() {
    int CPUInfo[4] = {-1};

    char cpuName[49];
    __cpuid(CPUInfo, 0x80000002);
    memcpy(cpuName, CPUInfo, sizeof(CPUInfo));
    __cpuid(CPUInfo, 0x80000003);
    memcpy(cpuName + 16, CPUInfo, sizeof(CPUInfo));
    __cpuid(CPUInfo, 0x80000004);
    memcpy(cpuName + 32, CPUInfo, sizeof(CPUInfo));
    cpuName[48] = '\0';

    return cpuName;
}

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

    SDL_Surface *cpuarchText = TTF_RenderText_Solid(font, "CPU Architecture: ", color);
    SDL_Surface *cpuarch = TTF_RenderText_Solid(font, cpuArch().c_str(), color);
    SDL_Surface *cpunameText = TTF_RenderText_Solid(font, "CPU Name: ", color);
    SDL_Surface *cpuname = TTF_RenderText_Solid(font, cpuName().c_str(), color);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, cpuarch);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(ren, cpuarchText);
    SDL_Texture *texture3 = SDL_CreateTextureFromSurface(ren, cpuname);
    SDL_Texture *texture4 = SDL_CreateTextureFromSurface(ren, cpunameText);

    SDL_Rect dest = {200, 5, cpuarch->w, cpuarch->h};
    SDL_Rect dest2 = {5, 5, cpuarchText->w, cpuarchText->h};
    SDL_Rect dest3 = {140, 50, cpuname->w, cpuname->h};
    SDL_Rect dest4 = {5, 50, cpunameText->w, cpunameText->h};

    SDL_RenderCopy(ren, texture, NULL, &dest);
    SDL_RenderCopy(ren, texture2, NULL, &dest2);
    SDL_RenderCopy(ren, texture3, NULL, &dest3);
    SDL_RenderCopy(ren, texture4, NULL, &dest4);
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

    SDL_FreeSurface(cpuarch);
    SDL_FreeSurface(cpuarchText);
    SDL_FreeSurface(cpuname);
    SDL_FreeSurface(cpunameText);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}