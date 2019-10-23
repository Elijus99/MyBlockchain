#include "blockchain.h"
#include <iomanip>
using std::cout;
using std::endl;

int main() {
    Blockchain bChain;
    vector<user> users;
    vector<Transaction> TransactionsPool;
    users = ReadUsersFile("users.txt");
    TransactionsPool = ReadTransactionsPoolFile("transactions.txt");
    size_t i = 1;
    while (TransactionsPool.size() > 0) {
        vector<Transaction> BlockTransactions = SelectTransactions(TransactionsPool, users);
        cout << "Mining block " << i <<"..." << endl;
        bChain.AddBlock(BlockTransactions);
        i++;
    }
    return 0;
}
