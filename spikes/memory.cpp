#include "../src/memory/memory.h"

int main()
{

    Memory m;

    m.set_double("a", 12);
    m.set_double("b", 5);
    m.set_double("c", -4);
    m.set_double("b", 2);

    m.unset("c");

    cout << m.get_double("a") << endl;
    cout << m.get_double("b") << endl;
    cout << m.get_double("c") << endl;

    cout << m.is_set("a") << endl;
    cout << m.is_set("b") << endl;
    cout << m.is_set("c") << endl;

    cout << m.get_type("a") << endl;
    cout << m.get_type("b") << endl;
    cout << m.get_type("c") << endl;

    return 0;
}