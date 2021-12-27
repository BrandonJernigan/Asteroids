//
// Created by Brandon Jernigan on 12/26/21.
//

#ifndef ASTEROIDS_CPP_MENU_H
#define ASTEROIDS_CPP_MENU_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Scene.h"
#include "Utilities.h"


class Menu : public Scene {
public:
    Menu(SDL_Renderer *renderer);
    ~Menu();

    void draw() override;

private:
    SDL_Renderer *renderer;
    SDL_Texture *titleTexture;
    SDL_Texture *actionTexture;

    int titleW, titleH;
    int actionW, actionH;
};


#endif //ASTEROIDS_CPP_MENU_H
