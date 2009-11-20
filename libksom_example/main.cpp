/* 
 * File:   main.cpp
 * Author: John
 *
 * Created on November 3, 2009, 8:15 AM
 */

#include <stdlib.h>
#include "grid.h"
#include "ksom.h"

static void repaint(Grid &grid, ksom_map &map);

double random_uniform() {
    return (double) (rand() + 1) / (double) (RAND_MAX + 1);
}

const static int XDIM = 200;
const static int YDIM = 200;

int main(int argc, char** argv) {
    char * error = "No error";
    Grid grid(XDIM, YDIM, 3);
    ksom_map_options opt;
    ksom_map map;

    opt.x_dim = XDIM;
    opt.y_dim = YDIM;
    opt.fv_size = 3;
    opt.num_iterations = 1000;
    opt.init_k_value = .1;

    if (ksom_map_init(&map, &opt) != KSOM_OK) {
        error = "Could not initialize map";
        goto end;
    }

    for (int i = 0; i < map.options.num_iterations; ++i) {
        repaint(grid, map);
        double random[3] = {random_uniform(),random_uniform(),random_uniform()};
        ksom_map_cycle(&map, random);
        printf("\r[%04i]bmu:(%03i,%03i)",
                map.iteration_count,
                map.bmu->x_pos, map.bmu->y_pos),
                map.nh_radius;
    }
    
end:
    printf("\n[%s]\n", error);
    grid.wait();
    ksom_map_free(&map);
    return 0;
}



static void repaint(Grid &grid, ksom_map &map) {
    for (int i = 0; i < map.num_nodes; ++i) {
        ksom_node node = map.nodes[i];
        unsigned char color [3];
        color[0] = (unsigned char) (node.fv[0] * 255);
        color[1] = (unsigned char) (node.fv[1] * 255);
        color[2] = (unsigned char) (node.fv[2] * 255);
        grid.setCellColor(node.x_pos, node.y_pos, color);
    }
    grid.refresh();
}