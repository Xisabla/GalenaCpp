#ifndef GALENACPP_VARMANAGER_CLASS
#define GALENACPP_VARMANAGER_CLASS

#include "./Memory.h"

class VarManager
{
public:
    VarManager(bool expandable = true, int size = 0);

    template <typename T>
    int set_var(string name, T value);

    // Memory &get_mem();

private:
    Memory memory;
};

template <typename T>
int VarManager::set_var(string name, T value)
{
    // case type string, case type char*, others
    if (typeid(T) == typeid(string))
        return -1; // TODO: Code for string
    if (typeid(T) == typeid(char *))
        return -1; // TODO: Code for char*

    int size = sizeof(value);

    auto bits = bitset<sizeof(value) * 8>(value);
    vector<bitset<8>> blocks;

    cout << bits << endl;

    for (int i = 0; i < size; i++)
    {
        bitset<8> block;

        for (int j = 0; j < 8; j++)
        {
            block[j] = bits[j + 8 * i];
        }

        blocks.push_back(block);
    }

    int addr = memory.affect(blocks);

    cout << memory << endl;

    return addr;
}

#endif // !GALENACPP_VARMANAGER_CLASS