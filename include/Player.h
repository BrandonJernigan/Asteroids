//
// Created by Brandon Jernigan on 12/23/21.
//

#ifndef ASTEROIDS_CPP_PLAYER_H
#define ASTEROIDS_CPP_PLAYER_H

#include <chrono>
#include "GameObject.h"
#include "Bullet.h"
#include "Utilities.h"

using sclock = std::chrono::system_clock;

const float R_SPEED = 0.1f;                                // Rotation speed
const float T_SPEED = 0.08f;                               // Thrust speed
const auto COOLDOWN = std::chrono::milliseconds(500);      // Cooldown time between shots

class Player : public GameObject {
public:
    explicit Player(SDL_Renderer *renderer);
    ~Player();

    Bullet *bullets[30]{};                                 // Array to use for bullet pool

    void draw() override;                                  // GameObject draw method
    void update() override;                                // GameObject update method
    void onCollision() override;                           // GameObject collision handler

private:
    float rVel;                                            // Rotation velocity
    bool thrusting;                                        // Player object state; thrusting or idle
    SDL_Texture *idleTex;                                  // Texture for idle state
    SDL_Texture *thrustingTex;                             // Texture for thrusting state
    sclock::time_point lastShotTime;                       // Time of last bullet shot; compared against cooldown

    void drawBullets();
    void updateBullets();                                  // Call bullets update method, to update position
    void checkBounds();                                    // Determine player position relative to screen, wrap if off screen
    void handleKeyEvents();
    void shoot();
};

#endif //ASTEROIDS_CPP_PLAYER_H
