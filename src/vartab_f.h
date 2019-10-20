#include "stdlib.h"
#include "stdio.h"
#include "string.h"

//
// ─── TYPEDEF ────────────────────────────────────────────────────────────────────
//

enum vt_errc
{
    SUCCESS = 0,
    ERROR
};

typedef double vartabt_f;

typedef struct vartabn_f
{
    int id;
    vartabt_f value;
    struct vartabn_f *next;
} vartabn_f;

typedef struct vartab_f
{
    int id_it;
    vartabn_f *head;
    int size;
} vartab_f;

typedef struct vartabr_f
{
    vartabt_f v;
    vt_errc status;
} vartabr_f;

// ────────────────────────────────────────────────────────────────────────────────

//
// ─── FUNCTIONS ──────────────────────────────────────────────────────────────────
//

/**
 * Create empty vartable
 */
vartab_f *init_vartab_f();

/**
 * Create vartable node with a given value
 */
vartabn_f* create_vartabn_f(vartab_f *vartab, vartabt_f value);

/**
 * Fetch node with the given id inside the vartab
 * NULL if no node found
 */
vartabn_f* get_vartabn_f(vartab_f *vartab, int id);


/**
 * Insert the given node at the head of the vartable
 * All other nodes are shifted
 */
void insert_vartabn_head(vartab_f* vartab, vartabn_f* node);


/**
 * Insert the given node at the back of the vartable
 */
void insert_vartabn_back(vartab_f* vartab, vartabn_f* node);

/**
 * Create and add a node with a given value in the vartable
 */
int add_vartabf_val(vartab_f *vartab, vartabt_f value);

/**
 * Set the value of a node with a given id inside the vartable
 */
int set_vartabf_val(vartab_f *vartab, int id, vartabt_f value);

/**
 * Fetch vartable value for the given node id
 * If the id doesn't exist, "status" is "ERROR" and "v" is set to 0
 */
vartabr_f get_vartabf_val(vartab_f *vartab, int id);

// ────────────────────────────────────────────────────────────────────────────────