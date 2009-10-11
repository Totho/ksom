# To change this template, choose Tools | Templates
# and open the template in the editor.

from Tkinter import *

__author__="John"
__date__ ="$Sep 29, 2009 5:14:30 AM$"


def gsNumToHexColor(num):
    if num > 255: num = 255
    elif num < 0: num = 0
    return '#' + '%x' * 3 % (num, num, num)

def numToHexColor(rgb):
    for v in rgb:
        if v > 255: v = 255
        elif v < 0: v = 0
    return '#' + '%-2x' * 3 % tuple(rgb)

class Grid:
    def __init__(self, frame, network, pScale):
        self.network = network
        self.pScale = pScale
        self.canvas = Canvas(
            frame,
            width = network.xDim * self.pScale,
            height = network.yDim * self.pScale,
            bg = 'black'
        )
        self.cells = [
            [None for x in range(self.network.xDim)]
                for y in range(self.network.yDim)
        ]
        for xPos in range(self.network.xDim):
            for yPos in range(self.network.yDim):
                self.cells[xPos][yPos] = self.createCell(xPos, yPos)
        self.canvas.pack()

    def createCell(self, xPos, yPos, color='#FFF'):
        return self.canvas.create_rectangle(
            self.pScale * xPos,
            self.pScale * yPos,
            self.pScale * (xPos + 1),
            self.pScale * (yPos + 1),
            fill = color
        )

    def setCellColor(self, xPos, yPos, color):
        self.canvas.itemconfig(self.cells[xPos][yPos], fill = color)

    def setCellColors(self, colorFunc=lambda x: '#FFF'):
        for node in self.network.nodes:
            self.setCellColor(node.xPos, node.yPos, colorFunc(node))
