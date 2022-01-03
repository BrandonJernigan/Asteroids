//
// Created by Brandon Jernigan on 12/25/21.
//

#ifndef ASTEROIDS_CPP_GAMEOBJECT_H
#define ASTEROIDS_CPP_GAMEOBJECT_H

#include <SDL.h>
#include <SDL_image.h>

class GameObject {
public:
    bool active{};                              // The state of the game object, whether to be rendered or not
    float rAngle{};                             // The angle of rotation
    float xPos{}, yPos{};                       // The position
    float xVel{}, yVel{};                       // The velocity
    float width{}, height{};                    // The size
    SDL_FPoint center{};                        // The calculated center axis

    virtual void draw(){};
    virtual void update(){};
    virtual void onCollision(){};

protected:
    SDL_Renderer *renderer{};
    SDL_Texture *texture{};
};

#endif //ASTEROIDS_CPP_GAMEOBJECT_H
