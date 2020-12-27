#include "game.h"
#include "boid.h"

Game::Game(int width, int height)
    : width(width), height(height)
{
}

void Game::AddBoid(Vector2 pos, Vector2 dir, float velocity)
{
    if (boids.size() >= MAX_BOIDS)
        return;

    Boid *b = new Boid(this);
    b->pos = pos;
    b->dir = dir;
    b->velocity = velocity;

    boids.push_back(b);
}

void Game::Update()
{
    for (Boid *boid : boids)
    {
        boid->Update();
    }
}

void Game::Draw() const
{
    for (Boid *boid : boids)
    {
        boid->Draw();
    }
}