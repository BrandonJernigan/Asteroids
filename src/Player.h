//
// Created by Brandon Jernigan on 12/23/21.
//

#ifndef ASTEROIDS_CPP_PLAYER_H
#define ASTEROIDS_CPP_PLAYER_H

#include <SDL.h>
#include <SDL_image.h>


class Player {
public:
    Player(SDL_Renderer *renderer);
    ~Player();
    void draw();

private:
    int xPos, yPos;
    int width, height;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
};


#endif //ASTEROIDS_CPP_PLAYER_H
