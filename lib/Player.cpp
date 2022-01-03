//
// Created by Brandon Jernigan on 12/23/21.
//

#include "Player.h"


Player::Player(SDL_Renderer *renderer)
{
    /* Set the object state */
    this->renderer = renderer;
    this->active = true;

    /* Set the initial rotation angle and velocity */
    this->rAngle = 0.0f;
    this->rVel = 0.0f;

    /* Set the size based on the image size */
    this->width = 26.0f;
    this->height = 32.0f;

    /* Calculate the center axis */
    this->center = {this->width / 2.0f, this->height / 2.0f};

    /* Set the position in the middle of the screen */
    int screenW, screenH = 0;
    SDL_GetRendererOutputSize(this->renderer, &screenW, &screenH);
    this->xPos = ((float)screenW - this->width) / 2.0f;
    this->yPos = ((float)screenH - this->height) / 2.0f;

    this->xVel = 0.0f;
    this->yVel = 0.0f;

    /* Texture is based on thrusting state */
    this->thrusting = false;
    this->idleTex =  Utilities::loadTexture(renderer, "sprites/player-idle.png");
    this->thrustingTex = Utilities::loadTexture(renderer, "sprites/player-thrusting.png");

    /* Initialize bullet pool; object pooling */
    for(auto & i : this->bullets)
    {
        auto *bullet = new Bullet(renderer);
        i = bullet;
    }
    this->lastShotTime = sclock::now() - COOLDOWN;
}

void Player::drawBullets()
{
    for(auto b : bullets)
    {
        if(b->active)
        {
            b->draw();
        }
    }
}

void Player::draw()
{
    /* Determine thrusting state & draw accordingly */
    float h = this->thrusting ? this->height + 13 : this->height;
    SDL_Texture *tex = this->thrusting ? this->thrustingTex : this->idleTex;

    SDL_Rect srcRect = {0, 0, (int)this->width, (int)h};
    SDL_FRect destRect = {this->xPos, this->yPos, this->width, h};
    SDL_RenderCopyExF(
            this->renderer,
            tex,
            &srcRect,
            &destRect,
            this->rAngle,
            &this->center,
            SDL_FLIP_NONE);

    this->drawBullets();
}

void Player::updateBullets()
{
    for(auto b : bullets)
    {
        b->update();
    }
}

void Player::shoot()
{
    if(lastShotTime + COOLDOWN <= sclock::now())
    {
        for(auto b : bullets)
        {
            if (!b->active)
            {
                b->xPos = this->xPos;
                b->yPos = this->yPos;
                b->rAngle = this->rAngle;
                b->active = true;
                lastShotTime = sclock::now();
                break;
            }
        }
    }
}

void Player::checkBounds()
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

void Player::handleKeyEvents()
{
    const u_int8_t *state = SDL_GetKeyboardState(nullptr);

    /* Rotation events */
    if (state[SDL_SCANCODE_A]) {
        this->rVel -= R_SPEED;
    }
    else if (state[SDL_SCANCODE_D])
    {
        this->rVel += R_SPEED;
    }

    /* Shooting event */
    if (state[SDL_SCANCODE_SPACE])
    {
        this->shoot();
    }

    /* Thrust event */
    if (state[SDL_SCANCODE_W]) {
        this->thrusting = true;
        this->xVel += sinf(rAngle * RADIAN_EQ) * T_SPEED;
        this->yVel -= cosf(rAngle * RADIAN_EQ) * T_SPEED;
    }
    else
    {
        this->thrusting = false;
    }
}

void Player::update()
{
    this->handleKeyEvents();

    this->rAngle += rVel;
    this->xPos += xVel;
    this->yPos += yVel;

    this->checkBounds();
    this->updateBullets();
}

void Player::onCollision()
{
    this->active = false;
}

Player::~Player()
{
    SDL_DestroyTexture(this->idleTex);
    SDL_DestroyTexture(this->thrustingTex);
    this->renderer = nullptr;
}