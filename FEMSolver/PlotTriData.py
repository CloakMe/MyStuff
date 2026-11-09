from mpl_toolkits.mplot3d import Axes3D
#from mpl_toolkits.mplot3d import art3d
import matplotlib.pyplot as plt
import matplotlib as mplt
from matplotlib import cm

def PlotTri( nodes, u, my_triangulation ):

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    #tri3 = mplt.tri.Triangulation(nodes[:, 0], nodes[:, 1], triangles=my_triangulation, mask=None)
    #ax.plot_trisurf( tri3, u, cmap=cm.coolwarm )

    ax.plot_trisurf( nodes[:, 0], nodes[:, 1], u, triangles=my_triangulation, cmap=cm.coolwarm )

    # Show the plot to the screen
    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')

    plt.show()    
    return
