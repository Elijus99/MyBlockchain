#pragma once
#ifndef TRANSACTIONS_GENERATOR_H_INCLUDED
#define TRANSACTIONS_GENERATOR_H_INCLUDED
#include "usersGenerator.h"
#include <fstream>
#include <string>
#include <random>
#include <vector>
using std::string;
using std::vector;
struct Transaction {
    string sender_id;
    string receiver_id;
    double value;
};

Transaction GenerateTransaction(size_t MaxUserId, double minTran, double maxTran);
vector<Transaction> GenerateTransactionsPool(size_t MaxUserId, size_t count, double minTran, double maxTran);
void GenerateTransactionsPoolFile(const string &fileName, size_t MaxUserId, size_t count, double minTran, double maxTran);
vector<Transaction> ReadTransactionsPoolFile(const string& fileName);
vector<Transaction> SelectTransactions(vector<Transaction>& TransactionsPool, vector<user>& users);
#endif
