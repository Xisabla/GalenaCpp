#ifndef GALENACPP_MEMORY_CLASS
#define GALENACPP_MEMORY_CLASS

#define BYTE_SIZE 8

#include <iostream>
#include <iomanip>

#include <algorithm>
#include <cmath>

#include <bitset>
#include <set>
#include <vector>

using namespace std;

class Memory
{
public:
    Memory(bool expandable = true, int size = 0);

    int size();

    bool is_reserved(int addr);
    int find_free_space(int size = 1);

    int reserve(int size = 1);
    int affect(int addr, bitset<BYTE_SIZE> block);
    int affect(int addr, vector<bitset<BYTE_SIZE>> blocks);
    int affect(bitset<BYTE_SIZE> block);
    int affect(vector<bitset<BYTE_SIZE>> blocks);

    bitset<BYTE_SIZE> &get(int addr);
    bitset<BYTE_SIZE> &operator[](int addr);

    void free(int addr, int size = 1);

    friend ostream &operator<<(ostream &os, Memory &m);

private:
    vector<bitset<BYTE_SIZE>> memory;
    set<int> addr_reserved;
    bool expandable;
};

#endif // !GALENACPP_MEMORY_CLASS