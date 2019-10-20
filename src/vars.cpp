#include "vars.h"

varman *init_vm()
{

    varman *vm = (varman *)malloc(sizeof(vm));

    vm->vt_f = init_vartab_f();

    return vm;
}

vm_node *create_vmnode(char *name, int id, vartype type)
{

    vm_node *node = (vm_node *)malloc(sizeof(vm_node));

    node->vml = {name, id, type};
    node->next = NULL;

    return node;
}

vm_node *get_vmnode(varman *vm, char *name)
{

    vm_node *node = vm->head;

    if (node == NULL)
        return NULL;

    while (strcmp(name, node->vml.name) != 0)
    {
        node = node->next;

        if (node == NULL)
            return NULL;
    }

    return node;
}

void insert_vmnode_back(varman *vm, vm_node *node)
{

    if (vm->head == NULL)
    {
        vm->head = node;
    }
    else
    {
        vm_node *last = vm->head;

        while (last->next != NULL)
            last = last->next;

        last->next = node;
    }
}

void setvar_f(varman *vm, char *name, vartabt_f value)
{

    vm_node *node = get_vmnode(vm, name);

    if (node == NULL)
    {
        node = create_vmnode(name, add_vartabf_val(vm->vt_f, value), FLOAT);
        insert_vmnode_back(vm, node);
    }
    else
    {
        if (node->vml.type == FLOAT)
        {
            set_vartabf_val(vm->vt_f, node->vml.id, value);
        }
        else
        {
            printf("ERROR: WRONG VARIABLE TYPE");
        }
    }
}

vartabr_f getvar_f(varman *vm, char *name)
{

    vm_node *node = get_vmnode(vm, name);

    if (node == NULL)
        return {0, ERROR};

    return get_vartabf_val(vm->vt_f, node->vml.id);
}

bool exists_var(varman *vm, char *name)
{

    return get_vmnode(vm, name) == NULL;
}

vartype type_var(varman *vm, char *name)
{

    vm_node *node = get_vmnode(vm, name);

    if (node == NULL)
        return UNDEFINED;

    return node->vml.type;
}

void show_var_f(varman *vm, char *name) {

    vartabr_f var = getvar_f(vm, name);

    if(var.status == ERROR) printf("Undefined %s\n", name);
    else printf("%s = %f\n", name, var.v);

}