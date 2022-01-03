#include "Menu.h"
#include "Game.h"
#include "Score.h"


const int SCREEN_WIDTH = 1280;                                              // Screen dimensions
const int SCREEN_HEIGHT = 720;

bool running = false;                                                       // Boolean for game loop
Scene *activeScene;                                                         // Scene to call update and draw on

void onDeath(SDL_Renderer *renderer, int score)                             // Player death handler to be injected into game scene
{
    activeScene = nullptr;                                                  // Remove pointer reference
    activeScene = new Score(renderer, score);                               // Set new active scene
    running = false;                                                        // Stop game loop
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);                                    // Initialize SDL
    IMG_Init(IMG_INIT_PNG);                                           // Initialize SDL_Image
    TTF_Init();                                                             // Initialize SDL_TTF

    SDL_Window *window = SDL_CreateWindow(                                  // Create SDL window
            "Asteroids C++",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_OPENGL);                                       // Use OpenGL window flag

    SDL_Renderer *renderer = SDL_CreateRenderer(                            // Create SDL renderer
            window,
            -1,
            SDL_RENDERER_PRESENTVSYNC);                               // Synchronize with refresh rate

    auto *menu = new Menu(renderer);                                        // Load menu scene
    activeScene = menu;                                                     // Set menu scene as active scene to start

    SDL_Event event;                                                        // Keyboard event container
    bool quit = false;                                                      // Boolean for program loop
    while (!quit)
    {
        while (SDL_PollEvent(&event))                                 // Poll for quit event
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        if (!running)
        {
            const u_int8_t *state = SDL_GetKeyboardState(nullptr); // Get any key presses
            if (state[SDL_SCANCODE_SPACE]) {                                // Allow for SPACE bar press to trigger game start
                activeScene = nullptr;                                      // Remove reference to current active scene
                activeScene = new Game(renderer, onDeath);                  // Set the new active scene to game scene
                running = true;                                             // Start the game loop
            }
        }

        SDL_RenderClear(renderer);                                          // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);         // Repaint the renderer with the color black
        activeScene->update();                                              // Update the active scene
        activeScene->draw();                                                // Draw the active scene and it's objects
        SDL_RenderPresent(renderer);                                        // Present the renderer's state
    }

    SDL_DestroyRenderer(renderer);                                          // Clean up the renderer
    SDL_DestroyWindow(window);                                              // Clean up the window

    TTF_Quit();                                                             // Clean up SDL_TTF
    IMG_Quit();                                                             // Clean up SDL_Image
    SDL_Quit();                                                             // Clean up SDL

    return 0;
}
