import numpy
from numpy import *
import pdb

def BndCondZero( domainBndNodes ):
# U_D evaluates the Dirichlet boundary conditions.
#
#  Discussion:
#
#    The user must supply the appropriate routine for a given problem
#
#  Modified:
#
#    25 February 2004
#
#  Parameters:
#
#    Input, real U(N,M), contains the M-dimensional coordinates of N points.
#
#    Output, VALUE(N), contains the value of the Dirichlet boundary
#    condition at each point.
#
    result = numpy.zeros( ( domainBndNodes.shape[0] , 1 ) )
    return result
