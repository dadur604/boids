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

    bool showParameters = true;
    bool showColorPicker = false;

    Color backgroundColor = RAYWHITE;

    Game game(screenWidth, screenHeight);

    srand(time(0));

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        if (IsMouseButtonPressed(0))
        {
            Vector2 mousePos = GetMousePosition();

            if (!(mousePos.x > screenWidth - 320 &&
                  mousePos.x < screenWidth - 20 &&
                  mousePos.y > 30 &&
                  mousePos.y < 680))
            {
                game.AddUniqueBoid(mousePos);
            }
        }

        game.Update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(backgroundColor);

        DrawText("Boids", screenWidth - 250, screenHeight - 50, 20, DARKGRAY);
        DrawText("Narek Daduryan", screenWidth - 250, screenHeight - 25, 20, DARKGRAY);

        game.Draw();

        // Draw GUI

        if (showParameters)
        {
            GuiSetStyle(BUTTON, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_LEFT);
            GuiSetStyle(BUTTON, TEXT_PADDING, 0);
            if (GuiWindowBox({screenWidth - 320, 30, 300, 650}, "Parameters"))
            {
                showParameters = false;
            }

            GuiLabel({screenWidth - 300, 70, 150, 20}, "Boid Speed");
            game.BOID_SPEED = GuiSlider({screenWidth - 300, 90, 150, 20},
                                         "",
                                         TextFormat("%2.2f", (float)game.BOID_SPEED),
                                         game.BOID_SPEED, 1, 25);

            GuiLabel({screenWidth - 300, 120, 150, 20}, "Rotation Speed");
            game.ROTATE_SPEED = GuiSlider({screenWidth - 300, 140, 150, 20},
                                           "",
                                           TextFormat("%2.2f", (float)game.ROTATE_SPEED),
                                           game.ROTATE_SPEED, 0.1, 1);

            GuiLabel({screenWidth - 300, 170, 150, 20}, "Flock Range");
            game.FLOCK_RANGE_SQR = GuiSlider({screenWidth - 300, 190, 150, 20},
                                              "",
                                              TextFormat("%2.2f", (float)game.FLOCK_RANGE_SQR),
                                              game.FLOCK_RANGE_SQR, 500, 80000);

            GuiLine({screenWidth - 300, 230, 150, 0}, "Behavior");

            GuiLabel({screenWidth - 300, 240, 150, 20}, "Separation");
            game.SEPARATION_LERP_AMOUNT = GuiSlider({screenWidth - 300, 260, 150, 20},
                                                     "",
                                                     TextFormat("%2.2f", (float)game.SEPARATION_LERP_AMOUNT),
                                                     game.SEPARATION_LERP_AMOUNT, 0., 1);

            GuiLabel({screenWidth - 300, 290, 150, 20}, "Alignment");
            game.ALIGNMENT_LERP_AMOUNT = GuiSlider({screenWidth - 300, 310, 150, 20},
                                                    "",
                                                    TextFormat("%2.2f", (float)game.ALIGNMENT_LERP_AMOUNT),
                                                    game.ALIGNMENT_LERP_AMOUNT, 0., 1);

            GuiLabel({screenWidth - 300, 340, 150, 20}, "Cohesion");
            game.COHESION_LERP_AMOUNT = GuiSlider({screenWidth - 300, 360, 150, 20},
                                                   "",
                                                   TextFormat("%2.2f", (float)game.COHESION_LERP_AMOUNT),
                                                   game.COHESION_LERP_AMOUNT, 0., 1);

            GuiLabel({screenWidth - 300, 390, 150, 20}, "Separation Distance");
            game.MINIMUM_DISTANCE = GuiSlider({screenWidth - 300, 410, 150, 20},
                                               "",
                                               TextFormat("%2.2f", (float)game.MINIMUM_DISTANCE),
                                               game.MINIMUM_DISTANCE, 0, 10000);

            game.DRAW_DEBUG = GuiCheckBox({screenWidth - 300, 440, 20, 20}, "Draw Debugging Information", game.DRAW_DEBUG);

            if (showColorPicker)
                GuiLock();

            GuiLine({screenWidth - 300, 480, 150, 0}, "Boids");

            GuiLabel({screenWidth - 300, 490, 150, 20}, "Number of Boids");
            game.SetNumBoids(GuiSlider({screenWidth - 300, 510, 150, 20},
                                       "", TextFormat("%2.2f", (float)game.boids.size()),
                                       (float)game.boids.size(), 0, MAX_BOIDS));

            GuiSetStyle(BUTTON, TEXT_PADDING, 5);
            if (GuiButton({screenWidth - 300, 540, 150, 20}, "Respawn Boids"))
            {
                int numBoids = game.boids.size();
                game.SetNumBoids(0);
                game.SetNumBoids(numBoids);
            }

            GuiLine({screenWidth - 300, 580, 150, 0}, "Presets");

            if (GuiButton({screenWidth - 300, 600, 100, 20}, "Small Flocks"))
            {
                game.ROTATE_SPEED = 1;
                game.FLOCK_RANGE_SQR = 5000;
                game.SEPARATION_LERP_AMOUNT = 0.2;
                game.ALIGNMENT_LERP_AMOUNT = 0.2;
                game.COHESION_LERP_AMOUNT = 0.2;
                game.MINIMUM_DISTANCE = 2000;
            }
            if (GuiButton({screenWidth - 180, 600, 100, 20}, "Large Flocks"))
            {
                game.ROTATE_SPEED = 0.6;
                game.FLOCK_RANGE_SQR = 50000;
                game.SEPARATION_LERP_AMOUNT = 0.3;
                game.ALIGNMENT_LERP_AMOUNT = 0.2;
                game.COHESION_LERP_AMOUNT = 0.25;
                game.MINIMUM_DISTANCE = 10000;
            }
            if (GuiButton({screenWidth - 300, 630, 100, 20}, "Chaotic"))
            {
                game.ROTATE_SPEED = 0.1;
                game.FLOCK_RANGE_SQR = 80000;
                game.SEPARATION_LERP_AMOUNT = 0.1;
                game.ALIGNMENT_LERP_AMOUNT = 0.1;
                game.COHESION_LERP_AMOUNT = 1;
                game.MINIMUM_DISTANCE = 10000;
            }
            if (GuiButton({screenWidth - 180, 630, 100, 20}, "Circles!"))
            {
                game.ROTATE_SPEED = 0.48;
                game.FLOCK_RANGE_SQR = 5000;
                game.SEPARATION_LERP_AMOUNT = 1;
                game.ALIGNMENT_LERP_AMOUNT = 0;
                game.COHESION_LERP_AMOUNT = 1;
                game.MINIMUM_DISTANCE = 2000;
            }
            GuiUnlock();

            if (showColorPicker)
            {
                GuiSetStyle(BUTTON, TEXT_PADDING, 0);
                if (GuiWindowBox({screenWidth - 1000, screenHeight - 400, 900, 300}, "Colors"))
                {
                    showColorPicker = false;
                }

                GuiLabel({screenWidth - 980, screenHeight - 360, 220, 20}, "Main Boid Color");
                game.MAIN_BOID_COLOR = GuiColorPicker({screenWidth - 980, screenHeight - 340, 220, 220}, game.MAIN_BOID_COLOR);

                GuiLabel({screenWidth - 680, screenHeight - 360, 220, 20}, "Unique Boid Color");
                game.UNIQUE_BOID_COLOR = GuiColorPicker({screenWidth - 680, screenHeight - 340, 220, 220}, game.UNIQUE_BOID_COLOR);

                GuiLabel({screenWidth - 380, screenHeight - 360, 220, 20}, "Background Color");
                backgroundColor = GuiColorPicker({screenWidth - 380, screenHeight - 340, 220, 220}, backgroundColor);
            }
            else
            {
                if (GuiButton({screenWidth - 140, 540, 100, 20}, "Colors"))
                {
                    showColorPicker = true;
                }
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
