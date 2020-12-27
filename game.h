#include "raymath.h"

class Boid;

const static int MAX_BOIDS = 10;

class Game
{
public:
    Boid *boids[MAX_BOIDS];
    int numBoids;
    int width;
    int height;
    Game(int width, int height);
    void AddBoid(Vector2 pos, Vector2 dir, float velocity);
    void Update();
    void Draw() const;
};