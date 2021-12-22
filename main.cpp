#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window = SDL_CreateWindow(
            "Asteroids C++",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            1024,
            768,
            SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface *img = IMG_Load("sprites/title.png");
    if (img == NULL)
    {
        std::cout << "Error loading bmp image: " << SDL_GetError();
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, img);

    SDL_Event event;
    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_Rect srect = {0, 0, 548, 353};
        SDL_Rect dsrect = {100, 100, 548, 353};
        SDL_RenderCopy(renderer, tex, &srect, &dsrect);

        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(img);
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
