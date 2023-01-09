#include "../include/raylib.h"
#include "game.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
//    const int screenWidth = 1200;
//    const int screenHeight = 850;
    InitWindow(0, 0, "Land of Promise");
    ToggleFullscreen();

    Game g = Game();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        g.Update();

        g.Draw();
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}