#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define M_PI 3.141592

struct v2d {
    float x;
    float y;
};

typedef struct v2d v2d;

struct boid {
    Vector2 pos;
    Vector2 vec;
};

typedef struct boid boid;

float BOID_SIZE = 10;
float BOID_SPEED = 5;

const int MAX_BOIDS = 10;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Boids");
    

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    boid* b[MAX_BOIDS];
    int numBoids = 0;

    srand(time(0));

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        if (IsMouseButtonPressed(0) &&
            numBoids != MAX_BOIDS) {
            b[numBoids] = (boid*)malloc(sizeof(boid));
            b[numBoids]->pos = GetMousePosition();

            float theta = fmod(rand(), 2 * M_PI);

            b[numBoids]->vec.x = cos(theta);
            b[numBoids]->vec.y = sin(theta);
            numBoids++;
        }

        for (int i = 0; i < numBoids; i++) {
            b[i]->pos.x += BOID_SPEED * b[i]->vec.x;
            b[i]->pos.y += BOID_SPEED * b[i]->vec.y;

            if (b[i]->pos.x >= screenWidth)
                b[i]->pos.x = 0;
            if (b[i]->pos.x < 0)
                b[i]->pos.x = screenWidth - 1;
            if (b[i]->pos.y >= screenHeight)
                b[i]->pos.y = 0;
            if (b[i]->pos.y < 0)
                b[i]->pos.y = screenHeight - 1;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        for (int i = 0; i < numBoids; i++) {
            Vector2 backLeft = b[i]->pos;
            //backLeft.x -= b[i]->vec.x;
            //backLeft.y -= b[i]->vec.y;

            backLeft.x += BOID_SIZE;
            backLeft.y += BOID_SIZE;

            Vector2 backRight = b[i]->pos;
            //backRight.x += b[i]->vec.x;
            //backRight.y -= b[i]->vec.y;

            backRight.x -= BOID_SIZE;
            backRight.y -= BOID_SIZE;

            DrawTriangle(b[i]->pos, backLeft, backRight, SKYBLUE);
            //DrawPoly(b[i]->pos, 3, 10, 0, SKYBLUE);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
