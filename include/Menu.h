//
// Created by Brandon Jernigan on 12/26/21.
//

#ifndef ASTEROIDS_CPP_MENU_H
#define ASTEROIDS_CPP_MENU_H

#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Scene.h"
#include "Utilities.h"

class Menu : public Scene {
public:
    Menu(SDL_Renderer *renderer);
    ~Menu();

    void draw() override;                       // Scene draw method

private:
    SDL_Renderer *renderer;
    SDL_Texture *titleTexture;                  // Asteroids logo texture
    SDL_Texture *actionTexture;                 // Texture for call to action (play)

    int titleW, titleH;                         // Width and height of title texture
    int actionW, actionH;                       // Width and height of action texture
};


#endif //ASTEROIDS_CPP_MENU_H
