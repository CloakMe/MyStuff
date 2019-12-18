
import numpy
from CalculateLeadMass import *
from HMin import *
from HMax import *


def OpenFile( fileName ):

    firstDataSet = []
    secondDataSet = []
    currentLine = []
    counter = 0
    invalid = 0
    flag = False
    with open(fileName, 'r') as dataFile:
        for line in dataFile:
            line = line.strip()
               
            if len(line) > 0:
                try:
                    currentLine = map( float, line.split() )
                    #pdb.set_trace()
                    if flag == False and counter > 1 and  -0.0001 < currentLine[0] and currentLine[0] < 0.0001:
                        flag = True
                                
                    if flag == False and  hMin[0] <= currentLine[0] and currentLine[0] <= hMax[0]:
                        firstDataSet.append( currentLine )
                        
                    if flag == True and hMin[0] <= currentLine[0] and currentLine[0] <= hMax[0]:
                        secondDataSet.append( currentLine )
                        
                except ValueError:
                    if counter != 0:
                        print "row " + str( counter + 1 ) + " in the input file do not have valid floating point number!"
                        print "skipping the row..."
                        invalid = invalid + 1
                        
            counter = counter + 1

	print str(counter) + " lines from imput file : " + fileName + " : were read"
	if invalid>0:
            print str(invalid) + " line(s) from that file were incorect!" 

	rawData1 = numpy.matrix( firstDataSet )
	rawData2 = numpy.matrix( secondDataSet )

	if rawData1.shape[0] > rawData2.shape[0]:
		matrixData1 = rawData1[ 0:rawData2.shape[0],: ]
		matrixData2 = rawData2[ 0:,: ] 

	if rawData1.shape[0] < rawData2.shape[0]:
		matrixData1 = rawData1[ 0:,: ]
		matrixData2 = rawData2[ 0:rawData1.shape[0],: ]

        if rawData1.shape[0] == rawData2.shape[0]:
		matrixData1 = rawData1[ 0:,: ]
		matrixData2 = rawData2[ 0:,: ]	

        print str( 2 * matrixData1.shape[0] ) + " lines were saved due to HMin = " + str(hMin[0]) + ", HMax = " + str(hMax[0]) + " restriction"
        
        CalculateLeadMass( matrixData1, matrixData2 )
        
    return


