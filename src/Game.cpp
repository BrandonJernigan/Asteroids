//
// Created by Brandon Jernigan on 12/25/21.
//

#include "Game.h"

Game::Game(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    this->player = new Player(this->renderer);
    this->gameObjects.push_back(player);

    auto *asteroid = new Asteroid(renderer);
    this->gameObjects.push_back(asteroid);
    this->asteroids.push_back(asteroid);

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
                    asteroid->onCollision();
                    return;
                }
            }
        }
    }

    for (auto asteroid : this->asteroids)
    {
        if (asteroid->active)
        {
            if(checkPositions(this->player, asteroid))
            {
                drawCollision(asteroid);
                this->player->onCollision();
                asteroid->onCollision();
                return;
            }
        }
    }
}

Game::~Game()
{
    for(auto object : gameObjects)
    {
        object = nullptr;
    }
    this->renderer = nullptr;
}