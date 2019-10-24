#include "../src/Memory.h"

#include <string>

int main(int argc, char **argv)
{
    vector<bitset<8>> data;
    string str = "hello world";

    for (auto &c : str)
        data.push_back(bitset<8>(c));

    Memory m(true, 0);

    cout << m << endl;

    m.affect(data);

    m[9] = bitset<8>('o');
    m.free(8, 2);

    cout << m << endl;

    return 0;
}