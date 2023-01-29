#ifndef BLOCKDATAMANAGER_HPP
#define BLOCKDATAMANAGER_HPP

#include "../include/raylib.h"
#include "unordered_map"
#include "block.hpp"

enum BlockType {
    Air,
    Water,
    Dirt,
    Grass_Dirt,
    Stone
};

class BlockDataManager {

public:
    std::unordered_map<BlockType, Texture2D> BlockTextureDictionary;

    BlockDataManager();
};

BlockDataManager::BlockDataManager() {
    // NOTE: By default each cube is mapped to one part of texture atlas
    Texture2D texture = LoadTexture("../res/dirt.png");    // Load map texture
    BlockTextureDictionary[Dirt] = texture;
}

BlockDataManager *blockDataManager;

#endif
