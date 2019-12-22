import numpy
import math
import pdb
from ro import *
import matplotlib.pyplot as plt

def CalculateLeadMass( dataMatrix1, dataMatrix2 ):

    H = dataMatrix1[:,0]
    MPerpendicular = dataMatrix1[:,2]
    Mparallel = dataMatrix2[:,2]
    #print H
    #print Mparallel
    #print MPerpendicular
    #print '============================='
    factor1 = numpy.divide( Mparallel, H )
    factor11 = numpy.divide( MPerpendicular, H )
    factor2 = numpy.divide( MPerpendicular, ( 2*MPerpendicular + Mparallel ) )
   
    ResultVec = - 8.0 * math.pi * ro[0] * numpy.multiply( factor1, factor2 )
    etaVec = 1 + 2*factor2

    print
    
    #print ResultVec
    
    numpy.savetxt( 'Output/ResultVec.txt', ResultVec,  fmt="%0.8f" )
    numpy.savetxt( 'Output/EtaVec.txt', etaVec,  fmt="%0.8f" )
    numpy.savetxt( 'Output/MParOverH.txt', factor1,  fmt="%0.8f" )
    numpy.savetxt( 'Output/MPerOverH.txt', factor11,  fmt="%0.8f" )
    
    ResultVal = sum( ResultVec ) / float( len( ResultVec ) )
    print "Mass mean value: " + str( str( ResultVal )[ 1:-1 ] )[ 1:-1 ]

    print "Standard deviation " + str( numpy.std( ResultVec ) )

    print "Vector result saved in Output/ResultVec.txt & Output/EtaVec.txt"

    f1 = plt.figure()
    af1 = f1.add_subplot(211)
    af1.plot(MPerpendicular, etaVec)
    plt.xlabel("M Perpendicular")
    plt.ylabel("1-eta")
    
    af2 = f1.add_subplot(212)
    af2.plot(Mparallel, etaVec)
    plt.xlabel("M Mparallel")
    plt.ylabel("1-eta")

    f2 = plt.figure()
    afa = f2.add_subplot(211)
    afa.plot(H, factor1)
    plt.xlabel("H")
    plt.ylabel("MParalel/H")
    
    afb = f2.add_subplot(212)
    afb.plot(H, factor11)
    plt.xlabel("H")
    plt.ylabel("MPerpend/H")

    f3 = plt.figure()
    afc = f3.add_subplot(111)
    afc.plot(H, ResultVec)
    plt.xlabel("H")
    plt.ylabel("m_pb")
    
    plt.show()
    #plt.xlabel("M Perpendicular")
    #plt.ylabel("1-eta")
    #af2.plot(Mparallel, etaVec)   
    
    return 
