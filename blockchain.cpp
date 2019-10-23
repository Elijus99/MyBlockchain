#include "blockchain.h"

Blockchain::Blockchain() {
    string temp{"Genesis Block"};
    _Chain.emplace_back(Block(temp));
}

void Blockchain::AddBlock(Block newBlock) {
    newBlock.prevHash = _GetLastBlock().GetHash();
    newBlock.MineBlock();
    _Chain.push_back(newBlock);
}

Block Blockchain::_GetLastBlock() const {
    return _Chain.back();
}
