//
// Created by Brandon Jernigan on 12/23/21.
//

#ifndef ASTEROIDS_CPP_PLAYER_H
#define ASTEROIDS_CPP_PLAYER_H


#include <SDL.h>
#include <SDL_image.h>
#include "Utilities.h"


const float R_SPEED = 0.1f;
const float T_SPEED = 0.02f;
const float RADIAN_EQ = 0.0174533;


class Player {
public:
    Player(SDL_Renderer *renderer);
    ~Player();
    void draw();
    void update();

private:
    SDL_Renderer *renderer;

    // Rotation
    float rAngle, rVel;

    // Size
    float width, height;
    SDL_FPoint center;

    // Position
    float xPos, yPos;
    float xVel, yVel;

    // State
    bool thrusting;
    SDL_Texture *idleTex;
    SDL_Texture *thrustingTex;
};


#endif //ASTEROIDS_CPP_PLAYER_H
