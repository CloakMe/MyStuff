import numpy
import math
import pdb
from ro import *

def CalculateLeadMass( dataMatrix1, dataMatrix2 ):

    H = dataMatrix1[:,0]
    MPerpendicular = dataMatrix1[:,2]
    Mparallel = dataMatrix2[:,2]

    
    factor1 = numpy.divide( Mparallel, H )
    factor2 = numpy.divide( MPerpendicular, ( 2*MPerpendicular + Mparallel ) )

    HelpVec = [ - 8.0 * math.pi * ro[0] ] * H.shape[0]
    HelpVecAsMatrix = numpy.matrix( HelpVec )
    factor3 = numpy.multiply( HelpVecAsMatrix.T, factor1 )
    
    ResultVec = numpy.multiply( factor2, factor3 )

    print
    
    #print ResultVec
    
    numpy.savetxt( 'Output/ResultVec.txt', ResultVec,  fmt="%0.8f" )
    ResultVal = sum( ResultVec ) / float( len( ResultVec ) )
    print "Mass mean value: " + str( str( ResultVal )[ 1:-1 ] )[ 1:-1 ]

    print "Standard deviation " + str( numpy.std( ResultVec ) )

    print "Vector result saved in Output/ResultVec.txt"
    return 
