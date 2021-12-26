//
// Created by Brandon Jernigan on 12/23/21.
//

#include "Player.h"


Player::Player(SDL_Renderer *renderer)
{
    this->renderer = renderer;

    // Set the rotation
    this->rAngle = 0.0f;
    this->rVel = 0.0f;

    // Set the size and axis
    this->width = 26.0f;
    this->height = 32.0f;
    this->center = {this->width / 2.0f, this->height / 2.0f};

    // Set position based on screen size
    int screenW, screenH = 0;
    SDL_GetRendererOutputSize(this->renderer, &screenW, &screenH);
    this->xPos = ((float)screenW - this->width) / 2.0f;
    this->yPos = ((float)screenH - this->height) / 2.0f;
    this->xVel, this->yVel = 0.0f;

    this->thrusting = false;
    this->idleTex =  Utilities::loadTexture(renderer, "sprites/player-idle.png");
    this->thrustingTex = Utilities::loadTexture(renderer, "sprites/player-thrusting.png");

    for(auto & i : this->bullets)
    {
        auto *bullet = new Bullet(renderer);
        i = bullet;
    }

    this->lastShotTime = sclock::now() - COOLDOWN;
}

void Player::draw()
{
    float h;
    SDL_Texture *tex;
    if(thrusting)
    {
        h = this->height + 13;
        tex = this->thrustingTex;
    }
    else
    {
        h = this->height;
        tex = this->idleTex;
    }

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

    for(auto b : bullets)
    {
        if(b->active)
        {
            b->draw();
        }
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

void Player::update() {
    const u_int8_t *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_A]) {
        this->rVel -= R_SPEED;
    }
    else if (state[SDL_SCANCODE_D])
    {
        this->rVel += R_SPEED;
    }
    this->rAngle += rVel;
    if (this->rAngle >= 360 || this->rAngle <= -360)
    {
        this->rAngle = 0.0f;
    }

    if (state[SDL_SCANCODE_SPACE])
    {
        this->shoot();
    }

    if (state[SDL_SCANCODE_W]) {
        this->thrusting = true;
        this->xVel += sinf(rAngle * RADIAN_EQ) * T_SPEED;
        this->yVel -= cosf(rAngle * RADIAN_EQ) * T_SPEED;
     }
    else
    {
        this->thrusting = false;
    }
    this->xPos += xVel;
    this->yPos += yVel;
    if(this->xPos <= 0)
    {
        this->xPos = 1280;
    }
    if(this->xPos >= (1280 + this->height))
    {
        this->xPos = 0;
    }
    if(this->yPos <= 0)
    {
        this->yPos = 720;
    }
    if(this->yPos >= (720 + this->height))
    {
        this->yPos = 0;
    }

    for(auto b : bullets)
    {
        b->update();
    }
}

Player::~Player()
{
    SDL_DestroyTexture(this->idleTex);
    SDL_DestroyTexture(this->thrustingTex);
    this->renderer = nullptr;
}