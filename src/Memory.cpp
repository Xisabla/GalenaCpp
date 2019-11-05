#include "Memory.h"

Memory::Memory(bool expandable, int size) : expandable(expandable), memory(size){};

int Memory::size()
{
    return memory.size();
}

bool Memory::is_reserved(int addr)
{
    return addr_reserved.find(addr) != addr_reserved.end();
}

int Memory::find_free_space(int size)
{
    int addr = -1;

    // No values in addr_reserved
    if (addr_reserved.size() == 0)
    {
        // And enough size
        if (memory.size() >= size)
            return 0;
        // Not enough size but expandable
        else if (expandable)
        {
            memory.resize(size);
            return 0;
        }

        // Not enough size and not expandable
        return -1;
    }

    // Sort reserved addresses
    vector<int> sorted(0);

    for (auto &addr : addr_reserved)
        sorted.push_back(addr);

    sort(sorted.begin(), sorted.end());

    // Check between values
    for (int i = 0; i < sorted.size() - 1; i++)
    {
        if (sorted[i + 1] - sorted[i] > size)
            return sorted[i] + 1;
    }

    // Check extremities
    if (sorted[0] >= size)
        return 0;

    if (memory.size() - sorted[sorted.size() - 1] > size)
        return sorted[sorted.size() - 1] + 1;

    // Expand if expandable
    if (expandable)
    {
        memory.resize(sorted[sorted.size() - 1] + size + 1);
        return sorted[sorted.size() - 1] + 1;
    }

    return addr;
}

int Memory::reserve(int size)
{
    int addr = find_free_space(size);

    for (int i = 0; i < size; i++)
        addr_reserved.insert(addr + i);

    return addr;
}

int Memory::affect(int addr, bitset<BYTE_SIZE> block)
{
    // If the address can't be in the memory, don't affect it
    if (addr < 0)
        return -1;
    if (addr >= memory.size())
        return -1;
    // If the address is not reserved
    if (!is_reserved(addr))
        return -1;

    memory[addr] = block;

    return addr;
}

int Memory::affect(int addr, vector<bitset<BYTE_SIZE>> blocks)
{
    vector<int> addrs(blocks.size());

    // Affect each block
    for (int i = 0; i < blocks.size(); i++)
    {
        addrs[i] = affect(addr + i, blocks[i]);
    }

    // Return first address
    return addrs[0];
}

// Both reserve memory AND affect block
int Memory::affect(bitset<BYTE_SIZE> block)
{
    return affect(reserve(), block);
}

// Both reserve memory AND affect block
int Memory::affect(vector<bitset<BYTE_SIZE>> blocks)
{
    return affect(reserve(blocks.size()), blocks);
}

bitset<BYTE_SIZE> &Memory::get(int addr)
{
    return memory[addr];
}

bitset<BYTE_SIZE> &Memory::operator[](int addr)
{
    return get(addr);
}

void Memory::free(int addr, int size)
{

    for (int i = 0; i < size; i++)
    {
        if (addr + i < memory.size())
        {
            memory[addr + i] = bitset<8>(0);
            addr_reserved.erase(addr + i);
        }
    }
}

ostream &operator<<(ostream &os, Memory &m)
{
    int addr_size = log10(m.memory.size()) + 1;

    os << "┌";

    for (int i = 0; i < addr_size; i++)
        os << "─";

    os << "─────────────┐" << endl;

    for (int i = 0; i < m.memory.size(); i++)
        if (m.is_reserved(i))
            os << "| " << setw(addr_size) << i << " | " << m.memory[i] << " |" << endl;

    os << "└";

    for (int i = 0; i < addr_size; i++)
        os << "─";

    os << "─────────────┘" << endl;
    os << "Size: " << m.memory.size() << " (" << m.memory.size() * 8 << " bits)" << endl;
    if (m.memory.size() > 0)
        os << "Reserved: " << m.addr_reserved.size() << " (" << m.addr_reserved.size() * 8 << " bits - " << setprecision(3) << (float)m.addr_reserved.size() / (float)m.memory.size() * 100 << "%)";

    return os;
}