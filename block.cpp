#include "Block.h"
#include "hash.h"
using std::cout;
using std::endl;
using std::stringstream;

Block::Block(string Genesis) {
    _Nonce = -1;
    _Difficulty = 5;
    _Version = "v0.1";
    _MerkleRoot = hash(Genesis);
    _Timestamp = time(nullptr);
}
Block::Block(const vector<Transaction> &TransactionsIn) : _Transactions(TransactionsIn) {
    _Nonce = -1;
    _Difficulty = 3;
    BuildMerkleRoot();
    _Timestamp = time(nullptr);
}

string Block::GetHash() {
    return _Hash;
}

void Block::MineBlock() {
    string str(_Difficulty, '0');
    str[_Difficulty] = '\0';
    do {
        _Nonce++;
        _Hash = _CalculateHash();
    } while (_Hash.substr(0, _Difficulty) != str);

    cout << "Block mined: " << _Hash << endl;
}

inline string Block::_CalculateHash() const {
    stringstream ss;
    ss << _Timestamp << _Version << _Nonce << prevHash << _MerkleRoot;
    return hash(ss.str());
}

void Block::BuildMerkleRoot() {
    vector<string> hashes;
    for (size_t i = 0; i < _Transactions.size(); i++) {
        hashes.push_back(hash(_Transactions[i].sender_id + " sent " + _Transactions[i].receiver_id + " " + std::to_string(_Transactions[i].value)));
    }
    while (hashes.size() > 1) {
        if (hashes.size() % 2 == 1) {
            hashes.push_back(hashes[hashes.size() - 1]);
        }
        int i = 0;
        for (size_t j = 0; j < hashes.size(); j+=2) {
            hashes[i] = hash(hashes[j] + hashes[j + 1]);
            i++;
        }
        hashes.resize(hashes.size()/2);
    }
    _MerkleRoot = hashes[0];
}
