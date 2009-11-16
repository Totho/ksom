/* 
 * File:   main.cpp
 * Author: John
 *
 * Created on November 3, 2009, 8:15 AM
 */

#include <stdlib.h>
#include "CImg.h"

using namespace cimg_library;

/*
 * 
 */
int main(int argc, char** argv) {
    CImg<unsigned char> img(640,400,1,3);
    img.fill(0);
    unsigned char purple[] = { 255,0,255 };
    unsigned char green[] = {0, 255, 0};

    for (int x = 0; x < 20; ++x) {
        for (int y = 0; y < 20; ++y) {
            unsigned char color[] = {rand()%255,rand()%255,rand()%255};
            img.draw_rectangle(x, x+1, y, y+1, color, 1);
        }
    }
    
    
    img.display("test");
    return 0;
}

