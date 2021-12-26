//
// Created by Brandon Jernigan on 12/25/21.
//

#include "Game.h"

Game::Game(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    this->score = 0;
    this->startTime = sclock::now();


    this->player = new Player(this->renderer);
    this->gameObjects.push_back(player);

    for (int i = 0; i < 5; i++)
    {
        auto *asteroid = new Asteroid(renderer);
        this->gameObjects.push_back(asteroid);
        this->asteroids.push_back(asteroid);
    }

    for (auto asteroid : this->asteroids)
    {
        if (checkAsteroidPosition(asteroid))
        {
            asteroid->xPos -= 100;
            asteroid->yPos -= 100;
        }
    }

    this->collisionTexture = Utilities::loadTexture(renderer, "sprites/collision.png");
}

void Game::draw()
{
    for (auto object : gameObjects)
    {
        if (object->active)
        {
            object->draw();
        }
    }
}

void Game::update()
{
    for (auto object : gameObjects)
    {
        if (object->active)
        {
            object->update();
        }
    }

    this->checkCollisions();
}

void Game::checkCollisions()
{
    for (auto bullet : player->bullets)
    {
        for (auto asteroid : this->asteroids)
        {
            if (bullet->active && asteroid->active)
            {
                if (checkPositions(bullet, asteroid))
                {
                    drawCollision(asteroid);
                    bullet->onCollision();
                    this->handleAsteroidCollision(asteroid);
                    this->score += 50;
                    return;
                }
            }
        }
    }

    for (auto asteroid : this->asteroids)
    {
        // delay for player collision on game start
        if (!(this->startTime + DELAY <= sclock::now()))
        {
            return;
        }

        if (asteroid->active)
        {
            if(checkPositions(this->player, asteroid))
            {
                drawCollision(asteroid);
                this->player->onCollision();
                this->handleAsteroidCollision(asteroid);
                return;
            }
        }
    }
}

void Game::drawCollision(GameObject *go)
{
    SDL_Rect srcRect = {0, 0, (int)go->width, (int)go->height};
    SDL_FRect destRect = {go->xPos, go->yPos, go->width, go->height};
    SDL_RenderCopyExF(
            this->renderer,
            this->collisionTexture,
            &srcRect,
            &destRect,
            go->rAngle,
            &go->center,
            SDL_FLIP_NONE);
}

Game::~Game()
{
    for(auto object : gameObjects)
    {
        object = nullptr;
    }
    SDL_DestroyTexture(this->collisionTexture);
    this->renderer = nullptr;
}

bool Game::checkPositions(GameObject *go1, GameObject *go2)
{
    bool xCondition1 = go1->xPos >= go2->xPos;
    bool xCondition2 = go1->xPos <= (go2->xPos + go2->width);
    if (xCondition1 && xCondition2)
    {
        bool yCondition1 = go1->yPos >= go2->yPos;
        bool yCondition2 = go1->yPos <= (go2->yPos + go2->height);
        if (yCondition1 && yCondition2)
        {
            return true;
        }
    }

    return false;
}

bool Game::checkAsteroidPosition(Asteroid *asteroid)
{
    bool xCondition1 = this->player->xPos >= (asteroid->xPos - 100);
    bool xCondition2 = this->player->xPos <= (asteroid->xPos + asteroid->width + 100);
    if (xCondition1 && xCondition2)
    {
        bool yCondition1 = this->player->yPos >= (asteroid->yPos - 100);
        bool yCondition2 = this->player->yPos <= (asteroid->xPos + asteroid->height + 100);
        if (yCondition1 && yCondition2)
        {
            return true;
        }
    }

    return false;
}

int Game::findGameObjectIndex(GameObject *go)
{
    auto item = std::find(this->gameObjects.begin(), this->gameObjects.end(), go);
    if (item != this->gameObjects.end())
    {
        return (int)(item - this->gameObjects.begin());
    }
    else
    {
        return -1;
    }
}

int Game::findAsteroidIndex(Asteroid *asteroid)
{
    auto item = std::find(
            this->asteroids.begin(),
            this->asteroids.end(),
            asteroid);

    if (item != this->asteroids.end())
    {
        return (int)(item - this->asteroids.begin());
    }
    else
    {
        return -1;
    }
}

void Game::handleAsteroidCollision(Asteroid *asteroid)
{
    if (asteroid->phase == 2)
    {
        asteroid->onCollision();
        int goIndex = this->findGameObjectIndex(asteroid);
        int aIndex = this->findAsteroidIndex(asteroid);

        this->gameObjects.erase(this->gameObjects.begin() + goIndex);
        this->asteroids.erase(this->asteroids.begin() + aIndex);

        auto newAsteroid = new Asteroid(this->renderer);

        if (checkAsteroidPosition(newAsteroid))
        {
            newAsteroid->xPos -= 100;
            newAsteroid->yPos -= 100;
        }

        this->gameObjects.push_back(newAsteroid);
        this->asteroids.push_back(newAsteroid);

        return;
    }

    asteroid->onCollision();
    auto *oppAsteroid = new Asteroid(
            renderer,
            asteroid->xPos,
            asteroid->yPos,
            -asteroid->xVel,
            -asteroid->yVel);

    this->asteroids.push_back(oppAsteroid);
    this->gameObjects.push_back(oppAsteroid);
}