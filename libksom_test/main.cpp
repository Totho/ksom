/* 
 * File:   main.cpp
 * Author: John
 *
 * Created on October 11, 2009, 1:14 PM
 */

#include <stdlib.h>
#include <stdio.h>
#include "ksom.h"

/*
 * 
 */
int main(int argc, char** argv) {
    KSOM_ERROR e = KSOM_OK;

    ksom_map map;
    ksom_map_options opt;

    opt.fv_size = 3;
    opt.x_dim = 10;
    opt.y_dim = 10;
    opt.init_k_value = 0.1;
    opt.num_iterations = 100;

    double test [] = {0, 0, 0};

    printf("initializing map... ");
    e = ksom_map_init(&map, &opt);
    if (KSOM_FAIL(e)) goto end;
    puts("done.");

    for (int i = 0; i < 10; ++i) {
        printf("cycle %-3d... ", map.iteration_count);
        e = ksom_map_cycle(&map, test);
        if (KSOM_FAIL(e)) goto end;
        puts("done.");
        printf("BMU: %p (%f, %f, %f)\n",
                map.bmu, map.bmu->fv[0], map.bmu->fv[1], map.bmu->fv[2]);
        printf("FVD: %f\n", map.bmu->fv_distance);
        printf("PHD: %f\n", map.bmu->bmu_distance);
        puts("---");
    }


    

    printf("freeing map... ");
    e = ksom_map_free(&map);
    if (KSOM_FAIL(e)) goto end;
    puts("done.");

    end:
    puts(ksom_error_str(e));
    return (EXIT_SUCCESS);
}

