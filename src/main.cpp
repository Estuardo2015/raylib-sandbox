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

    Game g = Game();

    SetTargetFPS(60);

    MeshData meshData = MeshData();
    meshData.GetMeshData({0, 0, 0}, Grass);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        g.Update();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(g.player.camera);

        DrawGrid(10, 1.0f);

        //g.world.Render();
        DrawModel(meshData.model, {0, 0, 0}, 1, WHITE);

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();

        g.Draw();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

