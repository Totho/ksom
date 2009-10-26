#include "ksom_node.h"
#include <stdlib.h>

KSOM_ERROR ksom_node_init(ksom_node *node, int x_pos, int y_pos, int fv_size) {
    int i;

    if (x_pos < 0 || y_pos < 0 || fv_size <= 0)
        return KSOM_INVALID_NODE_OPT;

    node->fv_size = fv_size;
    node->x_pos = x_pos;
    node->y_pos = y_pos;
    node->bmu_distance = 0;
    node->fv_distance = 0;
    node->fv = (double*)malloc(sizeof(double) * fv_size);

    if (node->fv == NULL)
        return KSOM_NOMEM;

    for (i = 0; i < fv_size; ++i)
        node->fv[i] = rand();
    
    return KSOM_OK;
}

KSOM_ERROR ksom_node_free(ksom_node *node) {
    if (node->fv != NULL)
        free(node->fv);
    return KSOM_OK;
}