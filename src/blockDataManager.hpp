#ifndef BLOCKDATAMANAGER_HPP
#define BLOCKDATAMANAGER_HPP

#include "unordered_map"
#include "block.hpp"

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

BlockDataManager blockDataManager;

#endif
