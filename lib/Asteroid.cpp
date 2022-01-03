//
// Created by Brandon Jernigan on 12/26/21.
//

#include "Asteroid.h"

Asteroid::Asteroid(SDL_Renderer *renderer)
{
    /* Random engine for generating random numbers */
    std::random_device rd;
    std::default_random_engine eng(rd());

    /* Asteroid phase */
    this->phase = 1;

    /* Set the starting position based on random value, within the screen */
    std::uniform_real_distribution<float> xDistribution(0, (1280 - this->width));
    std::uniform_real_distribution<float> yDistribution(0, (720 - this->height));
    this->xPos = xDistribution(eng);
    this->yPos = yDistribution(eng);

    /* Set the starting velocity based on random value, within -2 and 2 */
    std::uniform_real_distribution<float> velDistribution(-2, 2 );
    this->xVel = velDistribution(eng);
    this->yVel = velDistribution(eng);

    /* Set the size based on image size */
    this->width = 133;
    this->height = 143;

    /* Set the object textures for both phases */
    this->phaseOneTex = Utilities::loadTexture(renderer, "sprites/asteroid-1.png");
    this->phaseTwoTex = Utilities::loadTexture(renderer, "sprites/asteroid-2.png");

    /* General setup for Asteroid object */
    setupAsteroid(renderer);
}

Asteroid::Asteroid(SDL_Renderer *renderer, float xPos, float yPos, float xVel, float yVel)
{
    /* Asteroid phase */
    this->phase = 2;

    /* Set the position manually */
    this->xPos = xPos;
    this->yPos = yPos;
    this->xVel = xVel;
    this->yVel = yVel;

    /* Set the size based on image size */
    this->width = 97;
    this->height = 73;
    this->center = {this->width / 2.0f, this->height / 2.0f};

    /* Set the object textures for this phase */
    this->phaseTwoTex = Utilities::loadTexture(renderer, "sprites/asteroid-2.png");

    /* General setup for Asteroid object */
    setupAsteroid(renderer);
}

void Asteroid::setupAsteroid(SDL_Renderer *renderer)
{
    /* Set the object state */
    this->renderer = renderer;
    this->active = true;

    /* Set the initial rotation and rotation velocity */
    this->rAngle = 0.0f;
    this->rVel = 0.5f;

    /* Calculate the center axis */
    this->center = {this->width / 2.0f, this->height / 2.0f};
}

void Asteroid::draw()
{
    /* Don't draw the object if it isn't active */
    if(!this->active)
    {
        return;
    }

    SDL_Texture *tex = this->phase == 1 ? this->phaseOneTex : this->phaseTwoTex;

    /* Using FRect and CopyExF since we are using rotation values */
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