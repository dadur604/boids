class Game;

static float BOID_HEIGHT = 20;
static float BOID_WIDTH = 10;
static float BOID_SPEED = 5;

class Boid
{
public:
    Game *game;
    Vector2 pos;
    float velocity;
    Vector2 dir;

    Boid(Game *game);

    void Update();
    void Draw() const;
};
