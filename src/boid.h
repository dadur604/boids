class Game;

static bool DRAW_DEBUG = false;

static float BOID_HEIGHT = 20;
static float BOID_WIDTH = 10;
static float BOID_SPEED = 10;

static float FLOCK_RANGE_SQR = 20000;

static float SEPARATION_FACTOR = 200000;

static float SEPARATION_LERP_AMOUNT = 0.2;
static float ALIGNMENT_LERP_AMOUNT = 0.2;
static float COHESION_LERP_AMOUNT = 0.2;

static float ROTATE_SPEED = 0.6;

class Boid
{
public:
    Game *game;
    Vector2 pos;
    float velocity;
    Vector2 dir;
    Vector2 separationDirection;
    Vector2 averageAlignment;
    Vector2 localCenterOfMass;
    Vector2 cohesionDirection;

    Boid(Game *game);

    void Update();
    void Draw() const;
};
