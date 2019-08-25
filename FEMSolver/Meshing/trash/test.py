
too = [(1,2),(3,4)]
def myFun( too, foo ):
    foo[0] = len( too )
    
doo = [ 0 ]    
myFun(too, doo)    
print doo