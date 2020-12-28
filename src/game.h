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

private:
    int numBoids;
};