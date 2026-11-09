import numpy
import createMesh as cm
import sys, getopt

class Options():
    points2d = numpy.array( numpy.float )
    facets = numpy.array( numpy.int )
    visu = ''
    max_volume = numpy.float
    
def fileToArrs():    
    myOpts = Options()
    
    with open('domain.txt', 'r') as dom:
        batch = []
        currentType = ''
        for line in dom:
            if line.strip() == '':
                continue
            if 'points2d' in line:
                batch = []
                currentType = 'float'
                continue
            if 'facets' in line:
                batch = []
                currentType = 'int'
                continue
            if 'visu' in line:
                currentType = 'visu'
                continue            
            if 'end' in line:
                if( currentType == 'int' ):
                    myOpts.facets = numpy.loadtxt( batch, dtype = numpy.int, delimiter=' ' )
                if( currentType == 'float' ):
                    myOpts.points2d = numpy.loadtxt( batch, dtype = numpy.float, delimiter=' ' )                
                continue
            if( currentType == 'int' ):
                batch.append( line.strip() )
            if( currentType == 'float' ):
                batch.append( line.strip() )
            if( currentType == 'visu' ):
                myOpts.visu = line
            
    dom.close()   
    return myOpts    
    
def stringToArr( strng, arrType ):
    strng = strng.replace( '[', ' ' )
    strng = strng.replace( ']', ' ' )
    strng = strng.replace( '(', ' ' )
    strng = strng.replace( ')', ' ' )
    strng = strng.replace( ',', ' ' )
    strngArr = strng.split()
    arrFloat = numpy.array( strngArr )
    arrFloat = arrFloat.astype( arrType )
    arrFloat = arrFloat.reshape( len( arrFloat )/2, 2 )  
    return arrFloat
    
def main(argv):
    points2d = ''
    facets = ''
    domainFn = ''
    visu = ''
    max_volume = None
    try:
        opts, args = getopt.getopt(argv,"hp:f:d:v:m:",["points2d=","facets=","domain=","visualize=","max_volume="])
        if not opts:
            print "Empty arg list! Please use the following syntax to run" 
            inputSyntax()
            sys.exit()
    except getopt.GetoptError:
        inputSyntax()
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            inputSyntax()
            sys.exit()
        elif opt in ("-p", "--points2d"):
            points2d = arg
        elif opt in ("-f", "--facets"):
            facets = arg
        elif opt in ("-d", "--domain"):
            domainFn = arg   
        elif opt in ("-v", "--visualize"):
            visu = arg
        elif opt in ("-m", "--max_volume"):
            max_volume = float(arg)
    
    myOpts = Options()  
    if domainFn == '':
        myOpts.points2d = stringToArr( points2d, numpy.float ) 
        myOpts.facets = stringToArr( facets, numpy.int ) 
    else:
        myOpts = fileToArrs()
    myOpts.visu = visu        
    myOpts.max_volume = max_volume
    print 'points2d are "', myOpts.points2d
    print 'facets are "', myOpts.facets
    print 'domain file is "', domainFn
    
    return myOpts
    

    
def inputSyntax():
    print """
>>createMesh.py -p "[[x1, y1],[x2, y2],[x3, y3], ... ]" -f "[[0, 1],[1, 2], ... ]"
This creates a mesh from a domain defined by the 2d points (-p) and facets (-f).

>>createMesh.py -d <filename>
This creates a mesh from a domain defined in the <filename>.
...
$ filename.txt
points2d
0 0
2 0
2 2
0 2
facets
0 1
1 2
2 0
2 3
3 0"""  
    
myOpts = Options()    
if __name__ == "__main__":
    myOpts = main(sys.argv[1:])

meshObj = cm.createMesh( myOpts )
