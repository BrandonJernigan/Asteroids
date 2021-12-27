//
// Created by Brandon Jernigan on 12/26/21.
//

#ifndef ASTEROIDS_CPP_SCORE_H
#define ASTEROIDS_CPP_SCORE_H


#include <unistd.h>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Scene.h"


class Score : public Scene {
public:
    Score(SDL_Renderer *renderer, int score);
    ~Score();

    void draw() override;

private:
    SDL_Renderer *renderer;
    SDL_Texture *scoreTexture;
    SDL_Texture *actionTexture;

    int scoreW, scoreH;
    int actionW, actionH;
};


#endif //ASTEROIDS_CPP_SCORE_H
