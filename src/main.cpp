#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "../raygui/src/raygui.h"

#undef RAYGUI_IMPLEMENTATION

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

    bool showParameters = false;

    Game game(screenWidth, screenHeight);

    srand(time(0));

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        if (false && IsMouseButtonPressed(0))
        {
            double theta = ((float)rand() / (float)RAND_MAX) * 2 * PI;
            Vector2 direction = {(float)cos(theta), (float)sin(theta)};
            game.AddBoid(GetMousePosition(), direction);
        }

        game.Update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Boids", screenWidth - 250, screenHeight - 50, 20, DARKGRAY);
        DrawText("Narek Daduryan", screenWidth - 250, screenHeight - 25, 20, DARKGRAY);

        game.Draw();

        // Draw GUI

        if (showParameters)
        {
            GuiSetStyle(BUTTON, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_LEFT);
            GuiSetStyle(BUTTON, TEXT_PADDING, 0);
            if (GuiWindowBox({screenWidth - 320, 30, 300, 500}, "Parameters"))
            {
                showParameters = false;
            }

            GuiLabel({screenWidth - 300, 70, 150, 20}, "Boid Speed");
            Boid::BOID_SPEED = GuiSlider({screenWidth - 300, 90, 150, 20},
                                         "",
                                         TextFormat("%2.2f", (float)Boid::BOID_SPEED),
                                         Boid::BOID_SPEED, 1, 25);

            GuiLabel({screenWidth - 300, 120, 150, 20}, "Rotation Speed");
            Boid::ROTATE_SPEED = GuiSlider({screenWidth - 300, 140, 150, 20},
                                           "",
                                           TextFormat("%2.2f", (float)Boid::ROTATE_SPEED),
                                           Boid::ROTATE_SPEED, 0.1, 1);

            GuiLabel({screenWidth - 300, 170, 150, 20}, "Flock Range");
            Boid::FLOCK_RANGE_SQR = GuiSlider({screenWidth - 300, 190, 150, 20},
                                              "",
                                              TextFormat("%2.2f", (float)Boid::FLOCK_RANGE_SQR),
                                              Boid::FLOCK_RANGE_SQR, 5000, 80000);

            GuiLabel({screenWidth - 300, 220, 150, 20}, "Separation");
            Boid::SEPARATION_LERP_AMOUNT = GuiSlider({screenWidth - 300, 240, 150, 20},
                                                     "",
                                                     TextFormat("%2.2f", (float)Boid::SEPARATION_LERP_AMOUNT),
                                                     Boid::SEPARATION_LERP_AMOUNT, 0.1, 1);

            GuiLabel({screenWidth - 300, 270, 150, 20}, "Alignment");
            Boid::ALIGNMENT_LERP_AMOUNT = GuiSlider({screenWidth - 300, 290, 150, 20},
                                                    "",
                                                    TextFormat("%2.2f", (float)Boid::ALIGNMENT_LERP_AMOUNT),
                                                    Boid::ALIGNMENT_LERP_AMOUNT, 0.1, 1);

            GuiLabel({screenWidth - 300, 320, 150, 20}, "Cohesion");
            Boid::COHESION_LERP_AMOUNT = GuiSlider({screenWidth - 300, 340, 150, 20},
                                                   "",
                                                   TextFormat("%2.2f", (float)Boid::COHESION_LERP_AMOUNT),
                                                   Boid::COHESION_LERP_AMOUNT, 0.1, 1);

            GuiLabel({screenWidth - 300, 370, 150, 20}, "Separation Distance");
            Boid::MINIMUM_DISTANCE = GuiSlider({screenWidth - 300, 390, 150, 20},
                                               "",
                                               TextFormat("%2.2f", (float)Boid::MINIMUM_DISTANCE),
                                               Boid::MINIMUM_DISTANCE, 0, 10000);

            Boid::DRAW_DEBUG = GuiCheckBox({screenWidth - 300, 420, 20, 20}, "Draw Debugging Information", Boid::DRAW_DEBUG);

            GuiLabel({screenWidth - 300, 450, 150, 20}, "Number of Boids");
            game.SetNumBoids(GuiSlider({screenWidth - 300, 470, 150, 20},
                                       "", TextFormat("%2.2f", (float)game.boids.size()),
                                       (float)game.boids.size(), 0, MAX_BOIDS));

            if (GuiButton({screenWidth - 300, 500, 150, 20}, "Respawn Boids"))
            {
                int numBoids = game.boids.size();
                game.SetNumBoids(0);
                game.SetNumBoids(numBoids);
            }
        }
        else
        {
            GuiSetStyle(BUTTON, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_LEFT);
            GuiSetStyle(BUTTON, TEXT_PADDING, 5);
            if (GuiButton({screenWidth - 320, 30, 300, 25}, "Parameters"))
            {
                showParameters = true;
            }
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
