#include "raymath.h"
#include "boid.h"
#include "game.h"

#include <iostream>

bool Boid::DRAW_DEBUG = false;

float Boid::FLOCK_RANGE_SQR = 20000;

float Boid::BOID_SPEED = 10.;
float Boid::ROTATE_SPEED = 0.6;

float Boid::SEPARATION_LERP_AMOUNT = 0.2;
float Boid::ALIGNMENT_LERP_AMOUNT = 0.2;
float Boid::COHESION_LERP_AMOUNT = 0.2;

float Boid::SEPARATION_FACTOR = 200000;

Boid::Boid(Game *game)
    : game(game)
{
}

void Boid::Update()
{
    int numLocalBoids = 0;

    // Separation
    separationDirection = Vector2Zero();

    // Alignment
    averageAlignment = Vector2Zero();

    // Cohesion
    localCenterOfMass = Vector2Zero();

    for (Boid *boid : game->boids)
    {
        // Don't calculate ourselves
        if (boid == this)
            continue;

        // Only consider boids in our local range
        if (Vector2LengthSqr(Vector2Subtract(pos, boid->pos)) > FLOCK_RANGE_SQR)
            continue;

        numLocalBoids++;

        // Separation
        Vector2 difference = Vector2Subtract(pos, boid->pos);

        separationDirection = Vector2Add(separationDirection,
                                         Vector2Scale(Vector2Normalize(difference), SEPARATION_FACTOR / Vector2LengthSqr(difference)));

        // Alignment
        averageAlignment = Vector2Add(averageAlignment, boid->dir);

        // Cohesion
        localCenterOfMass = Vector2Add(localCenterOfMass, boid->pos);
    }

    if (numLocalBoids != 0)
    {
        // Separation
        if (Vector2LengthSqr(separationDirection) != 0)
        {
            dir = Vector2Normalize(Vector2Lerp(dir, Vector2Normalize(separationDirection), SEPARATION_LERP_AMOUNT * ROTATE_SPEED));
        }

        // Alignment
        if (Vector2LengthSqr(separationDirection) != 0)
        {
            averageAlignment = Vector2Scale(averageAlignment, 1. / numLocalBoids);
            dir = Vector2Normalize(Vector2Lerp(dir, Vector2Normalize(averageAlignment), ALIGNMENT_LERP_AMOUNT * ROTATE_SPEED));
        }

        // Cohesion
        if (Vector2LengthSqr(localCenterOfMass) != 0)
        {
            localCenterOfMass = Vector2Scale(localCenterOfMass, 1. / numLocalBoids);
            cohesionDirection = Vector2Subtract(localCenterOfMass, pos);

            dir = Vector2Normalize(Vector2Lerp(dir, Vector2Normalize(cohesionDirection), COHESION_LERP_AMOUNT * ROTATE_SPEED));
        }
    }

    // Move position according to velocity and direction
    pos = Vector2Add(pos,
                     Vector2Scale(dir, BOID_SPEED));

    std::cout << BOID_SPEED << std::endl;

    // Wrap around the screen
    if (pos.x > game->width)
        pos.x = 0;
    if (pos.x < 0)
        pos.x = game->width;
    if (pos.y > game->height)
        pos.y = 0;
    if (pos.y < 0)
        pos.y = game->height;
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

    if (DRAW_DEBUG)
    {
        // Draw vectors to aid debugging
        DrawLineEx(pos, Vector2Add(pos, Vector2Scale(dir, velocity * 40)), 2., GREEN);
        DrawLineEx(pos, Vector2Add(pos, Vector2Scale(norm_dir, velocity * 20)), 2., RED);
        DrawLineEx(pos, Vector2Add(pos, separationDirection), 2., DARKPURPLE);
        DrawLineEx(pos, Vector2Add(pos, Vector2Scale(averageAlignment, 40)), 2., PINK);
        DrawLineEx(pos, Vector2Add(pos, cohesionDirection), 2., ORANGE);

        DrawCircleLines(pos.x, pos.y, sqrtf(FLOCK_RANGE_SQR), YELLOW);
        DrawCircle(localCenterOfMass.x, localCenterOfMass.y, 10, ORANGE);
    }
}
