//
// Created by Brandon Jernigan on 12/23/21.
//

#include "Player.h"

Player::Player(SDL_Renderer *renderer)
{
    this->renderer = renderer;

    SDL_Surface *img = IMG_Load("sprites/player.png");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, img);
    this->texture = tex;
    this->width = img->w;
    this->height = img->h;
    SDL_FreeSurface(img);

    int screenW, screenH = 0;
    SDL_GetRendererOutputSize(this->renderer, &screenW, &screenH);
    this->xPos = (screenW - this->width) / 2;
    this->yPos = (screenH - this->height) / 2;
}

void Player::draw()
{
    SDL_Rect srcRect = {0, 0, this->width, this->height};
    SDL_Rect destRect = {this->xPos, this->yPos, this->width, this->height};
    SDL_RenderCopy(
            this->renderer,
            this->texture,
            &srcRect,
            &destRect);
}

Player::~Player()
{
    SDL_DestroyTexture(this->texture);
    this->renderer = nullptr;
}