#include "vartab_f.h"

vartab_f *init_vartab_f()
{
    
    vartab_f *vartab = (vartab_f *)malloc(sizeof(vartab_f));

    vartab->id_it = 0;
    vartab->size = 0;

    return vartab;
}

vartabn_f *create_vartabn_f(vartab_f *vartab, vartabt_f value)
{

    vartabn_f *node = (vartabn_f *)malloc(sizeof(vartabn_f));

    node->id = vartab->id_it++;
    node->value = value;
    node->next = NULL;

    return node;
}

vartabn_f *get_vartabn_f(vartab_f *vartab, int id)
{

    vartabn_f *node = vartab->head;

    if (node == NULL)
        return NULL;

    while (node->id != id)
    {
        node = node->next;

        if (node == NULL)
            return NULL;
    }

    return node;
}

void insert_vartabn_head(vartab_f *vartab, vartabn_f *node)
{

    if (vartab->head != NULL)
    {
        node->next = vartab->head;
        vartab->head = node;
    }

    vartab->head = node;
    vartab->size++;
}

void insert_vartabn_back(vartab_f *vartab, vartabn_f *node)
{

    if (vartab->head == NULL || vartab->size == 0)
    {
        vartab->head = node;
    }
    else
    {
        vartabn_f *last = vartab->head;

        while (last->next != NULL)
            last = last->next;

        last->next = node;
    }

    vartab->size++;
}

int add_vartabf_val(vartab_f *vartab, vartabt_f value)
{

    insert_vartabn_back(vartab, create_vartabn_f(vartab, value));

    return vartab->id_it - 1;
}

int set_vartabf_val(vartab_f *vartab, int id, vartabt_f value)
{

    vartabn_f *node = get_vartabn_f(vartab, id);

    if (node == NULL)
        return -1;

    node->value = value;

    return node->id;
}

vartabr_f get_vartabf_val(vartab_f *vartab, int id)
{

    vartabn_f *node = get_vartabn_f(vartab, id);

    if (node == NULL)
        return {0, ERROR};

    return {node->value, SUCCESS};
}