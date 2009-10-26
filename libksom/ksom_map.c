#include "ksom_map.h"

#include <memory.h>
#include <math.h>


static void setLearningRate(ksom_map *map);
static void setNeighborhoodRadius(ksom_map *map);

KSOM_ERROR ksom_map_init(ksom_map *map, ksom_map_options *opts) {
    int x, y, i, node_index;

    map->iteration_count = 0;
    map->options = *opts;
    map->num_nodes = opts->x_dim * opts->y_dim;
    map->nodes = (ksom_node*) malloc(sizeof (ksom_node) * map->num_nodes);
    if (map->nodes == NULL)
        return KSOM_NOMEM;
    map->radius = pow(max(map->options.x_dim, map->options.y_dim), 2);
    map->t_constant = map->iteration_count / log10(map->radius);
    map->bmu = NULL;
    setLearningRate(map);
    setNeighborhoodRadius(map);

    node_index = 0;
    for (x = 0; x < opts->x_dim; ++x) {
        for (y = 0; y < opts->y_dim; ++y) {
            if (ksom_node_init(&map->nodes[node_index], x, y, map->options.fv_size) != KSOM_OK)
                return KSOM_INTERNAL;
            ++node_index;
        }
    }

    return KSOM_OK;
}



KSOM_ERROR ksom_map_free(ksom_map *map) {
    int i;
    
    if (map->nodes != NULL) {
        for (i = 0; i < map->num_nodes; ++i)
            ksom_node_free(&map->nodes[i]);
        free(map->nodes);
    }

    return KSOM_OK;
}



KSOM_ERROR ksom_map_cycle(ksom_map *map, double *fv) {
    double influence;
    int i, j;

    //calculate each node's fv's distance from
    // presented fv and find bmu
    for (i = 0; i < map->num_nodes; ++i) {
        map->nodes[i].fv_distance = 0;
        for (j = 0; j < map->options.fv_size; ++j)
            map->nodes[i].fv_distance += pow(map->nodes[i].fv[j] - fv[j], 2);
        if (map->bmu == NULL || map->nodes[i].fv_distance < map->bmu->fv_distance)
            map->bmu = &map->nodes[i];
    }

    //calculate each node's physical distance from
    // bmu and train accordingly
    for (i = 0; i < map->num_nodes; ++i) {
        map->nodes[i].bmu_distance = pow(map->nodes[i].x_pos - map->bmu->x_pos, 2)
                + pow(map->nodes[i].y_pos - map->bmu->y_pos, 2);
        influence = exp(map->nodes[i].bmu_distance / map->radius * 2);
        for (j = 0; j < map->options.fv_size; ++j)
            map->nodes[i].fv[j] += influence * (fv[j] - map->nodes[i].fv[j]);
    }

    ++map->iteration_count;

    setLearningRate(map);
    setNeighborhoodRadius(map);

    return KSOM_OK;
}





static void setLearningRate(ksom_map *map) {
    map->learning_rate = map->options.init_k_value *
            exp(-map->iteration_count / map->options.num_iterations);
}

static void setNeighborhoodRadius(ksom_map *map) {
    map->nh_radius = map->radius *
            exp(-map->iteration_count / map->t_constant);
}