#pragma once
#ifndef BLOCKCHAIN_H_INCLUDED
#define BLOCKCHAIN_H_INCLUDED
#include "Block.h"
#include <vector>
using std::vector;

class Blockchain {
public:
    Blockchain();
    void AddBlock(Block newBlock);
private:
    vector<Block> _Chain;
    Block _GetLastBlock() const;
};

#endif
