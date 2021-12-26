//
// Created by Brandon Jernigan on 12/24/21.
//

#ifndef ASTEROIDS_CPP_UTILITIES_H
#define ASTEROIDS_CPP_UTILITIES_H

#include <SDL.h>
#include <SDL_image.h>


const float RADIAN_EQ = 0.0174533;


class Utilities {
public:
    static SDL_Texture* loadTexture(SDL_Renderer *renderer, const char *path);
};


#endif //ASTEROIDS_CPP_UTILITIES_H
