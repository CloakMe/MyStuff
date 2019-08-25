from mpl_toolkits import mplot3d
#from matplotlib import pyplot
from plotFacets import PlotFacets

import numpy
import meshpy.triangle as triangle

if __package__ is None:
    import sys
    from os import path
    sys.path.append( path.dirname( path.dirname( path.abspath(__file__) ) ) )
    #from components.core import GameLoopEvents
    from PlotTriData import PlotTri
else:
    #from ..components.core import GameLoopEvents    
    from ..PlotTriData import PlotTri

def createMesh( myOpts ):  
    mesh_info = triangle.MeshInfo()
    mesh_info.set_points( myOpts.points2d )
    mesh_info.set_facets( myOpts.facets )
    
    mesh = triangle.build(mesh_info, volume_constraints=True, max_volume=myOpts.max_volume ) #
    #triangle.write_gnuplot_mesh( 'meshpyTri', mesh, False )
    
    with open('domElementsTri.dat', 'w') as domElements:
        for i in range(len(mesh.elements)):
            domElements.write( '%8s %8s %8s\n' % ( mesh.elements[i][0], mesh.elements[i][1], mesh.elements[i][2] ) )
            #print mesh.elements[i]
    domElements.close()
    
    with open('domFacetsTri.dat', 'w') as domFacets:
        for i in range(len(mesh.facets)):
            domFacets.write( '%8s %8s\n' % ( mesh.facets[i][0], mesh.facets[i][1] ) )
            #print mesh.facets[i]
    domFacets.close()
    
    with open('domPointsTri.dat', 'w') as domPoints:    
        for i in range(len(mesh.points)):
            domPoints.write( '%8s %8s\n' % ( mesh.points[i][0], mesh.points[i][1]) )
            #print mesh.points[i]    
    domPoints.close()
    
    #PlotFacets()
    if( myOpts.visu is not '' ):
        mshEl = numpy.array( mesh.elements )
        mshPts = numpy.array( mesh.points )
        dummyU = numpy.zeros( mshPts.shape[0] )
        PlotTri( mshPts, dummyU, mshEl )
    print "Triangulation finished!"
    
    return mesh




