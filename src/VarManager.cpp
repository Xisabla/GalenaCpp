#include "VarManager.h"

VarManager::VarManager(bool expandable, int size) : memory(new Memory(expandable, size)){};

int VarManager::set_double(string name, double value)
{

    bitset<64> b = double_to_bin(value);
    vector<bitset<BYTE_SIZE>> blocks;

    for (int i = 0; i < 8; i++)
    {
        blocks.push_back(bitset<BYTE_SIZE>());

        for (int j = 0; j < 8; j++)
        {
            blocks[i][j] = b[(7 - i) * 8 + j];
        }
    }

    int addr = memory.affect(blocks);

    if (addr != -1)
        linker[name] = addr;

    return addr;
}

Memory &VarManager::get_mem()
{

    return memory;
}