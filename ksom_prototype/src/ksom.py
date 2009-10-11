# To change this template, choose Tools | Templates
# and open the template in the editor.

import math
import random

#test

__author__ = "John"
__date__ = "$Sep 28, 2009 7:04:36 PM$"




def euDistanceSq(vect1, vect2):
    distance = 0.0
    for v1, v2 in zip(vect1, vect2):
        distance += (v1 - v2) ** 2
    return distance



class Node:
    def __init__(self, network, xPos, yPos, randFunc):
        self.network = network
        self.physDistance = 0.0
        self.fvDistance = 0.0
        self.xPos = xPos
        self.yPos = yPos
        self.fv = [randFunc() for i in range(self.network.fvLen)]

        self.bmuCount = 0 #experimental

    def getCoordVector(self):
        return [self.xPos, self.yPos]

    def calcPhysDistance(self, node):
        self.physDistance = euDistanceSq(self.getCoordVector(),
                                         node.getCoordVector())
        return self.physDistance

    def calcFVDistance(self, fv):
        self.fvDistance = euDistanceSq(self.fv, fv)
        return self.fvDistance

    def train(self, fv):
        influence = math.exp(-self.physDistance / self.network.nhRadius * 2)
        for i in range(len(fv)):
            self.fv[i] += influence * (fv[i] - self.fv[i])


class Network:
    def __init__(self, xDim, yDim, fvLen, 
                 randFunc = random.random,
                 numIterations = 1000):
        self.mapRadius = (max(xDim, yDim) / 2.0) ** 2
        self.tConstant = numIterations / math.log10(self.mapRadius)
        self.KValueInit = 0.01
        self.kValue = 0.0
        self.numIterations = numIterations
        self.iterationCount = 1
        
        self.nhRadius = 0.0

        self.xDim = xDim
        self.yDim = yDim
        self.fvLen = fvLen
        self.nodes = []
        self.bmu = None

        for x in range(self.xDim):
            for y in range(self.yDim):
                self.nodes.append(Node(self, x, y, randFunc))
                
        self.setNHRadius()
        self.setLearningRate()


    def setNHRadius(self):
        self.nhRadius = self.mapRadius * math.exp(-float(self.iterationCount) / self.tConstant)

    def setLearningRate(self):
        self.kValue = self.KValueInit * math.exp(-float(self.iterationCount) / self.numIterations)

    def cycle(self, fv):
        if self.iterationCount > self.numIterations:
            raise Exception, 'too many iterations'

        self.bmu = None
        for node in self.nodes:
            node.calcFVDistance(fv)
            if self.bmu is None or node.fvDistance < self.bmu.fvDistance:
                self.bmu = node
                node.bmuCount += 1
                
        for node in self.nodes:
            node.calcPhysDistance(self.bmu)
            if node.physDistance < self.nhRadius:
                node.train(fv)

        self.iterationCount += 1

        self.setNHRadius()
        self.setLearningRate()

        #print 'nh radius: ', self.nhRadius
        #print 'k        : ', self.kValue
