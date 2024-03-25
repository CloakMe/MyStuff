import numpy as np

input_list = [1, 7, 10, 11]

def custom_map(input_list, ext):
    newarray = np.zeros((len(input_list)-1) * ext + 1, float)
    for i in range(len(input_list)-1):
        quote = float(input_list[i+1] - input_list[i])/ext
        for j in range(ext):
            newarray[i*ext + j] = input_list[i] + j * quote
            print (i*ext + j)
            print (newarray[i*ext + j])
            
    newarray[(len(input_list) - 1) * ext] = float(input_list[len(input_list)-1])
    
    return newarray

result = custom_map(input_list, 10)
print(result)