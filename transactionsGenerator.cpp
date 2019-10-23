#include "transactionsGenerator.h"

Transaction GenerateTransaction(size_t MaxUserId, double minTran, double maxTran)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution <int> genInt(0, (MaxUserId - 1));
    std::uniform_real_distribution <double> genDouble(minTran, maxTran);
    Transaction temp;
    do {
        temp.sender_id = std::to_string(genInt(mt));
        temp.receiver_id = std::to_string(genInt(mt));
    } while (temp.sender_id == temp.receiver_id);
    temp.value = genDouble(mt);
    return temp;
}
vector<Transaction> GenerateTransactionsPool(size_t MaxUserId, size_t count, double minTran, double maxTran)
{
    vector<Transaction> TransactionsPool;
    for (size_t i = 0; i < count; i++) {
        TransactionsPool.push_back(GenerateTransaction(MaxUserId, minTran, maxTran));
    }
    return TransactionsPool;
}
void GenerateTransactionsPoolFile(const string &fileName, size_t MaxUserId, size_t count, double minTran, double maxTran)
{
    std::ofstream out(fileName);
    for (size_t i = 0; i < count; i++) {
        Transaction temp;
        temp = GenerateTransaction(MaxUserId, minTran, maxTran);
        out << temp.sender_id << " " << temp.receiver_id << " " << temp.value << std::endl;
    }
}
vector<Transaction> ReadTransactionsPoolFile(const string& fileName)
{
    vector<Transaction> transactions;
    Transaction temp;
    std::ifstream in(fileName);
    while (!in.eof()) {
        in >> temp.sender_id >> temp.receiver_id >> temp.value;
        transactions.push_back(temp);
    }
    return transactions;
}
vector<Transaction> SelectTransactions(vector<Transaction>& TransactionsPool, vector<user>& users)
{
    vector<Transaction> BlockTransactions;
    std::random_device rd;
    std::mt19937 mt(rd());
    while (BlockTransactions.size() != 100 && TransactionsPool.size() != 0) {
        std::uniform_int_distribution <int> gen(0, (TransactionsPool.size()-1));
        size_t i = gen(mt);
        Transaction temp;
        temp.sender_id = users[std::stoi(TransactionsPool[i].sender_id)].public_key;
        temp.receiver_id = users[std::stoi(TransactionsPool[i].receiver_id)].public_key;
        temp.value = TransactionsPool[i].value;
        users[std::stoi(TransactionsPool[i].sender_id)].ECoin -= temp.value;
        users[std::stoi(TransactionsPool[i].receiver_id)].ECoin += temp.value;
        BlockTransactions.push_back(temp);
        TransactionsPool.erase(TransactionsPool.begin() + i);
    }
    return BlockTransactions;
}
