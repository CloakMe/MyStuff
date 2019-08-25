import numpy
from numpy import *

def SetDiff( vec1, vec2 ):
    vec1WithoudVec2 = list(set(vec1) - set(vec2))
    return vec1WithoudVec2
