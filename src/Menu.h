//
// Created by Brandon Jernigan on 12/26/21.
//

#ifndef ASTEROIDS_CPP_MENU_H
#define ASTEROIDS_CPP_MENU_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Utilities.h"


class Menu {
public:
    Menu(SDL_Renderer *renderer);
    ~Menu();

    void draw();

private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    int titleW, titleH;
};


#endif //ASTEROIDS_CPP_MENU_H
