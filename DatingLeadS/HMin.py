
with open( "Input/HMin.txt", 'r') as InputFile:
    
    for line in InputFile:
        line = line.strip()
        
        if len(line) > 0:
            try:
                hMin = map( float, line.split() )
                print "Reading Input/HMin.txt file..." + "hMin is " + line
            except ValueError:
                print "Could not assign hMin! Could not parse " + line + "to a valid number!"
                
        break
