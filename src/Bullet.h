//
// Created by Brandon Jernigan on 12/25/21.
//

#ifndef ASTEROIDS_CPP_BULLET_H
#define ASTEROIDS_CPP_BULLET_H


#include <SDL.h>
#include <SDL_image.h>
#include "Utilities.h"


const float B_SPEED = 5.0f;


class Bullet {
public:
    Bullet(SDL_Renderer *renderer);
    ~Bullet();

    // State
    bool active;

    // Rotation
    float rAngle;

    // Position
    float xPos, yPos;

    void draw();
    void update();

private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    // Size
    float width, height;
    SDL_FPoint center;

    float xVel, yVel;
};


#endif //ASTEROIDS_CPP_BULLET_H
