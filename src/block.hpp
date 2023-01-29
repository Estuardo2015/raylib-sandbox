#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "unordered_map"
#include "raylib.h"
#include "blockDataManager.hpp"

const float BLOCK_SIZE = 0.5;

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
