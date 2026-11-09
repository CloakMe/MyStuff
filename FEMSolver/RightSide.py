import numpy
import pdb
from numpy import *

def RightSideIntegral( basisFunction, vertices, triangleArea):
    
    integral = \
    basisFunction[0] + basisFunction[1]*vertices[ 0, 0 ] + basisFunction[2]*vertices[ 0, 1 ] + \
    basisFunction[0] + basisFunction[1]*vertices[ 1, 0 ] + basisFunction[2]*vertices[ 2, 1 ] + \
    basisFunction[0] + basisFunction[1]*vertices[ 2, 0 ] + basisFunction[2]*vertices[ 2, 1 ]
       
    integral = triangleArea * integral/3;

    return integral

def RightSide( vertices ):
    #pdb.set_trace()
    colCnt = vertices.shape[1]
    localVector = numpy.zeros( (3, 1) )
    
    myMatrix = numpy.ones( ( 1, colCnt+1 ) )
    myMatrix = numpy.vstack( [ myMatrix, vertices.transpose() ] )
    
    myMatrix2 = numpy.ones( ( colCnt+1, 1 ) )
    myMatrix2 = numpy.hstack( [ myMatrix2, vertices] )
    basisFunctions = numpy.linalg.solve( myMatrix2, numpy.eye( colCnt+1 ) )
    xSize = basisFunctions.shape[0]
    
    triangleArea = abs( numpy.linalg.det( myMatrix )/2.0 )
    
    localVector[0] = 10*RightSideIntegral( basisFunctions[ :,0 ], vertices, triangleArea )
    localVector[1] = 10*RightSideIntegral( basisFunctions[ :,1 ], vertices, triangleArea )
    localVector[2] = 10*RightSideIntegral( basisFunctions[ :,2 ], vertices, triangleArea )
    
    return localVector
