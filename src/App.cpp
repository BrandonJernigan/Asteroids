#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Menu.h"
#include "Game.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


int main()
{
    // initialize SDL {image}
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow(
            "Asteroids C++",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_PRESENTVSYNC);

    // the game scene
    auto *game = new Game(renderer);

    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        // poll for quit event
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // update and draw
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        game->update();
        game->draw();
        SDL_RenderPresent(renderer);
    }

    // clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
