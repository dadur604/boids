#include "game.h"
#include "boid.h"

Game::Game(int width, int height)
    : width(width), height(height), numBoids(0)
{
}

void Game::AddBoid(Vector2 pos, Vector2 dir, float velocity)
{
    if (numBoids >= MAX_BOIDS)
        return;

    Boid *b = new Boid(this);
    b->pos = pos;
    b->dir = dir;
    b->velocity = velocity;

    boids[numBoids] = b;

    numBoids++;
}

void Game::Update()
{
    for (int i = 0; i < numBoids; i++)
    {
        boids[i]->Update();
    }
}

void Game::Draw() const
{
    for (int i = 0; i < numBoids; i++)
    {
        boids[i]->Draw();
    }
}