//
// Created by Brandon Jernigan on 12/26/21.
//

#ifndef ASTEROIDS_CPP_ASTEROID_H
#define ASTEROIDS_CPP_ASTEROID_H

#include <random>
#include "GameObject.h"
#include "Utilities.h"

class Asteroid : public GameObject {
public:
    Asteroid(SDL_Renderer *renderer);
    Asteroid(SDL_Renderer *renderer, float xPos, float yPos, float xVel, float yVel);
    ~Asteroid();

    int phase;                                                 // Tracker for asteroid size and collision amount before explosion

    void draw() override;                                      // GameObject draw method
    void update() override;                                    // GameObject update method
    void onCollision() override;                               // GameObject collision handler

private:
    float rVel;                                                // Rotation velocity
    SDL_Texture *phaseOneTex{};                                // Texture for big asteroid
    SDL_Texture *phaseTwoTex;                                  // Texture for small asteroid

    void setupAsteroid(SDL_Renderer *renderer);                // General settings for all constructors
    void checkBounds();                                        // If asteroid goes off the screen, loop it around
};


#endif //ASTEROIDS_CPP_ASTEROID_H
