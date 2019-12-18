from OpenFile import *

with open( "Input/InputFile.txt", 'r') as dataFile:
    for line in dataFile:
        line = line.strip()
        
        if len(line) > 0:
            print "Reading file: " + line
            OpenFile( line )

        break

