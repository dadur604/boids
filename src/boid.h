class Game;

static float BOID_HEIGHT = 20;
static float BOID_WIDTH = 10;

class Boid
{
public:
    static bool DRAW_DEBUG;

    static float FLOCK_RANGE_SQR;

    static float BOID_SPEED;
    static float ROTATE_SPEED;

    static float SEPARATION_LERP_AMOUNT;
    static float ALIGNMENT_LERP_AMOUNT;
    static float COHESION_LERP_AMOUNT;

    static float SEPARATION_FACTOR;

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
