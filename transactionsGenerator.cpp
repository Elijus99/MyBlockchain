#include "transactionsGenerator.h"

Transaction GenerateTransaction(vector<user> users, double minTran, double maxTran)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution <int> genInt(0, (users.size() - 1));
    std::uniform_real_distribution <double> genDouble(minTran, maxTran);
    Transaction temp;
    do {
        temp.sender_id = genInt(mt);
        temp.receiver_id = genInt(mt);
    } while (temp.sender_id == temp.receiver_id);
    temp.sender = users[temp.sender_id].public_key;
    temp.receiver = users[temp.receiver_id].public_key;
    temp.value = genDouble(mt);
    temp.transaction_id = hash(temp.sender + " sent " + temp.receiver + " " + std::to_string(temp.value));
    return temp;
}
vector<Transaction> GenerateTransactionsPool(vector<user> users, size_t count, double minTran, double maxTran)
{
    vector<Transaction> TransactionsPool;
    for (size_t i = 0; i < count; i++) {
        Transaction temp = GenerateTransaction(users, minTran, maxTran);
        TransactionsPool.push_back(temp);
    }
    return TransactionsPool;
}
void GenerateTransactionsPoolFile(const string &fileName, vector<user> users, size_t count, double minTran, double maxTran)
{
    std::ofstream out(fileName);
    Transaction temp;
    temp = GenerateTransaction(users, minTran, maxTran);
    out << " " << temp.sender_id << " " << temp.sender << " " << temp.receiver_id << " " << temp.receiver << " " << std::to_string(temp.value) << " " << temp.transaction_id;
    for (size_t i = 1; i < count; i++) {
        temp = GenerateTransaction(users, minTran, maxTran);
        out << "\n" << " " << temp.sender_id << " " << temp.sender << " " << temp.receiver_id << " " << temp.receiver << " " << std::to_string(temp.value) << " " << temp.transaction_id;
    }
}
vector<Transaction> ReadTransactionsPoolFile(const string& fileName)
{
    vector<Transaction> transactions;
    Transaction temp;
    std::ifstream in(fileName);
    while (!in.eof()) {
        in >> temp.sender_id >> temp.sender >> temp.receiver_id >> temp.receiver >> temp.value >> temp.transaction_id;
        transactions.push_back(temp);
    }
    return transactions;
}
vector<vector<Transaction>> SelectTransactions(vector<Transaction>& TransactionsPool, vector<user>& users)
{
    vector<vector<Transaction>> candidates;
    vector<Transaction> BlockTransactions;
    std::random_device rd;
    std::mt19937 mt(rd());
    for (int i = 0; i < 5; i++) {
        vector<Transaction> temp = TransactionsPool;
        while (BlockTransactions.size() != 100 && temp.size() != 0) {
            std::uniform_int_distribution <int> gen(0, (temp.size() - 1));
            size_t i = gen(mt);
            if (users[temp[i].sender_id].ECoin > temp[i].value) {
                if (temp[i].transaction_id == hash(temp[i].sender + " sent " + temp[i].receiver + " " + std::to_string(temp[i].value))) {
                    BlockTransactions.push_back(temp[i]);
                    temp.erase(temp.begin() + i);
                }
                else {
                    cout << "A forged transaction was found and deleted" << endl;
                    TransactionsPool.erase(std::find(TransactionsPool.begin(), TransactionsPool.end(), temp[i]));
                    temp.erase(temp.begin() + i);
                }
            }
            else {
                TransactionsPool.erase(std::find(TransactionsPool.begin(), TransactionsPool.end(), temp[i]));
                temp.erase(temp.begin() + i);
            }
        }
        candidates.push_back(BlockTransactions);
        BlockTransactions.clear();
    }
    return candidates;
}
