/* 
 * File:   main.cpp
 * Author: John
 *
 * Created on October 11, 2009, 1:14 PM
 */

#include <stdlib.h>
#include <stdio.h>
#include "ksom.h"
#include "random.h"


void dump_map_fvdistances(ksom_map *map) {
    for (int i = 0; i < map->num_nodes; ++i) {
        printf("%-10f\n", map->nodes[i].bmu_distance);
    }
    printf("\n");
}

/*
 * 
 */
int main(int argc, char** argv) {
    KSOM_ERROR e = KSOM_OK;

    ksom_map map;
    ksom_map_options opt;

    double random_number = 0.0;
    double test [3];
    
    opt.fv_size = 3;
    opt.x_dim = 5;
    opt.y_dim = 5;
    opt.init_k_value = 0.1;
    opt.num_iterations = 100;


    //test random number generation functions
    printf("testing random\n");
    printf("initializing random... ");
    e = random_init();
    if (KSOM_FAIL(e)) goto end;
    printf("initialized.\n");

    printf("testing random (i=1000)... ");
    for (int i = 0; i < 1000; ++i) {
        random_number = random_uniform();
        if (random_number >= 1.0 || random_number <= 0.0) {
            printf("(iteration %d)error: number is %f\n", i, random_number);
            e = KSOM_INTERNAL;
            goto end;
        }
    }
    puts("ok.");
    puts("random ok.");

    printf("initializing map... ");
    e = ksom_map_init(&map, &opt);
    if (KSOM_FAIL(e)) goto end;
    puts("done.");

    for (int i = 0; i < map.num_nodes; ++i)
        printf("%10f %10f %10f\n", map.nodes[i].fv[0], map.nodes[i].fv[1], map.nodes[i].fv[2]);

    for (int i = 0; i < 10; ++i) {
        test[0] = random_uniform();
        test[1] = random_uniform();
        test[2] = random_uniform();

        printf("cycle %-3d... ", map.iteration_count);
        e = ksom_map_cycle(&map, test);
        if (KSOM_FAIL(e)) goto end;
        puts("done.");
        
        dump_map_fvdistances(&map);
    }


    

    printf("freeing map... ");
    e = ksom_map_free(&map);
    if (KSOM_FAIL(e)) goto end;
    puts("done.");

    end:
    printf("\n[!] %s\n", ksom_error_str(e));
    return (EXIT_SUCCESS);
}

