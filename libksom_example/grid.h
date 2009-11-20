/* 
 * File:   grid.h
 * Author: John
 *
 * Created on November 15, 2009, 7:51 PM
 */

#ifndef _GRID_H
#define	_GRID_H

#include "CImg.h"

#ifdef	__cplusplus
extern "C" {
#endif


    class Grid {
        
    public:
        Grid(int x, int y, int _cellSize);
        ~Grid();

        void setCellColor(int x, int y, unsigned char * color);
        void randomFill();
        void wait();
        void wait(int millis);
        void makeStatic();
        void refresh();


        int getYCells() const {
            return yCells;
        }
        int getXCells() const {
            return xCells;
        }
        int getYDim() const {
            return yDim;
        }
        int getXDim() const {
            return xDim;
        }

        
    private:
        cimg_library::CImg<unsigned char> img;
        cimg_library::CImgDisplay disp;
        int cellSize;
        int xDim;
        int yDim;
        int xCells;
        int yCells;
        
    };

#ifdef	__cplusplus
}
#endif

#endif	/* _GRID_H */

