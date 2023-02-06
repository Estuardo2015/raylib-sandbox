#ifndef BLOCKDATAMANAGER_HPP
#define BLOCKDATAMANAGER_HPP

#include "../include/raylib.h"
#include "unordered_map"
#include "block.hpp"
#include "direction.hpp"
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;

enum BlockType {
    Air,
    Water,
    Dirt,
    Grass,
    Stone
};

std::unordered_map<std::string, BlockType> BlockDict{
        {"grass", Grass},
        {"water", Water},
        {"dirt",  Dirt},
        {"stone", Stone}
};

class BlockDataManager {

public:
    Material atlas;

    std::unordered_map<BlockType, std::unordered_map<Direction, std::vector<float>>> BlockFaceToUVs;

    BlockDataManager();

    json LoadBlockJSON(const char *);
};

BlockDataManager::BlockDataManager() {
    // Load the image atlas
    Texture atlasTexture = LoadTexture("../res/atlas.png");
    atlas = LoadMaterialDefault();
    SetMaterialTexture(&atlas, MATERIAL_MAP_DIFFUSE, atlasTexture);

    std::cout << "atlas loaded" << std::endl;

    // Load block data
    json blockData = LoadBlockJSON("../data/block_data.json");

    // Iterate through block types
    for (auto &blockToDirections: blockData.items()) {
        std::string blockTypeStr = blockToDirections.key();
        BlockType blockType = BlockDict[blockTypeStr];

        // Iterate through directions
        for (auto &blockDirection: blockToDirections.value().items()) {
            // Get texture uv's for each face
            std::string dir = blockDirection.key();
            std::vector<float> uvs;

            for (auto &uv: blockDirection.value()) {
                uvs.push_back(uv);
            }

            // Set atlas to the block direction
            if (dir == "top") {
                BlockFaceToUVs[blockType][Up] = uvs;
            } else if (dir == "bottom") {
                BlockFaceToUVs[blockType][Down] = uvs;
            } else if (dir == "side") {
                BlockFaceToUVs[blockType][Forward] = uvs;
                BlockFaceToUVs[blockType][Backward] = uvs;
                BlockFaceToUVs[blockType][Left] = uvs;
                BlockFaceToUVs[blockType][Right] = uvs;
            }
        }
    }

    std::cout << "precalculated uv's loaded" << std::endl;
}

json BlockDataManager::LoadBlockJSON(const char *blockJSONPath) {
    std::ifstream file(blockJSONPath);
    return json::parse(file);
}

BlockDataManager *blockDataManager;

#endif
