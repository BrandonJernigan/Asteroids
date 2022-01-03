//
// Created by Brandon Jernigan on 12/26/21.
//

#include "Score.h"

Score::Score(SDL_Renderer *renderer, int score)
{
    this->renderer = renderer;

    /* Get the font using absolute path */
    TTF_Font *font = TTF_OpenFont(
            "<YOUR ABSOLUTE PATH HERE>/EncodeSansCondensed-Regular.ttf",
            24);

    std::string scoreString = std::string("You scored: ") + std::to_string(score);
    SDL_Surface *scoreSurface = TTF_RenderUTF8_Solid(
            font,
            scoreString.data(),
            SDL_Color{255, 255, 255, 255});

    this->scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    this->scoreW = scoreSurface->w;
    this->scoreH = scoreSurface->h;

    SDL_Surface *actionSurface = TTF_RenderUTF8_Solid(
            font,
            "Press SPACE to play again",
            SDL_Color{255, 255, 255, 255});

    this->actionTexture = SDL_CreateTextureFromSurface(renderer, actionSurface);
    this->actionW = actionSurface->w;
    this->actionH = actionSurface->h;

    /* Clean up unneeded resources */
    TTF_CloseFont(font);
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(actionSurface);
}

void Score::draw()
{
    SDL_Rect sSrcRect = {0, 0, this->scoreW, this->scoreH};
    SDL_Rect sDestRect = {(1280 - this->scoreW) / 2, 100, this->scoreW, this->scoreH};
    SDL_RenderCopy(
            this->renderer,
            this->scoreTexture,
            &sSrcRect,
            &sDestRect);

    SDL_Rect aSrcRect = {0, 0, this->actionW, this->actionH};
    SDL_Rect aDestRect = {(1280 - this->actionW) / 2, 300, this->actionW, this->actionH};
    SDL_RenderCopy(
            this->renderer,
            this->actionTexture,
            &aSrcRect,
            &aDestRect);
}

Score::~Score()
{
    SDL_DestroyTexture(this->scoreTexture);
    SDL_DestroyTexture(this->actionTexture);
    this->renderer = nullptr;
}