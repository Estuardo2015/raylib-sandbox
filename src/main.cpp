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

    // Prepare first face
    float vertices[12] = {
            -0.5, 0, 0,
            -0.5, 1, 0,
            0.5, 1, 0,
            0.5, 0, 0,
    };

    unsigned short indices[6] = {
            0, 1, 2,
            2, 3, 0
    };

    float texcoords[8] = {
            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
    };

    Mesh mesh { 0 };
    mesh.vertexCount = 4;
    mesh.vertices = vertices;

    mesh.indices = indices;
    mesh.triangleCount = 2;

    mesh.texcoords = texcoords;

    UploadMesh(&mesh, false);

    // Prepare second face
    float verticesTwo[12] = {
            -0.5, 0, 0,
            -0.5, 0, -1,
            -0.5, 1, -1,
            -0.5, 1, 0,
    };

    unsigned short indicesTwo[6] = {
            0, 1, 2,
            2, 3, 0
    };

    float texcoordsTwo[8] = {
            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
    };

    Mesh meshTwo { 0 };
    meshTwo.vertexCount = 4;
    meshTwo.vertices = verticesTwo;

    meshTwo.indices = indicesTwo;
    meshTwo.triangleCount = 2;

    meshTwo.texcoords = texcoordsTwo;

    UploadMesh(&meshTwo, false);

    //Model model = LoadModelFromMesh(mesh);

    // Load material
    Material material = LoadMaterialDefault();
    Texture texture = g.blockDataManager.BlockTextureDictionary[Grass][Left];

    SetMaterialTexture(&material, MATERIAL_MAP_DIFFUSE, texture);

    // Load material2
    Material materialTwo = LoadMaterialDefault();
    Texture textureTwo = g.blockDataManager.BlockTextureDictionary[Grass][Left];

    SetMaterialTexture(&materialTwo, MATERIAL_MAP_DIFFUSE, textureTwo);

    // Load model
    Model model = { 0 };

    model.transform = MatrixIdentity();

    model.meshCount = 1;
    model.meshes = (Mesh *)RL_CALLOC(model.meshCount, sizeof(Mesh));
    model.meshes[0] = mesh;

    model.materialCount = 1;
    model.materials = (Material *)RL_CALLOC(model.materialCount, sizeof(Material));
    model.materials[0] = material;

    model.meshMaterial = (int *)RL_CALLOC(model.meshCount, sizeof(int));
    model.meshMaterial[0] = 0;  // First material index
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
        //DrawMesh(mesh, material, MatrixIdentity());
        DrawModel(model, {0, 0, 0}, 1, BLANK);

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();

        g.Draw();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}