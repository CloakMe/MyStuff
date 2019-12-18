
with open( "Input/HMax.txt", 'r') as InputFile:
    
    for line in InputFile:
        line = line.strip()
        
        if len(line) > 0:
            try:
                hMax = map( float, line.split() )
                print "Reading Input/HMax.txt file..." + "hMax is " + line
            except ValueError:
                print "Could not assign hMax! Could not parse " + line + "to a valid number!"
                
        break
