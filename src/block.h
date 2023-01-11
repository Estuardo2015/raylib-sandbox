#ifndef BLOCK_H
#define BLOCK_H

#include "unordered_map"

const double BLOCK_SIZE = 0.5;
std::unordered_map<unsigned short int, Color> BLOCK_DICT {{1,BROWN}, {2,BLUE}};

class Block {
    public:
        unsigned short int Material;
};

#endif
