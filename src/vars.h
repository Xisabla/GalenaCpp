#include "./vartab_f.h"

//
// ─── TYPEDEF ────────────────────────────────────────────────────────────────────
//

enum vartype
{
    UNDEFINED = -1,
    FLOAT
};

typedef struct vm_linker
{
    char *name;
    int id;
    vartype type;
} vm_linker;

typedef struct vm_node
{
    vm_linker vml;
    struct vm_node *next;
} vm_node;

typedef struct varman
{
    vm_node *head;
    vartab_f *vt_f;
} varman;

// ────────────────────────────────────────────────────────────────────────────────

//
// ─── FUNCTIONS ──────────────────────────────────────────────────────────────────
//

varman *init_vm();

vm_node *create_vmnode(char *name, int id, vartype type);

vm_node *get_vmnode(varman *vm, char *name);

void insert_vmnode_back(varman *vm, vm_node *node);

void setvar_f(varman *vm, char *name, vartabt_f value);

vartabr_f getvar_f(varman *vm, char *name);

bool exists_var(varman *vm, char *name);

vartype type_var(varman *vm, char *name);

void show_var_f(varman *vm, char *name);

// ────────────────────────────────────────────────────────────────────────────────