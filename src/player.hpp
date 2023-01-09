#include "../include/raylib.h"

class Player {
    Vector3 position;
    Vector3 direction;

public:
    Vector2 oldMousePosition;
    Camera3D camera{};

    Player();
    void Update();
};