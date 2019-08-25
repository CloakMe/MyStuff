#!/usr/bin/env python

import pdb
from numpy import *
from SetDiff import *
from Unique import *
from RightSide import *
from BndCond import *
from BndCondZero import *
from PlotTriData import *
from GetStiffnessMatrix3 import *
import time

def FEMLaplaceSolver():
    
    print "FEMLaplaceSolver"
    print "Python version"
    print "A program to demonstrate the finite element method."
    start_time = time.time()
    
    #Read node, element and dirichlet bnd cond data
    domainNodes    = numpy.loadtxt( "domPointsTri.dat", dtype = float ) #"domainNodes.dat"
    #print domainNodes.shape
    domainElements = numpy.loadtxt( "domElementsTri.dat", dtype = int ) #"domainElements3.dat"
    boundaryElements = numpy.loadtxt( "domFacetsTri.dat", dtype = int ) #"boundaryElements.dat"

    #domainElements = domainElements - 1
    #boundaryElements = boundaryElements - 1
    
    domNodesX = domainNodes.shape[ 0 ]
    A = numpy.zeros ( ( domNodesX, domNodesX ) )
    b = numpy.zeros ( ( domNodesX ) )
    
    print "Matrix size: ", domNodesX, domNodesX
    
    elapsed_time = time.time() - start_time
    print "Pre Processor time:               ", elapsed_time
    
    #Assembly
    start_time = time.time()
    
    domElementsX = domainElements.shape[ 0 ]
    for j in range(0, domElementsX):
        stiffMat = GetStiffnessMatrix3( domainNodes[ domainElements[ j,: ],: ] )
        #print stiffMat
        #pdb.set_trace()
        F = numpy.matrix( [ domainElements[j, ] ] )
        #print F
        A[ F.transpose(), domainElements[j, ] ] = A[ F.transpose(), domainElements[j, ] ] + stiffMat

    
    #Volume Forces.
    for j in range(0, domElementsX):
        #print "b = " + str( b[ domainElements[j, ] ]).strip('[]') 
        rs = RightSide( domainNodes[ domainElements[j, ], ] )
        #print rs
        #print "rs = " + str( rs ).strip( '[]') 
        b[ domainElements[j, ] ] = b[ domainElements[j, ] ] + rs
        
    elapsed_time = time.time() - start_time
    print "Assembly time:                    ", elapsed_time 
    
    #  Determine which nodes are associated with Dirichlet conditions.
    #  Assign the corresponding entries of U, and adjust the right hand side.
    start_time = time.time()
    
    u = numpy.zeros( ( domainNodes.shape[0] ) )
    bndNodes = Unique( boundaryElements )
    # Assign boundary condition to the solution vector u.
    u[ bndNodes ] = BndCondZero( domainNodes[ bndNodes, ] )
    UonBndNodes = numpy.dot( A, u )
    b = b - UonBndNodes
    
    elapsed_time = time.time() - start_time
    print "Boundary Condition Assembly time: ", elapsed_time  
    
    #  Compute the solution by solving A * U = B for the remaining unknown values of U.
    start_time = time.time()
    domNodes = Unique( domainElements )
    innerNodes = SetDiff ( domNodes, bndNodes )

    F = numpy.matrix( innerNodes )

    innerA = A[ F.transpose(), innerNodes ]
    innerB = b[ innerNodes ]
    linSolveResult = numpy.linalg.solve( innerA, innerB )
    
    u[ innerNodes ] = linSolveResult

    elapsed_time = time.time() - start_time
    print "Solution time:                    ", elapsed_time
    
    # Graphic representation.
    PlotTri( domainNodes, u, domainElements )
    
    #  Terminate.
    print "\n"
    print "FEM_50:\n"
    print "Normal end of execution.\n"
    
    return

FEMLaplaceSolver()
