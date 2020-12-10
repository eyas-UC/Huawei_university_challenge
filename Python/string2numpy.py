import requests
import numpy as np

def string2numpy(data):
	# print(data)
	# print((type(data)))
	string = str(data).decode('utf-8') #start decoding the string
	suint8tring = data.replace('[', '')
	suint8tring = suint8tring.replace(']', '')
	
	my_array = np.squeeze(np.fromstring(suint8tring, sep=',', count=4096, dtype=np.uint8)) #COUNT 6000, I AM NOT SURE ABOUT THAT, CV2 USES STANDARD RESOLUTIONS
	my_array = np.reshape(my_array, (-1, 64))  # becomes 2dims (second dim is here)

	# strr = np.array_str(my_array)
	#print(hashlib.md5(strr.encode('utf-8')).hexdigest())
	#print(my_array.shape)

	return my_array