//
// Created by Brandon Jernigan on 12/26/21.
//

#ifndef ASTEROIDS_CPP_ASTEROID_H
#define ASTEROIDS_CPP_ASTEROID_H


#include <SDL.h>
#include "GameObject.h"
#include "Utilities.h"


class Asteroid : public GameObject {
public:
    Asteroid(SDL_Renderer *renderer);
    ~Asteroid();

    int phase;

    void draw() override;
    void update() override;
    void onCollision() override;

private:
    float rVel;

};


#endif //ASTEROIDS_CPP_ASTEROID_H
