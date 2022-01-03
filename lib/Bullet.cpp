//
// Created by Brandon Jernigan on 12/25/21.
//

#include "Bullet.h"

Bullet::Bullet(SDL_Renderer *renderer)
{
    /* Set the object state */
    this->renderer = renderer;
    this->active = false;

    /* Set the angle of rotation */
    this->rAngle = 0.0f;

    /* Set the size based on the image size */
    this->width = 24.0f;
    this->height = 28.0f;

    /* Calculate the center axis */
    this->center = {this->width / 2.0f, this->height / 2.0f};

    /* Manually set the initial position, before being loaded to play position */
    this->xPos = 0.0f;
    this->yPos = 0.0f;
    this->xVel = 0.0f;
    this->yVel = 0.0f;

    this->texture = Utilities::loadTexture(renderer, "sprites/bullet.png");
}

void Bullet::draw()
{
    if(!this->active)
    {
        return;
    }

    /* Using FRect and CopyExF since we are using rotation values */
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