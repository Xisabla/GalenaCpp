#include "../src/Binary.h"

#include "assert.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char **argv)
{
    vector<double> ds = {
        0.1256344905,
        0.7167253516,
        -4851000548.4615326636,
        -6769467048.6341942530,
        2e11,
        1.7e-8,
        3.14159265359793};

    vector<int> is = {
        4852,
        -4512848,
        148994749,
        -487794616,
        4,
        264898,
        -8,
        -46589};

    for (auto d : ds)
    {
        auto b = Binary::double_to_bin(d);

        cout << setprecision(20)
             << Binary::bin_to_double(b) << endl
             << d << endl;
    }

    for (auto i : is)
    {
        auto b = Binary::int_to_bin(i);

        cout << Binary::bin_to_int(b) << endl
             << i << endl;
    }

    return 0;
}