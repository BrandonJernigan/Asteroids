//
// Created by Brandon Jernigan on 12/23/21.
//

#ifndef ASTEROIDS_CPP_PLAYER_H
#define ASTEROIDS_CPP_PLAYER_H


#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include "GameObject.h"
#include "Bullet.h"
#include "Utilities.h"


const float R_SPEED = 0.1f;
const float T_SPEED = 0.08f;
const auto COOLDOWN = std::chrono::milliseconds(500);


using sclock = std::chrono::system_clock;


class Player : public GameObject {
public:
    explicit Player(SDL_Renderer *renderer);
    ~Player();

    Bullet *bullets[30]{};

    void draw() override;
    void update() override;
    void onCollision() override;

private:
    float rVel;

    // state
    bool thrusting;
    SDL_Texture *idleTex;
    SDL_Texture *thrustingTex;
    sclock::time_point lastShotTime;

    void drawBullets();
    void updateBullets();
    void checkBounds();
    void handleKeyEvents();
    void shoot();
};


#endif //ASTEROIDS_CPP_PLAYER_H
