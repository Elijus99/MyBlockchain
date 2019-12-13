#include "Block.h"
#include "hash.h"
using std::cout;
using std::endl;
using std::stringstream;

Block::Block(string Genesis) {
    _Nonce = -1;
    _Difficulty = 4;
    _Version = "v0.1";
    _MerkleRoot = hash(Genesis);
    _Timestamp = time(nullptr);
}
Block::Block(const vector<vector<Transaction>> &TransactionsIn) : _Transactions(TransactionsIn) {
    _Nonce = -1;
    _Difficulty = 4;
    _Version = "v0.1";
    BuildMerkleRoot();
    _Timestamp = time(nullptr);
}

string Block::GetHash() {
    return _Hash;
}

void Block::MineBlock() {
    string str(_Difficulty, '0');
    str[_Difficulty] = '\0';
    size_t maxTries = 100000;
    std::random_device rd;
    std::mt19937 mt(rd());
    int position;
    do {
        int maxRoll = _Transactions.size() - 1;
        vector<int> rollValue;
        for (size_t i = 0; i < _Transactions.size(); i++) {
            rollValue.push_back(i);
        }
        do {
            std::uniform_int_distribution <int> genInt(0, maxRoll); 
            position = genInt(mt);
            _MerkleRoot = _MerkleRoots[rollValue[position]]; 
            _Nonce = 0;
            do {
                _Nonce++;
                _Hash = _CalculateHash();
            } while ((_Hash.substr(0, _Difficulty) != str) && _Nonce != maxTries);
            rollValue.erase(rollValue.begin() + position);
            maxRoll--;
        } while ((_Hash.substr(0, _Difficulty) != str) && maxRoll != -1);
        maxTries += 100000;
    } while (_Hash.substr(0, _Difficulty) != str);
    cout << "Block mined: " << _Hash << endl;
    _WinnerID = position;
}

inline string Block::_CalculateHash() const {
    stringstream ss;
    ss << _Timestamp << _Version << _Nonce << prevHash << _MerkleRoot;
    return hash(ss.str());
}

void Block::BuildMerkleRoot() {
    vector<string> temp;
    vector<vector<string>> hashes;
    for (size_t i = 0; i < _Transactions.size(); i++) {
        for (size_t j = 0; j < _Transactions[i].size(); j++) {
            temp.push_back(_Transactions[i][j].transaction_id);
        }
        hashes.push_back(temp);
        temp.clear();
    }
    for (size_t i = 0; i < _Transactions.size(); i++) {
        while (hashes[i].size() > 1) {
            if (hashes[i].size() % 2 == 1) {
                hashes[i].push_back(hashes[i][hashes.size() - 1]);
            }
            int k = 0;
            for (size_t j = 0; j < hashes[i].size(); j += 2) {
                hashes[i][k] = hash(hashes[i][j] + hashes[i][j + 1]);
                k++;
            }
            hashes[i].resize(hashes[i].size() / 2);
        }
        _MerkleRoots.push_back(hashes[i][0]);
    }
}
int Block::getWinnerID() {
    return _WinnerID;
}
