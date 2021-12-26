//
// Created by Brandon Jernigan on 12/26/21.
//

#include "Asteroid.h"

Asteroid::Asteroid(SDL_Renderer *renderer)
{
    // random engine
    std::random_device rd;
    std::default_random_engine eng(rd());

    // set object state
    this->renderer = renderer;
    this->active = true;
    this->phase = 1;

    // set the rotation
    this->rAngle = 0.0f;
    this->rVel = 0.5f;

    // position based on random value between 0 and screen width for x,
    // 0 and screen height for y
    std::uniform_real_distribution<float> xDistribution(0, (1280 - this->width));
    std::uniform_real_distribution<float> yDistribution(0, (720 - this->height));
    this->xPos = xDistribution(eng);
    this->yPos = yDistribution(eng);

    std::uniform_real_distribution<float> velDistribution(-3, 3);
    this->xVel = velDistribution(eng);
    this->yVel = velDistribution(eng);

    // set size and axis
    this->width = 133;
    this->height = 143;
    this->center = {this->width / 2.0f, this->height / 2.0f};

    // set the texture
    this->phaseOneTex = Utilities::loadTexture(renderer, "sprites/asteroid-1.png");
    this->phaseTwoTex = Utilities::loadTexture(renderer, "sprites/asteroid-2.png");
}

Asteroid::Asteroid(SDL_Renderer *renderer, float xPos, float yPos, float xVel, float yVel)
{
    // set object state
    this->renderer = renderer;
    this->active = true;
    this->phase = 2;

    // set the rotation
    this->rAngle = 0.0f;
    this->rVel = 0.5f;

    // set the position
    this->xPos = xPos;
    this->yPos = yPos;
    this->xVel = xVel;
    this->yVel = yVel;

    // set size and axis
    this->width = 97;
    this->height = 73;
    this->center = {this->width / 2.0f, this->height / 2.0f};

    // set the texture
    this->phaseTwoTex = Utilities::loadTexture(renderer, "sprites/asteroid-2.png");
}

void Asteroid::draw()
{
    if(!this->active)
    {
        return;
    }

    SDL_Texture *tex = this->phase == 1 ? this->phaseOneTex : this->phaseTwoTex;

    SDL_Rect srcRect = {0, 0, (int)this->width, (int)this->height};
    SDL_FRect destRect = {this->xPos, this->yPos, this->width, this->height};
    SDL_RenderCopyExF(
            this->renderer,
            tex,
            &srcRect,
            &destRect,
            this->rAngle,
            &this->center,
            SDL_FLIP_NONE);
}

void Asteroid::checkBounds()
{
    this->xPos = this->xPos <= 0 ? 1280 : this->xPos;
    this->xPos = this->xPos >= (1280 + this->height) ? 0 : this->xPos;

    this->yPos = this->yPos <= 0 ? 720 : this->yPos;
    this->yPos = this->yPos >= (720 + this->height) ? 0 : this->yPos;

    if (this->rAngle >= 360 || this->rAngle <= -360)
    {
        this->rAngle = 0.0f;
    }
}

void Asteroid::update()
{
    this->rAngle += rVel;

    this->xPos += xVel;
    this->yPos += yVel;

    this->checkBounds();
}

void Asteroid::onCollision()
{
    if (this->phase == 1)
    {
        this->phase = 2;
        this->width = 97;
        this->height = 73;
        this->center = {this->width / 2.0f, this->height / 2.0f};
        SDL_DestroyTexture(this->phaseOneTex);
    }
    else
    {
        this->active = false;
    }
}

Asteroid::~Asteroid()
{
    SDL_DestroyTexture(this->texture);
    SDL_DestroyTexture(this->phaseOneTex);
    SDL_DestroyTexture(this->phaseTwoTex);
    this->renderer = nullptr;
}