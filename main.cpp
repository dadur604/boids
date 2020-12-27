#include <raylib.h>
#include <raymath.h>

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <iostream>

#include "boid.h"
#include "game.h"

using namespace std;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Boids");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Game game(screenWidth, screenHeight);

    srand(time(0));

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        if (IsMouseButtonPressed(0))
        {
            double theta = ((float)rand() / (float)RAND_MAX) * 2 * PI;
            Vector2 direction = {(float)cos(theta), (float)sin(theta)};
            game.AddBoid(GetMousePosition(), direction, BOID_SPEED);
        }

        game.Update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        game.Draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
