//
// Created by Brandon Jernigan on 12/25/21.
//

#ifndef ASTEROIDS_CPP_GAMEOBJECT_H
#define ASTEROIDS_CPP_GAMEOBJECT_H


#include <SDL.h>
#include <SDL_image.h>


class GameObject {
public:
    // state
    bool active{};

    // rotation
    float rAngle{};

    // position
    float xPos{}, yPos{};

    // rendering
    virtual void draw(){};
    virtual void update(){};

protected:
    SDL_Renderer *renderer{};
    SDL_Texture *texture{};

    // Size
    float width{}, height{};
    SDL_FPoint center{};

    // movement
    float xVel{}, yVel{};
};


#endif //ASTEROIDS_CPP_GAMEOBJECT_H
