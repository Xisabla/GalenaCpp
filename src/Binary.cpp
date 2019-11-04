#include "Binary.h"

int Binary::bin_to_int(bitset<32> &b)
{
    return (int)b.to_ulong();
}

double Binary::bin_to_double(bitset<64> &b)
{

    int alpha = -1023;
    double frac = 1;

    for (int i = 0; i < 11; i++)
    {
        if (b.test(52 + i))
            alpha += (int)pow(2., (float)i);
    }

    for (int i = 1; i < 52; i++)
    {
        if (b.test(52 - i))
            frac += pow(2., (float)-i);
    }

    if (b.test(63))
        frac *= -1;

    return frac * pow(2., alpha);
}

bitset<32> Binary::int_to_bin(int &n)
{
    return bitset<32>(n);
}

bitset<64> Binary::double_to_bin(double &d)
{
    return bitset<64>(*reinterpret_cast<unsigned long long *>(&d));
}