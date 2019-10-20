#include <iostream>
#include <cmath>
using namespace std;

#include "../src/vartab_f.h"

int main()
{

    //
    // ─── CREATE VARTAB ──────────────────────────────────────────────────────────────
    //

    vartab_f *vartab = init_vartab_f();

    //
    // ─── ADD VALUE ──────────────────────────────────────────────────────────────────
    //

    cout << "ADD VALUE: " << endl;

    for (int i = 0; i < 15; i++)
    {
        add_vartabf_val(vartab, sqrt(i));
    }

    vartabn_f *node = vartab->head;

    while (node != NULL)
    {
        cout << node << ": " << node->value << " (" << node->id << ")" << endl;
        node = node->next;
    }

    //
    // ─── SET VALUE ──────────────────────────────────────────────────────────────────
    //

    cout << "SET VALUE: " << endl;

    for (int i = 0; i < 18; i += 4)
    {
        set_vartabf_val(vartab, i, sqrt(10 * (i + 1)));
    }

    node = vartab->head;

    while (node != NULL)
    {
        cout << node << ": " << node->value << " (" << node->id << ")" << endl;
        node = node->next;
    }

    //
    // ─── GET VALUE ──────────────────────────────────────────────────────────────────
    //

    cout << "GET VALUE: " << endl;

    for(int i = 0; i < 20; i++) {
        cout << i << ": " << (get_vartabf_val(vartab, i).status ? "(error)" : "(success)") << get_vartabf_val(vartab, i).v << endl;
    }

    return 0;
}