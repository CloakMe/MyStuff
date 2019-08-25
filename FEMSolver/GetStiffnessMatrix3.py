import numpy
from numpy import *

#basisFunction = b(1) + b(2)*x + b(3)*y 
def IntegralOfGradientsOfBasisFuns( basisFunction1, \
basisFunction2, \
triangleArea ):
                                         
    integral = ( basisFunction1[1] *basisFunction2[1] + \
    basisFunction1[2] *basisFunction2[2] ) * triangleArea;
    return integral

def GetStiffnessMatrix3( vertices ):

#*****************************************************************************80
#
# GetStiffnessMatrix3 determines the local stiffness matrix for a triangular element.
#
#  Discussion:
#
#    Although this routine is intended for 2D usage, the same formulas
#    work for tetrahedral elements in 3D.  The spatial dimension intended
#    is determined implicitly, from the spatial dimension of the vertices.
#
#  Modified:
#
#    23 February 2004
#
#  Author:
#
#    Jochen Alberty, Carsten Carstensen, Stefan Funken.
#
#  Reference:
#
#    Jochen Alberty, Carsten Carstensen, Stefan Funken,
#    Remarks Around 50 Lines of MATLAB:
#    Short Finite Element Implementation,
#    Numerical Algorithms,
#    Volume 20, pages 117-137, 1999.
#
#  Parameters:
#
#    Input, real VERTICES(1:(D+1),1:D), contains the D-dimensional 
#    coordinates of the vertices.
#
#    Output, real M(1:(D+1),1:(D+1)), the local stiffness matrix 
#    for the element.
#
#d = size ( vertices, 2 );

#D_eta = [ ones(1,d+1); vertices' ] \ [ zeros(1,d); eye(d) ];

#M = det ( [ ones(1,d+1); vertices' ] ) * (D_eta * D_eta') / prod ( 1:d );
  
    d = vertices.shape[ 1 ];
    myMatrix = numpy.ones( ( 1, d+1 ) )
    myMatrix = numpy.vstack([ myMatrix, vertices.transpose() ])
    triangleArea = abs( numpy.linalg.det( myMatrix )/2.0 )
    
    
    myMatrix2 = numpy.ones( ( d+1, 1 ) )
    myMatrix2 = numpy.hstack( [ myMatrix2, vertices ] )
    basisFunctions = numpy.linalg.solve( myMatrix2, numpy.eye( d+1 ) )
    xSize = basisFunctions.shape[0]
      
    integral_1_1 = IntegralOfGradientsOfBasisFuns( basisFunctions[:,0], basisFunctions[:,0], triangleArea )
    integral_1_2 = IntegralOfGradientsOfBasisFuns( basisFunctions[:,0], basisFunctions[:,1], triangleArea )
    integral_1_3 = IntegralOfGradientsOfBasisFuns( basisFunctions[:,0], basisFunctions[:,2], triangleArea )
    integral_2_2 = IntegralOfGradientsOfBasisFuns( basisFunctions[:,1], basisFunctions[:,1], triangleArea )
    integral_2_3 = IntegralOfGradientsOfBasisFuns( basisFunctions[:,1], basisFunctions[:,2], triangleArea )
    integral_3_3 = IntegralOfGradientsOfBasisFuns( basisFunctions[:,2], basisFunctions[:,2], triangleArea )
    
    M = numpy.matrix([ \
    [integral_1_1, integral_1_2, integral_1_3],\
    [integral_1_2, integral_2_2, integral_2_3], \
    [integral_1_3, integral_2_3, integral_3_3]])
    
    
# M = [ 1/2  -1/2   0; -1/2   1   -1/2; 0   -1/2  1/2];
#M = [ 1  -1/2 -1/2; -1/2 1/2   0; -1/2  0   1/2] *Det;
    return M



