#include "grid.h"

Grid::Grid(int x, int y, int _cellSize) :
        xDim(x * _cellSize),
        yDim(y * _cellSize),
        xCells(x),
        yCells(y),
        cellSize(_cellSize) {
    img = cimg_library::CImg<unsigned char>(xDim, yDim, 1, 3);
    img.fill(0);
    disp = cimg_library::CImgDisplay(img);
    disp.set_title("KSOM Example");
}

Grid::~Grid() {
    
}

void Grid::randomFill() {
    for (int x = 0; x < xCells; ++x) {
        for (int y = 0; y < yCells; ++y) {
            unsigned char color [3] = {rand() % 255, rand() % 255, rand() % 255};
            setCellColor(x, y, color);
        }
    }
    img.display(disp);
}

void Grid::setCellColor(int x, int y, unsigned char* color) {
    if (x > xDim / cellSize || y > yDim / cellSize) {
        printf("Error: (%d, %d) over bounds\n", x, y);
        return;
    }

    if (x < 0 || y < 0) {
        puts("Error: x or y coord was below zero");
        return;
    }

    int x0 = cellSize * x;
    int y0 = cellSize * y;
    int x1 = cellSize * (x + 1);
    int y1 = cellSize * (y + 1);
    
    img.draw_rectangle(x0, y0, x1, y1, color);
}

void Grid::wait() {
    while (!disp.is_closed())
        disp.wait();
}

void Grid::wait(int millis) {
    disp.wait(millis);
}

void Grid::makeStatic() {
    while (!disp.is_closed())
        this->randomFill();
}

void Grid::refresh() {
    img.display(disp);
}
