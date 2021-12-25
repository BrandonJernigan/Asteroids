//
// Created by Brandon Jernigan on 12/24/21.
//

#include "Utilities.h"

SDL_Texture* Utilities::loadTexture(SDL_Renderer *renderer, const char *path)
{
    SDL_Surface *img = IMG_Load(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);
    return tex;
}