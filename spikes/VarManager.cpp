#include "../src/VarManager.h"

int main(int argc, char **argv)
{

    VarManager vm(true, 1024);

    vm.set_double("foo", 12);
    vm.set_double("very_good_varname", 5154.1487);
    // cout << vm.set_int("bar", 12) << endl;

    vm.unset("foo");

    vector<bitset<8>> data;
    string str = "hello world; foo bar; let a = b";

    for (auto &c : str)
        data.push_back(bitset<8>(c));

    vm.get_mem().affect(data);

    vm.set_double("hello", 54);

    cout << vm.get_mem() << endl;
    cout << vm << endl;

    return 0;
}