#include "game.h"
#include "boid.h"

Game::Game(int width, int height)
    : width(width), height(height)
{
    SetNumBoids(40);
}

void Game::SetNumBoids(int numBoids)
{
    if (this->numBoids == numBoids)
        return;

    while (boids.size() < numBoids)
    {
        AddBoid();
    }

    while (boids.size() > numBoids)
    {
        RemoveBoid();
    }

    if (numBoids >= 100)
    {
        Boid::BOID_HEIGHT = 10;
        Boid::BOID_WIDTH = 5;
    }
    else
    {
        Boid::BOID_HEIGHT = 20;
        Boid::BOID_WIDTH = 10;
    }

    this->numBoids = numBoids;
}

void Game::AddBoid()
{
    float x = rand() % width;
    float y = rand() % height;

    double theta = ((float)rand() / (float)RAND_MAX) * 2 * PI;
    Vector2 direction = {(float)cos(theta), (float)sin(theta)};

    AddBoid({x, y}, direction);
}

void Game::AddBoid(Vector2 pos, Vector2 dir)
{
    if (boids.size() >= MAX_BOIDS)
        return;

    Boid *b = new Boid(this);
    b->pos = pos;
    b->dir = dir;

    boids.push_back(b);
}

void Game::RemoveBoid()
{
    if (boids.size() == 0)
        return;

    Boid *b = boids.back();
    delete b;

    boids.pop_back();
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