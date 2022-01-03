//
// Created by Brandon Jernigan on 12/26/21.
//

#ifndef ASTEROIDS_CPP_SCORE_H
#define ASTEROIDS_CPP_SCORE_H

#include <unistd.h>
#include <string>
#include <SDL_ttf.h>
#include "Scene.h"

class Score : public Scene {
public:
    Score(SDL_Renderer *renderer, int score);
    ~Score();

    void draw() override;

private:
    SDL_Renderer *renderer;
    SDL_Texture *scoreTexture;                          // Texture for the score text
    SDL_Texture *actionTexture;                         // Texture for the call to action (play)

    int scoreW, scoreH;                                 // Score texture width and height
    int actionW, actionH;                               // Action texture width and height
};

#endif //ASTEROIDS_CPP_SCORE_H
