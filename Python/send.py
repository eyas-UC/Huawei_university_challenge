import time
import serial
from class_convert import *

inst = test_data()
input_ = inst.get_mat()
# convert numpy array to list
lista = input_.tolist()
# print((lista))
s = []
# get 7 floating point from any number stored in the list then add them agaim in a new list
for i in single:
    i = format(i, '.7f')

    # i = float(i).as_integer_ratio()
    s.append(i)
input_ = list(map(lambda s: s.strip("["), s))

string_1 = str(s)
sstring_2 = string_1.replace("'", '')
sstring_2 = sstring_2.replace("[", '')
sstring_2 = sstring_2.replace("]", '')
clean_string = sstring_2.replace(",", '')

# configure the serial connections (the parameters differs on the device you are connecting to)
#460800
#128000
#921600 				transfer time = 0.5 sec
#2000000 (2Mbps)		transfer time = 0.327 secs
time1 = (time.time())
ser = serial.Serial(port='COM7', baudrate=2000000, stopbits=serial.STOPBITS_ONE)
ser.isOpen()
while 1:
    ser.write(str(clean_string).encode())
    # ser.write(str("my nameis").encode())
    print(len(clean_string))
    #print((clean_string))
    # print("1234567890")
    time2 = (time.time())
    print(f'the time for {len(clean_string)} bytes is {time2-time1} seconds')
    break
    
