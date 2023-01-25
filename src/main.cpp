#include "../include/raylib.h"
#include "game.hpp"
#include "block.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(0, 0, "Land of Promise");
    ToggleFullscreen();

    Game g = Game();
    blockDataManager = BlockDataManager();

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        g.Update();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(g.player.camera);

        //DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground

        DrawGrid(10, 1.0f);

        g.world.Render();

        EndMode3D();

        DrawFPS(10, 10);

        std::string cameraAngle = "CameraX: " + std::to_string(g.player.camera.target.x) + " - CameraY: " +
                                  std::to_string(g.player.camera.target.y) + " - Camera Z: " +
                                  std::to_string(g.player.camera.target.z);
        DrawText(StrToCharArr(cameraAngle), 10, 30, 20, BLACK);

        std::string cameraPosition = "CameraPosX: " + std::to_string(g.player.camera.position.x) + " - CameraPosY: " +
                                     std::to_string(g.player.camera.position.z);
        DrawText(StrToCharArr(cameraPosition), 10, 60, 20, BLUE);

        EndDrawing();

        g.Draw();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}