#ifndef GALENACPP_BINARY
#define GALENACPP_BINARY

#define BYTE_SIZE 8

#include <bitset>
#include <cmath>
#include <vector>

using namespace std;

namespace Binary
{
int bin_to_int(bitset<32> &b);
double bin_to_double(bitset<64> &b);

bitset<32> int_to_bin(int &n);
bitset<64> double_to_bin(double &d);
} // namespace Binary

#endif // !GALENACPP_BINARY