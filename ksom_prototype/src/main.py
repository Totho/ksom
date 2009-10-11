# To change this template, choose Tools | Templates
# and open the template in the editor.

import ksom
import gui
import random
from Tkinter import *

__author__="John"
__date__ ="$Sep 28, 2009 7:37:37 PM$"




def colorFuncCellWeightColor(node):
    return gui.numToHexColor(node.fv)

def colorFuncShowNeighborhood(node):
    if node.physDistance <= node.network.nhRadius and node is not node.network.bmu:
        return 'blue'
    return colorFuncCellWeightColor(node)

def colorBMUCount(node):
    return gui.gsNumToHexColor(node.bmuCount)

class KSOMWindow(Frame):
    def __init__(self, app):
        Frame.__init__(self, app)
        self.network = ksom.Network(60, 60, 3, numIterations = 100,
            randFunc = lambda: random.randint(0, 255))
        self.grid = gui.Grid(self, self.network, pScale=6)

        f = Frame(self)
        Button(f, text='run', command=self.run).pack(side=LEFT)
        Button(f, text='step', command=self.step).pack(side=LEFT)
        Button(f, text='show nh', command=self.showNH).pack(side=LEFT)
        Button(f, text='show colors', command=self.showColors).pack(side=LEFT)        
        f.pack()

    #test 

    def step(self):
        self.network.cycle([random.randint(0, 255) for i in range(3)])

    def showNH(self):
        self.grid.setCellColors(colorFuncShowNeighborhood)

    def showColors(self):
        self.grid.setCellColors(colorFuncCellWeightColor)

    def run(self):
        for i in range(self.network.numIterations - 1):
            self.step()
            self.grid.setCellColors(colorFuncCellWeightColor)
            #self.grid.setCellColors(colorFuncShowNeighborhood)
            #self.grid.setCellColors(colorBMUCount)
            self.update()
            
if __name__ == "__main__":
    root = Tk()
    KSOMWindow(root).pack()
    root.mainloop()
