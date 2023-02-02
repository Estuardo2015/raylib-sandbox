#ifndef BLOCKDATAMANAGER_HPP
#define BLOCKDATAMANAGER_HPP

#include "../include/raylib.h"
#include "unordered_map"
#include "block.hpp"
#include "direction.hpp"
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

const int BLOCK_TEXTURE_SIZE = 16;

enum BlockType {
    Air,
    Water,
    Dirt,
    Grass,
    Stone
};

std::unordered_map<std::string, BlockType> BlockDict {
        {"grass", Grass}
};

class BlockDataManager {

public:
    std::unordered_map<BlockType, std::unordered_map<Direction, Texture2D>> BlockTextureDictionary;

    BlockDataManager();

    json LoadBlockJSON(const char *);
};

BlockDataManager::BlockDataManager() {
    // Load the atlas atlas
    Image atlas = LoadImage("../res/atlas.png");

    // Load block data
    json blockData = LoadBlockJSON("../data/block_data.json");

    // Iterate through block types
    for (auto& blockToDirections : blockData.items()) {
        std::string blockTypeStr = blockToDirections.key();
        BlockType blockType = BlockDict[blockTypeStr];

        // Iterate through directions
        for (auto& blockDirection : blockToDirections.value().items()) {
            // Get the coordinates of the atlas in the atlas
            std::string dir = blockDirection.key();
            float x = blockDirection.value()["x"];
            float y = blockDirection.value()["y"];

            // Get subimage using coordinates
            Rectangle rect = {x, y, BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE};
            Image subImage = ImageFromImage(atlas, rect);
            Texture tex = LoadTextureFromImage(subImage);

            // Set atlas to the block direction
            if (dir == "top") {
                BlockTextureDictionary[blockType][Up] = tex;
            } else if (dir == "bottom") {
                BlockTextureDictionary[blockType][Down] = tex;
            } else if (dir == "side") {
                BlockTextureDictionary[blockType][Forward] = tex;
                BlockTextureDictionary[blockType][Backward] = tex;
                BlockTextureDictionary[blockType][Left] = tex;
                BlockTextureDictionary[blockType][Right] = tex;
            }

            //UnloadTexture(tex);
        }
    }
}

json BlockDataManager::LoadBlockJSON(const char * blockJSONPath) {
    std::ifstream file(blockJSONPath);
    return json::parse(file);
}

#endif
