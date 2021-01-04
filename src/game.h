#include <vector>
#include "raymath.h"

class Boid;

const static int MAX_BOIDS = 200;

class Game
{
public:
    std::vector<Boid *> boids;
    int width;
    int height;
    Game(int width, int height);
    void SetNumBoids(int numBoids);
    void AddBoid();
    Boid *AddBoid(Vector2 pos, Vector2 dir);
    void AddUniqueBoid(Vector2 pos);
    void RemoveBoid();
    void Update();
    void Draw() const;

public:
    bool DRAW_DEBUG = false;

    float BOID_HEIGHT = 20;
    float BOID_WIDTH = 10;

    float BOID_SPEED = 10;
    float ROTATE_SPEED = 1;
    float FLOCK_RANGE_SQR = 5000;

    float SEPARATION_LERP_AMOUNT = 0.2;
    float ALIGNMENT_LERP_AMOUNT = 0.2;
    float COHESION_LERP_AMOUNT = 0.2;

    float MINIMUM_DISTANCE = 2000;

    Color MAIN_BOID_COLOR = SKYBLUE;
    Color UNIQUE_BOID_COLOR = RED;

private:
    int numBoids;
};