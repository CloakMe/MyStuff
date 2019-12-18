
with open( "Input/ro.txt", 'r') as InputFile:

    for line in InputFile:
        line = line.strip()
        
        if len(line) > 0:
            try:
                ro = map( float, line.split() )
                print "Reading Input/ro.txt file..." + "ro is " + line
            except ValueError:
                print "Could not assign ro! Could not parse " + line + "to a valid number!"
                
        break
