#include "hash.h"

const char character_table[16]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

char change_symbol(char a)
{
    int b;
    if (!((a >= 48 && a <= 57) || (a >= 97 && a <= 102)))
    {
        b = (int)a;
        b = b % 16;
        a = character_table[b];
    }
    return a;
}

string hash(string text)
{
    string defaultHash = "cgeVo3oGOdNKRZ4u8RgMhegdsgrU2rLq";
    for (unsigned int i = 0; i < text.length(); i++) {
        for (unsigned int j = 0; j < defaultHash.length(); j++) {
            int magic1 = 17 * text[i] * text[i];
            int magic2 = (j+2) * text[i] * j;
            int magicIndex = (i * j + text[i]) % defaultHash.length();
            int magicIndex2 = i * text[i] % defaultHash.length();
            defaultHash[j] = (defaultHash[j] + magic1 + i * j + magic2 + ((defaultHash[magicIndex] * text[i] + text[0]) ^ (defaultHash[magicIndex2]))) % 128;
        }
    }
    for (unsigned int i = 0; i < defaultHash.length(); i++) {
        defaultHash[i] = change_symbol(defaultHash[i]);
    }
    return defaultHash;
}
bool exist(const string& fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}
string InputFromFile(const string& fileName)
{
    std::ifstream in(fileName);
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}
std::chrono::duration<double> HashingEfficiency(const string& fileName)
{
        string line;
        vector<string> hashes;
        std::ifstream in(fileName);
        std::chrono::duration<double> totalTime = {};
        while (!in.eof()) {
            std::getline(in, line);
            auto start = std::chrono::high_resolution_clock::now();
            string temp = hash(line);
            auto end = std::chrono::high_resolution_clock::now();
            totalTime += (end - start);
        }
        return totalTime;
}
string CharToBinary(char c)
{
    string binary;
    for (int i = 7; i >= 0; --i)
        binary += ((c & (1 << i)) ? '1' : '0');
    return binary;
}
