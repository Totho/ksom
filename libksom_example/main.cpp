/* 
 * File:   main.cpp
 * Author: John
 *
 * Created on November 3, 2009, 8:15 AM
 */

#include <stdlib.h>
#include <iostream>
#include "grid.h"
#include "ksom.h"
#include "config.h"
using namespace std;

static void repaint(Grid &grid, ksom_map &map);
static double random_uniform();

int main(int argc, char** argv) {
    cout << "parsing config file..." << endl;
    Config cfg("settings.cfg");
    cout << "initializing grid..." << endl << endl;
    Grid grid(cfg.getIntOption("xdim"), cfg.getIntOption("ydim"), cfg.getIntOption("pix_size"));
    ksom_map_options opt;
    ksom_map map;


    opt.x_dim = cfg.getIntOption("xdim");
    opt.y_dim = cfg.getIntOption("ydim");
    opt.fv_size = 3;    
    opt.num_iterations = cfg.getIntOption("num_iterations");
    opt.init_k_value = cfg.getDoubleOption("init_k_value");
    
    cout << "initializing map..." << endl;
    if (ksom_map_init(&map, &opt) != KSOM_OK) {
        cout << "Could not initialize map" << endl;
        goto end;
    }

    cout << "beginning training cycles" << endl;
    for (int i = 0; i < map.options.num_iterations; ++i) {
        repaint(grid, map);
        double random[3] = {random_uniform(),random_uniform(),random_uniform()};
        ksom_map_cycle(&map, random);
        cout << "cycle " << map.iteration_count << endl
                << "bmu coords: " << map.bmu->x_pos << "," << map.bmu->y_pos << endl
                << "learning rate: " << map.learning_rate << endl
                << "nh radius: " << map.nh_radius << endl
                << endl;
    }

    cout << endl << "training done" << endl;

end:
    grid.wait();
    ksom_map_free(&map);
    getchar();
    return 0;
}



static void repaint(Grid &grid, ksom_map &map) {
    for (int i = 0; i < map.num_nodes; ++i) {
        ksom_node node = map.nodes[i];
        unsigned char color [3];
        color[0] = (unsigned char) (node.fv[0] * 256);
        color[1] = (unsigned char) (node.fv[1] * 256);
        color[2] = (unsigned char) (node.fv[2] * 256);
        grid.setCellColor(node.x_pos, node.y_pos, color);
    }
    grid.refresh();
}

static double random_uniform() {
    return (double) (rand() + 1) / (double) (RAND_MAX + 1);
}
