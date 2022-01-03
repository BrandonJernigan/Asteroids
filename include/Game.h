//
// Created by Brandon Jernigan on 12/25/21.
//

#ifndef ASTEROIDS_CPP_GAME_H
#define ASTEROIDS_CPP_GAME_H

#include <chrono>
#include <vector>
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Asteroid.h"
#include "Utilities.h"

const auto DELAY = std::chrono::seconds(2);                                     // Collision detection delay, to prevent player death on start

using sclock = std::chrono::system_clock;

class Game : public Scene {
public:
    Game(SDL_Renderer *renderer, std::function<void(SDL_Renderer*, int)> onDeath);
    ~Game();

    int score;                                                                      // Player score
    sclock::time_point startTime;                                                   // Time of game start

    void draw() override;                                                           // Scene draw method
    void update() override;                                                         // Scene update method

private:
    Player *player;                                                                 // The player
    std::vector<GameObject*> gameObjects;                                           // List of all current game objects
    SDL_Texture *collisionTexture;                                                  // Explosion texture for collisions
    std::vector<Asteroid*> asteroids;                                               // List of current asteroids in the game
    std::function<void(SDL_Renderer*, int)> onDeath;                                // Player death handler, injected

    void checkCollisions();                                                         // Check for player, asteroid, and bullet collisions
    void drawCollision(GameObject *go);                                             // Draw the explosion texture at point of collision
    bool checkPositions(GameObject *go1, GameObject *go2);                          // Determine if x and y positions are within one another
    bool checkAsteroidPosition(Asteroid *asteroid);                                 // Check asteroid position relative to player, used at game start to avoid collision on start
    int findGameObjectIndex(GameObject *go);                                        // Get the index of a game object from the GameObjects list
    int findAsteroidIndex(Asteroid *asteroid);                                      // Get the index of an asteroid object from the Asteroids list
    void handleAsteroidCollision(Asteroid *asteroid);                               // Set the phase of the asteroid on collision, or remove from game
};

#endif //ASTEROIDS_CPP_GAME_H
