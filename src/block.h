#ifndef BLOCK_H
#define BLOCK_H

#include "unordered_map"

const float BLOCK_SIZE = 0.5;
std::unordered_map<unsigned short int, Color> BLOCK_DICT {{1,RED}, {2,BLUE}, {3,GREEN}};

class Block {
    public:
        unsigned short int Material;
};

#endif
