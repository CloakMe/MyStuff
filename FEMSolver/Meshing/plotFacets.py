import pdb
import numpy
from numpy import *

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm


def PlotFacets(u = 0):
    #Read node, element and dirichlet bnd cond data
    domainNodes    = numpy.loadtxt( "domPointsTri.dat", dtype = float ) #"domainNodes.dat"
    boundaryElements = numpy.loadtxt( "domFacetsTri.dat", dtype = int ) #"boundaryElements.dat"
    
    bndNodesEnum = numpy.unique( boundaryElements )
    bndNodes = domainNodes[ bndNodesEnum ]
    
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    
    # Plot the surface.
    scatter = ax.scatter(bndNodes[:,0], bndNodes[:,1], u) #
    plt.show()


