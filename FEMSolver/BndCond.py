import numpy
from numpy import *
import pdb

def BndCond( domainBndNodes ):
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
    c = 0;
    x = numpy.matrix( domainBndNodes[ :, 0 ] ).transpose()
    y = numpy.matrix( domainBndNodes[ :, 1 ] ).transpose()
    xx = numpy.multiply( x - 0.5, x - 0.5 )
    yy = numpy.multiply( y - 0.5, y - 0.5 )
    pdb.set_trace();
    up = ( 1 - c*c )*xx - yy
    down = numpy.multiply( ( 1 - c*c )*xx + yy ,  ( 1 - c*c )*xx + yy ) 
    result = numpy.divide( up, down )
    pdb.set_trace();
    return result
