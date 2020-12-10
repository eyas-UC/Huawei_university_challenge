from PIL import Image
import numpy as np
import requests
import string2numpy as s2n
from class_send import *

#
# text = requests.get('http://localhost:8088').text
# # print(text)
# suint8tring = text.replace('[', '')
# suint8tring = suint8tring.replace(']', '')
#
#
#
# my_array = np.squeeze(np.fromstring(suint8tring, sep=',', count=4096, dtype=np.uint8)) #COUNT 6000, I AM NOT SURE ABOUT THAT, CV2 USES STANDARD RESOLUTIONS
# my_array = np.reshape(my_array, (-1, 64))  # becomes 2dims (second dim is here)
#
#

a = test_data()
mat = a.get_mat()
mat = mat[:, 0]
print(mat.shape)
new_mat = np.reshape(mat, (-1, 64))  # becomes 2dims (second dim is here)
print(new_mat)
# print(mat.shape)
# data[0:256, 0:256] = [255, 0, 0] # red patch in upper left
# img = Image.fromarray(mat, 'RGB')
img = Image.fromarray(new_mat)
img.save('my.png')
img.show()

# 7abebna
