class Game;

class Boid
{
public:
    static bool DRAW_DEBUG;

    static float BOID_HEIGHT;
    static float BOID_WIDTH;

    static float BOID_SPEED;
    static float ROTATE_SPEED;
    static float FLOCK_RANGE_SQR;

    static float SEPARATION_LERP_AMOUNT;
    static float ALIGNMENT_LERP_AMOUNT;
    static float COHESION_LERP_AMOUNT;

    static float MINIMUM_DISTANCE;

    static Color MAIN_BOID_COLOR;
    static Color UNIQUE_BOID_COLOR;

    Vector2 pos;
    Vector2 dir;

    Boid(Game *game);

    void MakeUnique();

    void Update();
    void Draw() const;

private:
    Game *game;
    Vector2 separationDirection;
    Vector2 averageAlignment;
    Vector2 localCenterOfMass;
    Vector2 cohesionDirection;
    bool unique = false;
};
