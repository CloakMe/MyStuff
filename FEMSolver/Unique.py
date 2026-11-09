import numpy
from numpy import *

def Unique( array ):
    uniq, index = numpy.unique(array, return_index=True)
    tt = index.argsort()
    newUni = uniq[tt]
    return newUni
