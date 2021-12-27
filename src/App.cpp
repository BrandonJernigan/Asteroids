#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Menu.h"
#include "Game.h"
#include "Score.h"


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

bool running = false;
Scene *activeScene;

// function to be injected in the game scene for
// loading score scene on player death
void onDeath(SDL_Renderer *renderer, int score)
{
    activeScene = nullptr;
    activeScene = new Score(renderer, score);
    running = false;
}

int main()
{
    // initialize SDL {image}
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    // create the window and renderer
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

    // load the scenes
    auto *menu = new Menu(renderer);
    activeScene = menu;

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

        if (!running)
        {
            const u_int8_t *state = SDL_GetKeyboardState(nullptr);
            if (state[SDL_SCANCODE_SPACE]) {
                activeScene = nullptr;
                activeScene = new Game(renderer, onDeath);
                running = true;
            }
        }

        // update and draw
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        activeScene->update();
        activeScene->draw();
        SDL_RenderPresent(renderer);
    }

    // clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
