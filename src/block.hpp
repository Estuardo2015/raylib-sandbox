#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "unordered_map"
#include "raylib.h"

const float BLOCK_SIZE = 0.5;

enum BlockType {
    Air,
    Water,
    Dirt,
    Grass_Dirt,
    Stone
};

std::unordered_map<unsigned short int, Color> BLOCK_DICT{{Water,      BLUE},
                                                         {Dirt,       BROWN},
                                                         {Grass_Dirt, DARKGREEN},
                                                         {Stone,      GRAY}};

class Block {
public:
    BlockType type;

    Block();

    Block(BlockType);
};

Block::Block() {
    type = Air;
}

Block::Block(BlockType blockType) {
    type = blockType;
}

#endif
