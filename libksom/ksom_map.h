/* 
 * File:   ksom_map.h
 * Author: John
 *
 * Created on October 12, 2009, 8:23 PM
 */

#ifndef _KSOM_MAP_H
#define	_KSOM_MAP_H

#include "ksom_error.h"
#include "ksom_node.h"

#ifdef	__cplusplus
extern "C" {
#endif
    #define max(a, b) a > b ? a : b
    
    typedef struct _ksom_map_options {
        int x_dim;
        int y_dim;
        int fv_size;
        int num_iterations;
        double init_k_value;
    } ksom_map_options;

    typedef struct _ksom_map{
        ksom_map_options options;
        int num_nodes;
        int radius;
        double learning_rate;
        double t_constant;
        int iteration_count;
        int nh_radius;
        ksom_node *bmu;
        ksom_node *nodes;
    } ksom_map;

    
    
    KSOM_ERROR ksom_map_init(ksom_map *map, ksom_map_options *opts);
    KSOM_ERROR ksom_map_cycle(ksom_map *map, double *fv);
    KSOM_ERROR ksom_map_free(ksom_map *map);

#ifdef	__cplusplus
}
#endif

#endif	/* _KSOM_MAP_H */

