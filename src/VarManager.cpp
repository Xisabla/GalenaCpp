#include "VarManager.h"

VarManager::VarManager(bool expandable, int size) : memory(new Memory(expandable, size)){};

bool VarManager::is_set(string name)
{
    return linkers.find(name) != linkers.end();
}

int VarManager::size_of(type var_type)
{
    switch (var_type)
    {
    case INT:
        return 4;
    case DOUBLE:
        return 8;

    default:
        return 0;
        break;
    }
}

int VarManager::size_of(linker l)
{
    return size_of(l.var_type);
}

int VarManager::size_of(string name)
{
    if (!is_set(name))
        return 0;

    return size_of(linkers[name].var_type);
}

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
        linkers[name] = {addr, DOUBLE};

    return addr;
}

double VarManager::get_double(string name)
{
    if (!is_set(name))
        return (double)0;

    int addr = linkers[name].addr;

    if (addr + 8 > memory.size())
        return (double)0;

    bitset<64> b;

    for (int i = 0; i < 8; i++)
    {
        bitset<BYTE_SIZE> block = memory[addr + i];

        for (int j = 0; j < 8; j++)
        {
            b[(7 - i) * 8 + j] = block[j];
        }
    }

    return bin_to_double(b);
}

void VarManager::unset(string name)
{
    if (is_set(name))
    {
        int size = size_of(name);
        int addr = linkers[name].addr;

        memory.free(addr, size);

        linkers.erase(name);
    }
}

Memory &VarManager::get_mem()
{
    return memory;
}

ostream &operator<<(ostream &os, VarManager &vm)
{
    int name_size = 5;

    for (auto &l : vm.linkers)
        if (l.first.size() > name_size)
            name_size = l.first.size();

    int val_size = 10;

    os << "┌";
    for (int i = 0; i < name_size; i++)
        os << "─";

    os << "─────";

    for (int i = 0; i < val_size; i++)
        os << "─";

    os << "┐" << endl;

    for (auto &l : vm.linkers)
    {
        os << "| " << setw(name_size) << l.first << " | " << setw(val_size);
        if (l.second.var_type == DOUBLE)
            os << vm.get_double(l.first);
        // TODO: Show addr and size
        os << " |" << endl;
    }

    os << "└";
    for (int i = 0; i < name_size; i++)
        os << "─";

    os << "─────";

    for (int i = 0; i < val_size; i++)
        os << "─";

    os << "┘" << endl;

    return os;
}