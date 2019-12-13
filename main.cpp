#include "blockchain.h"
#include <iomanip>
#include <algorithm>
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
        vector<vector<Transaction>> candidates = SelectTransactions(TransactionsPool, users);
        cout << "Mining block " << i << "..." << endl;
        bChain.AddBlock(candidates);
        int winnerID = bChain.getBlockWinnerID();
        vector<Transaction> temp = candidates[winnerID];
        for (int i = 0; i < temp.size(); i++) {
            TransactionsPool.erase(std::find(TransactionsPool.begin(), TransactionsPool.end(), temp[i]));
        }
        i++;
    }
    cout << "Transactions Pool has been emptied!" << endl;
    return 0;
}
