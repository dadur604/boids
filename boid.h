class Game;

static float BOID_HEIGHT = 20;
static float BOID_WIDTH = 10;
static float BOID_SPEED = 5;

static float SEPARATION_FACTOR = 200000;
static float ROTATE_SPEED = 0.1;
static float SEPARATION_THRESHOLD = 1;

class Boid
{
public:
    Game *game;
    Vector2 pos;
    float velocity;
    Vector2 dir;
    Vector2 averageDirection;

    Boid(Game *game);

    void Update();
    void Draw() const;
};
