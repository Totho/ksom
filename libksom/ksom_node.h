/* 
 * File:   ksom_node.h
 * Author: John
 *
 * Created on October 12, 2009, 8:37 PM
 */

#ifndef _KSOM_NODE_H
#define	_KSOM_NODE_H

#include "ksom_error.h"

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct _ksom_node {
        int x_pos;
        int y_pos;
        int fv_size;
        double *fv;
        double bmu_distance;
        double fv_distance;
    } ksom_node;    


    KSOM_ERROR ksom_node_init(ksom_node *node, int x_pos, int y_pos, int fv_size);
    KSOM_ERROR ksom_node_free(ksom_node *node);

#ifdef	__cplusplus
}
#endif

#endif	/* _KSOM_NODE_H */

