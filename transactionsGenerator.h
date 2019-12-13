#pragma once
#ifndef TRANSACTIONS_GENERATOR_H_INCLUDED
#define TRANSACTIONS_GENERATOR_H_INCLUDED
#include "usersGenerator.h"
#include "hash.h"
#include <fstream>
#include <string>
#include <random>
#include <vector>
using std::string;
using std::vector;
struct Transaction {
    bool operator==(const Transaction& rhs) const { return this->transaction_id == rhs.transaction_id; }
    string transaction_id;
    size_t sender_id;
    string sender;
    size_t receiver_id;
    string receiver;
    double value;
};

Transaction GenerateTransaction(vector<user> users, double minTran, double maxTran);
vector<Transaction> GenerateTransactionsPool(vector<user> users, size_t count, double minTran, double maxTran);
void GenerateTransactionsPoolFile(const string &fileName, vector<user> users, size_t count, double minTran, double maxTran);
vector<Transaction> ReadTransactionsPoolFile(const string& fileName);
vector<vector<Transaction>> SelectTransactions(vector<Transaction>& TransactionsPool, vector<user>& users);
#endif
