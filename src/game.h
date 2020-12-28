#include <vector>
#include "raymath.h"

class Boid;

const static int MAX_BOIDS = 150;

class Game
{
public:
    std::vector<Boid *> boids;
    int width;
    int height;
    Game(int width, int height);
    void SetNumBoids(int numBoids);
    void AddBoid();
    void AddBoid(Vector2 pos, Vector2 dir);
    void RemoveBoid();
    void Update();
    void Draw() const;

private:
    int numBoids;
};