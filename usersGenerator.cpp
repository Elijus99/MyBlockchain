#include "usersGenerator.h"

const char char_table[62]{ '0','1','2','3','4','5','6','7','8','9',
'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

string GenerateString(size_t length)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution <int> gen(0, 61);
    string temp = "";
    for (unsigned int j = 0; j < length; j++) {
        temp += char_table[gen(mt)];
    }
    return temp;
}
double GenerateDouble(size_t min, size_t max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution <double> gen(min, max);
    return gen(mt);
}

user GenerateUser(size_t nameLength, size_t public_key_length, size_t balanceMin, size_t balanceMax)
{
    user temp;
    temp.name = GenerateString(nameLength);
    temp.public_key = GenerateString(public_key_length);
    temp.ECoin = GenerateDouble(balanceMin, balanceMax);
    return temp;
}
vector<user> GenerateUsers(size_t usersCount, size_t nameLength, size_t public_key_length, size_t balanceMin, size_t balanceMax)
{
    vector<user> temp;
    for (size_t i = 0; i < usersCount; i++) {
        temp.push_back(GenerateUser(nameLength, public_key_length, balanceMin, balanceMax));
    }
    return temp;
}
void GenerateUsersFile(const string &fileName, size_t usersCount, size_t nameLength, size_t public_key_length, size_t balanceMin, size_t balanceMax)
{
    std::ofstream out(fileName);
    for (size_t i = 0; i < usersCount; i++) {
        user temp;
        temp = GenerateUser(nameLength, public_key_length, balanceMin, balanceMax);
        out << temp.name << " " << temp.public_key << " " << temp.ECoin << std::endl;
    }
}
vector<user> ReadUsersFile(const string& fileName)
{
    vector<user> users;
    user temp;
    std::ifstream in(fileName);
    while (!in.eof()) {
        in >> temp.name >> temp.public_key >> temp.ECoin;
        users.push_back(temp);
    }
    return users;
}
