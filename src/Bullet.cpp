//
// Created by Brandon Jernigan on 12/25/21.
//

#include "Bullet.h"

Bullet::Bullet(SDL_Renderer *renderer)
{
    // set object state
    this->renderer = renderer;
    this->active = false;

    // set the rotation
    this->rAngle = 0.0f;

    // set the size and axis
    this->width = 24.0f;
    this->height = 28.0f;
    this->center = {this->width / 2.0f, this->height / 2.0f};

    // set the position
    this->xPos = 0.0f;
    this->yPos = 0.0f;
    this->xVel = 0.0f;
    this->yVel = 0.0f;

    // set the texture
    this->texture = Utilities::loadTexture(renderer, "sprites/bullet.png");
}

void Bullet::draw()
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

void Bullet::update()
{
    if(!this->active)
    {
        return;
    }

    this->xVel = sinf(rAngle * RADIAN_EQ) * B_SPEED;
    this->yVel = -cosf(rAngle * RADIAN_EQ) * B_SPEED;

    this->xPos += xVel;
    this->yPos += yVel;

    if (this->xPos <= 0 || this->xPos >= 1280)
    {
        this->active = false;
    }
    if (this->yPos <= 0 || this->yPos >= 720)
    {
        this->active = false;
    }
}

void Bullet::onCollision()
{
    this->active = false;
}

Bullet::~Bullet()
{
    SDL_DestroyTexture(this->texture);
    this->renderer = nullptr;
}