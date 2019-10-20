#include <iostream>
#include <cmath>
using namespace std;

#include "../src/vars.h"

int main()
{
    varman *vm = init_vm();

    setvar_f(vm, strdup("b"), 1.2);
    setvar_f(vm, strdup("c"), 0.8);
    setvar_f(vm, strdup("b"), 0.2);

    show_var_f(vm, strdup("a"));
    show_var_f(vm, strdup("b"));
    show_var_f(vm, strdup("c"));
    
    cout << "a: " << exists_var(vm, strdup("a")) << " " << type_var(vm, strdup("a")) << endl;
    cout << "b: " << exists_var(vm, strdup("b")) << " " << type_var(vm, strdup("b")) << endl;
    cout << "c: " << exists_var(vm, strdup("c")) << " " << type_var(vm, strdup("c")) << endl;

    return 0;
}