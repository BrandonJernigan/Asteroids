//
// Created by Brandon Jernigan on 12/26/21.
//

#include "Menu.h"

Menu::Menu(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    this->titleW = 1085;
    this->titleH = 297;
    this->texture = Utilities::loadTexture(renderer, "sprites/asteroids-logo.png");
}

void Menu::draw()
{
    SDL_Rect srcRect = {0, 0, this->titleW, this->titleH};
    SDL_Rect destRect = {(1280 - this->titleW) / 2, this->titleH, this->titleW, this->titleH};
    SDL_RenderCopy(
            this->renderer,
            this->texture,
            &srcRect,
            &destRect);
}

Menu::~Menu()
{
    SDL_DestroyTexture(texture);
    this->renderer = nullptr;
}