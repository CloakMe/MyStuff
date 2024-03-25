import wave
import struct
import matplotlib.pyplot as plt
import numpy as np

def custom_map(input_list, ext):
    newarray = np.zeros((len(input_list)-1) * ext + 1, float)
    for i in range(len(input_list)-1):
        quote = float(input_list[i+1] - input_list[i])/ext
        for j in range(ext):
            newarray[i*ext + j] = input_list[i] + j * quote
            #print (i*ext + j)
            #print (newarray[i*ext + j])
            
    newarray[(len(input_list) - 1) * ext] = float(input_list[len(input_list)-1])
    
    return newarray
    
def convert_to_wav(input_file, output_file):
    with open(input_file, 'r') as file:
        raw_data_str = file.read().split()
       
    raw_data = [int(x) for x in raw_data_str]

    # Normalize raw data to be between -1.0 and 1.0
    max_val = float(max(raw_data))
    print(max_val)
    normalized_dataG = [float(val) / max_val for val in raw_data]
    normalized_data = custom_map(normalized_dataG, 100)
    x = np.array(range(0, len(normalized_data)))
    plt.title("Plotting 1-D array")
    plt.xlabel("X axis")
    plt.ylabel("Y axis")
    plt.plot(x, normalized_data, color="red", marker="o", label="Array elements")
    plt.legend()
    plt.show()
    # Open a new WAV file
    with wave.open(output_file, 'w') as wav_file:
        wav_file.setnchannels(1)  # Mono audio
        wav_file.setsampwidth(2)  # 2 bytes per sample
        wav_file.setframerate(19400)  # Sample rate of 44100 Hz
        
        for val in normalized_data:
            wav_file.writeframes(struct.pack('<h', int(val * 32767)))  # Convert floating point value to 16-bit PCM integer
            
if __name__ == '__main__':
    input_file = 'output.txt'
    output_file = 'output.wav'
    
    convert_to_wav(input_file, output_file)