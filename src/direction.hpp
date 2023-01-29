#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include "raylib.h"

enum Direction {
    Forward,  // z+ direction
    Right,  // +x direction
    Backward,   // -z direction
    Left,   // -x direction
    Up,     // +y direction
    Down    // -y direction
};

Direction directions[] = {
    Backward,
    Down,
    Forward,
    Left,
    Right,
    Up
};

Vector3 GetDirectionVector(Direction direction) {
    switch (direction) {
        case Up:
            return {0, 1, 0};
        case Down:
            return {0, -1, 0};
        case Left:
            return {-1, 0, 0};
        case Right:
            return {1, 0, 0};
        case Forward:
            return {0, 0, 1};
        case Backward:
            return {0, 0, -1};
    }
}

#endif
