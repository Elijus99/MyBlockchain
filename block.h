#pragma once
#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "transactionsGenerator.h"
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector>
using std::string;
using std::vector;

class Block {
public:
    Block(string Genesis);
    Block(const vector<Transaction> &TransactionsIn);
    string prevHash;
    string GetHash();
    void MineBlock();
    void BuildMerkleRoot();
private:
    size_t _Nonce;
    string _Hash;
    string _Version;
    time_t _Timestamp;
    string _MerkleRoot;
    size_t _Difficulty;
    string _CalculateHash() const;
    vector<Transaction> _Transactions;
};

#endif
