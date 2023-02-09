#include "../include/raylib.h"
#include "game.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(0, 0, "Land of Promise");
    //ToggleFullscreen();

    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";

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

