#include "../include/raylib.h"
#include "game.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(0, 0, "Land of Promise");
    ToggleFullscreen();

    Game g = Game();

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Test Drawing Mesh
    Mesh mesh = {0};
    float vertices[] = {0.5, 0, 0,
                        0, 0.5, 0,
                        -0.5, 0, 0};
    mesh.vertices = vertices;
    mesh.vertexCount = 9;

    unsigned short indices[] = {0, 1, 2};
    mesh.indices = indices;
    mesh.triangleCount = 1;

    // Load test material
    Material material = LoadMaterialDefault();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        g.Update();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(g.player.camera);

        DrawGrid(10, 1.0f);

        DrawMesh(mesh, material, MatrixIdentity());

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();

        g.Draw();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}