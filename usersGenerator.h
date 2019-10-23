#pragma once
#ifndef USERS_GENERATOR_H_INCLUDED
#define USERS_GENERATOR_H_INCLUDED
#include <fstream>
#include <string>
#include <random>
#include <vector>
using std::string;
using std::vector;
struct user {
    string name;
    string public_key;
    double ECoin;
};

string GenerateString(size_t length);
double GenerateDouble(size_t min, size_t max);
user GenerateUser(size_t nameLength, size_t public_key_length, size_t balanceMin, size_t balanceMax);
vector<user> GenerateUsers(size_t usersCount, size_t nameLength, size_t public_key_length, size_t balanceMin, size_t balanceMax);
void GenerateUsersFile(const string& fileName, size_t usersCount, size_t nameLength, size_t public_key_length, size_t balanceMin, size_t balanceMax);
vector<user> ReadUsersFile(const string& fileName);
#endif
