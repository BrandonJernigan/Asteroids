//
// Created by Brandon Jernigan on 12/26/21.
//

#include "Menu.h"

Menu::Menu(SDL_Renderer *renderer)
{
    this->renderer = renderer;

    /* Set the size based on the size of the image */
    this->titleW = 1085;
    this->titleH = 297;
    this->titleTexture = Utilities::loadTexture(renderer, "sprites/asteroids-logo.png");

    /* Get the font using absolute path */
    TTF_Font *font = TTF_OpenFont(
            "<YOUR ABSOLUTE PATH HERE>/EncodeSansCondensed-Regular.ttf",
            24);

    SDL_Surface *actionSurface = TTF_RenderUTF8_Solid(
            font,
            "Press SPACE to start",
            SDL_Color{255, 255, 255, 255});

    this->actionTexture = SDL_CreateTextureFromSurface(renderer, actionSurface);
    this->actionW = actionSurface->w;
    this->actionH = actionSurface->h;

    /* Clean up unneeded resources */
    TTF_CloseFont(font);
    SDL_FreeSurface(actionSurface);
}

void Menu::draw()
{
    SDL_Rect tSrcRect = {0, 0, this->titleW, this->titleH};
    SDL_Rect tDestRect = {(1280 - 400) / 2, 100, 400, 109};
    SDL_RenderCopy(
            this->renderer,
            this->titleTexture,
            &tSrcRect,
            &tDestRect);

    SDL_Rect aSrcRect = {0, 0, this->actionW, this->actionH};
    SDL_Rect aDestRect = {(1280 - this->actionW) / 2, 300, this->actionW, this->actionH};
    SDL_RenderCopy(
            this->renderer,
            this->actionTexture,
            &aSrcRect,
            &aDestRect);
}

Menu::~Menu()
{
    SDL_DestroyTexture(titleTexture);
    SDL_DestroyTexture(actionTexture);
    this->renderer = nullptr;
}