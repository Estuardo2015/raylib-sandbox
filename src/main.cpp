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

    Mesh m = { 0 };

    float vertices[12] = {
       0, 0, 0,
       0, 1, 0,
       1, 1, 0,
       1, 0, 0
    };
    m.vertices = vertices;
    m.vertexCount = 12;

    unsigned short indices[12] = {
        0, 1, 2,
        2, 3, 0
    };
    m.indices = &indices[6];
    m.triangleCount = 6 / 3;

    float texcoords[12] = {
        0, 0,
        0, 1,
        1,1,
        1, 0
    };
    m.texcoords = texcoords;

    UploadMesh(&m, false);

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        g.Update();

        g.Draw();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(g.player.camera);

        DrawGrid(50, 1.0f);

        //g.world.Render();

        DrawMesh(m, blockDataManager->atlas, MatrixIdentity());

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}

