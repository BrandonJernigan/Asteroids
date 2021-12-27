//
// Created by Brandon Jernigan on 12/25/21.
//

#ifndef ASTEROIDS_CPP_GAME_H
#define ASTEROIDS_CPP_GAME_H


#include <chrono>
#include <vector>
#include <SDL.h>
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Asteroid.h"
#include "Utilities.h"

const auto DELAY = std::chrono::seconds(2);

using sclock = std::chrono::system_clock;

class Game : public Scene {
public:
    Game(SDL_Renderer *renderer, std::function<void(SDL_Renderer*, int)> onDeath);
    ~Game();

    int score;
    sclock::time_point startTime;

    void draw() override;
    void update() override;

private:
    SDL_Texture *collisionTexture;
    std::function<void(SDL_Renderer*, int)> onDeath;

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
