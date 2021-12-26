//
// Created by Brandon Jernigan on 12/26/21.
//

#include "Asteroid.h"

Asteroid::Asteroid(SDL_Renderer *renderer)
{
    // set object state
    this->renderer = renderer;
    this->active = true;

    // set the rotation
    this->rAngle = 0.0f;
    this->rVel = 0.5f;

    // set the position
    this->xPos = (float)(1280 - 133) / 2.0;
    this->yPos = 100.0f;
    this->xVel = 0.0f;
    this->yVel = 0.0f;

    // set size and axis
    this->width = 133;
    this->height = 143;
    this->center = {this->width / 2.0f, this->height / 2.0f};

    // set the texture
    this->texture = Utilities::loadTexture(renderer, "sprites/asteroid-1.png");
}

void Asteroid::draw()
{
    if(!this->active)
    {
        return;
    }

    SDL_Rect srcRect = {0, 0, (int)this->width, (int)this->height};
    SDL_FRect destRect = {this->xPos, this->yPos, this->width, this->height};
    SDL_RenderCopyExF(
            this->renderer,
            this->texture,
            &srcRect,
            &destRect,
            this->rAngle,
            &this->center,
            SDL_FLIP_NONE);
}

void Asteroid::update()
{
    this->rAngle += rVel;
}

void Asteroid::onCollision()
{
    this->active = false;
}

Asteroid::~Asteroid()
{
    SDL_DestroyTexture(this->texture);
    this->renderer = nullptr;
}