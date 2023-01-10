#include "../include/raylib.h"
#include "game.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(0, 0, "Land of Promise");
    ToggleFullscreen();

    Game g = Game();

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        g.Update();

        g.Draw();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}