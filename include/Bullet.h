//
// Created by Brandon Jernigan on 12/25/21.
//

#ifndef ASTEROIDS_CPP_BULLET_H
#define ASTEROIDS_CPP_BULLET_H

#include "GameObject.h"
#include "Utilities.h"

const float B_SPEED = 5.0f;

class Bullet : public GameObject {
public:
    explicit Bullet(SDL_Renderer *renderer);
    ~Bullet();

    void draw() override;                           // GameObject draw method
    void update() override;                         // GameObject update method
    void onCollision() override;                    // GameObject collision handler
};


#endif //ASTEROIDS_CPP_BULLET_H
