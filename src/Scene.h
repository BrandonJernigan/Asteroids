//
// Created by Brandon Jernigan on 12/26/21.
//

#ifndef ASTEROIDS_CPP_SCENE_H
#define ASTEROIDS_CPP_SCENE_H


#include <SDL.h>


class Scene {
public:
    virtual void update(){};
    virtual void draw(){};

protected:
    SDL_Renderer *renderer{};
};


#endif //ASTEROIDS_CPP_SCENE_H
