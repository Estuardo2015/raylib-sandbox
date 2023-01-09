#include "../include/raylib.h"

class Player {
    Vector3 position;
    Vector3 direction;
    Vector3 velocity;
    float speed;

public:
    Vector2 oldMousePosition;
    Camera3D camera{};

    Player();
    void Update();
};