class Game;

class Boid
{
public:
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
