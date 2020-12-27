#include "raymath.h"
#include "boid.h"
#include "game.h"

#include <iostream>

Boid::Boid(Game *game)
    : game(game)
{
}

void Boid::Update()
{
    // Separation
    averageDirection = Vector2Zero();

    // Calculate average direction difference
    for (Boid *boid : game->boids)
    {
        // Don't calculate ourselves
        if (boid == this)
            continue;

        Vector2 difference = Vector2Subtract(pos, boid->pos);

        averageDirection = Vector2Add(averageDirection,
                                      Vector2Scale(Vector2Normalize(difference), SEPARATION_FACTOR / Vector2LengthSqr(difference)));
    }

    if (Vector2LengthSqr(averageDirection) > SEPARATION_THRESHOLD)
    {
        dir = Vector2Normalize(Vector2Lerp(dir, Vector2Normalize(averageDirection), ROTATE_SPEED));
    }

    // Move position according to velocity and direction
    pos = Vector2Add(pos,
                     Vector2Scale(dir, velocity));
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

    // Draw vectors to aid debugging
    DrawLineEx(pos, Vector2Add(pos, Vector2Scale(dir, velocity * 40)), 2., GREEN);
    DrawLineEx(pos, Vector2Add(pos, Vector2Scale(norm_dir, velocity * 20)), 2., RED);
    DrawLineEx(pos, Vector2Add(pos, averageDirection), 2., DARKPURPLE);
}
