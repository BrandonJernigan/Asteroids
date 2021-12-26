//
// Created by Brandon Jernigan on 12/25/21.
//

#ifndef ASTEROIDS_CPP_GAME_H
#define ASTEROIDS_CPP_GAME_H


#include <vector>
#include <SDL.h>
#include "GameObject.h"
#include "Utilities.h"
#include "Player.h"
#include "Asteroid.h"


class Game {
public:
    Game(SDL_Renderer *renderer);
    ~Game();

    void draw();
    void update();

private:
    SDL_Renderer *renderer;
    SDL_Texture *collisionTexture;

    Player *player;
    std::vector<GameObject*> gameObjects;
    std::vector<Asteroid*> asteroids;

    bool checkPositions(GameObject *go1, GameObject *go2);
    void checkCollisions();
    void drawCollision(GameObject *go);
};


#endif //ASTEROIDS_CPP_GAME_H
