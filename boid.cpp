#include "raymath.h"
#include "boid.h"

Boid::Boid(Game *game)
    : game(game)
{
}

void Boid::Update()
{
    this->pos = Vector2Add(this->pos,
                           Vector2Scale(this->dir, this->velocity));
}

void Boid::Draw() const
{
    Vector2 norm_dir = {dir.y * -1.0, dir.x};

    Vector2 bottom = Vector2Subtract(pos,
                                     Vector2Scale(dir, BOID_HEIGHT));

    DrawTriangle(
        Vector2Add(pos, (Vector2Scale(dir, BOID_HEIGHT))),
        Vector2Subtract(bottom, Vector2Scale(norm_dir, BOID_WIDTH)),
        Vector2Add(bottom, Vector2Scale(norm_dir, BOID_WIDTH)),
        SKYBLUE);
}
