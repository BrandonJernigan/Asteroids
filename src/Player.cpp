//
// Created by Brandon Jernigan on 12/23/21.
//

#include "Player.h"


Player::Player(SDL_Renderer *renderer)
{
    // set object state
    this->renderer = renderer;
    this->active = true;

    // set the rotation
    this->rAngle = 0.0f;
    this->rVel = 0.0f;

    // set the size and axis
    this->width = 26.0f;
    this->height = 32.0f;
    this->center = {this->width / 2.0f, this->height / 2.0f};

    // set position based on screen size
    int screenW, screenH = 0;
    SDL_GetRendererOutputSize(this->renderer, &screenW, &screenH);
    this->xPos = ((float)screenW - this->width) / 2.0f;
    this->yPos = ((float)screenH - this->height) / 2.0f;
    this->xVel = 0.0f;
    this->yVel = 0.0f;

    // set the textures; based on state
    this->thrusting = false;
    this->idleTex =  Utilities::loadTexture(renderer, "sprites/player-idle.png");
    this->thrustingTex = Utilities::loadTexture(renderer, "sprites/player-thrusting.png");

    // initialize bullet state and array; object pooling
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

    // rotation events
    if (state[SDL_SCANCODE_A]) {
        this->rVel -= R_SPEED;
    }
    else if (state[SDL_SCANCODE_D])
    {
        this->rVel += R_SPEED;
    }

    // shooting event
    if (state[SDL_SCANCODE_SPACE])
    {
        this->shoot();
    }

    // thrust event
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

Player::~Player()
{
    SDL_DestroyTexture(this->idleTex);
    SDL_DestroyTexture(this->thrustingTex);
    this->renderer = nullptr;
}