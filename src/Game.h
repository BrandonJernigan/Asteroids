//
// Created by Brandon Jernigan on 12/25/21.
//

#ifndef ASTEROIDS_CPP_GAME_H
#define ASTEROIDS_CPP_GAME_H


#include <chrono>
#include <vector>
#include <SDL.h>
#include "GameObject.h"
#include "Utilities.h"
#include "Player.h"
#include "Asteroid.h"


const auto DELAY = std::chrono::seconds(2);


using sclock = std::chrono::system_clock;


class Game {
public:
    Game(SDL_Renderer *renderer);
    ~Game();

    int score;
    sclock::time_point startTime;

    void draw();
    void update();

private:
    SDL_Renderer *renderer;
    SDL_Texture *collisionTexture;

    Player *player;
    std::vector<GameObject*> gameObjects;
    std::vector<Asteroid*> asteroids;

    void checkCollisions();
    void drawCollision(GameObject *go);

    // helper methods
    bool checkPositions(GameObject *go1, GameObject *go2);
    bool checkAsteroidPosition(Asteroid *asteroid);
    int findGameObjectIndex(GameObject *go);
    int findAsteroidIndex(Asteroid *asteroid);
    void handleAsteroidCollision(Asteroid *asteroid);
};


#endif //ASTEROIDS_CPP_GAME_H
