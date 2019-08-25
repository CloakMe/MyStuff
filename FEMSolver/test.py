import numpy
from numpy import *

domainNodes    = numpy.genfromtxt( "coordinates.dat", delimiter=" ")
size = domainNodes.shape

print size
a = 4
b = 3
xx = a + \
b
print xx