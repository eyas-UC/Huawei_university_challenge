# import h5py
import numpy as np
import os
from PIL import Image
import glob
# import tensorflow as tf
# from tensorflow.python.framework import ops
import math
# import matplotlib.pyplot as plt
import cv2

class test_data():
    def __init__(self):
        F = np.empty((0,64,64))
        L = np.empty((0,64,64))
        R = np.empty((0,64,64))
        M = np.empty((0,64,64))

        Fn = np.empty((0,64,64))
        Ln = np.empty((0,64,64))
        Rn = np.empty((0,64,64))
        Mn = np.empty((0,64,64))


        files =r"C:\huawei\DNN\OwnCollection\vehicles\Far\*.png"
        count = 0
        for f in glob.glob(files):
            if count >= 875:
                img = cv2.imread(f, 0)
                img = img[np.newaxis, :, :]
                F= np.concatenate((F, img), axis=0)
                #print(A.shape) # training data # class car = True (class 1)

            count+= 1

            
        files =r"C:\huawei\DNN\OwnCollection\vehicles\Left\*.png"
        count = 0
        for f in glob.glob(files):
            if count >= 875:
                img = cv2.imread(f, 0)
                img = img[np.newaxis, :, :]
                L= np.concatenate((L, img), axis=0)
                #print(A.shape) # training data # class car = True (class 1)

            count+= 1

        files =r"C:\huawei\DNN\OwnCollection\vehicles\Right\*.png"
        count = 0
        for f in glob.glob(files):
            if count >= 875:
                img = cv2.imread(f, 0)
                img = img[np.newaxis, :, :]
                R= np.concatenate((R, img), axis=0)
                #print(A.shape) # training data # class car = True (class 1)

            count+= 1
            

            
        files =r"C:\huawei\DNN\OwnCollection\vehicles\MiddleClose\*.png"
        count = 0
        for f in glob.glob(files):
            if count >= 400 and count <500:
                img = cv2.imread(f, 0)
                img = img[np.newaxis, :, :]
                M= np.concatenate((M, img), axis=0)
                #print(A.shape) # training data # class car = True (class 1)

            count+= 1
            
                
        files =r"C:\huawei\DNN\OwnCollection\non-vehicles\Far\*.png" 
        count = 0
        for f in glob.glob(files):
            if count >= 875:
                img = cv2.imread(f, 0)
                img = img[np.newaxis, :, :]
                Fn= np.concatenate((Fn, img), axis=0)
                #print(Y.shape) # training data # class car = False (class 0)

            count+= 1


            
        files =r"C:\huawei\DNN\OwnCollection\non-vehicles\Left\*.png" 
        count = 0
        for f in glob.glob(files):
            if count >= 875:
                img = cv2.imread(f, 0)
                img = img[np.newaxis, :, :]
                Ln= np.concatenate((Ln, img), axis=0)
                #print(Y.shape) # training data # class car = False (class 0)

            count+= 1
            
            
        files =r"C:\huawei\DNN\OwnCollection\non-vehicles\Right\*.png" 
        count = 0
        for f in glob.glob(files):
            if count >= 875:
                img = cv2.imread(f, 0)
                img = img[np.newaxis, :, :]
                Rn= np.concatenate((Rn, img), axis=0)
                #print(Y.shape) # training data # class car = False (class 0)

            count+= 1   

        files =r"C:\huawei\DNN\OwnCollection\non-vehicles\MiddleClose\*.png" 
        count = 0
        for f in glob.glob(files):
            if count >= 400 and count <500:
                img = cv2.imread(f, 0)
                img = img[np.newaxis, :, :]
                Mn= np.concatenate((Mn, img), axis=0)
                #print(Y.shape) # training data # class car = False (class 0)

            count+= 1  
        test_x_orig= np.concatenate((F,L,R,M,Fn,Ln,Rn,Mn)) 
        # print(test_x_orig.shape)
        test_x_flatten = test_x_orig.reshape(test_x_orig.shape[0], -1).T
        test_x = test_x_flatten / 255.
        # test_x = test_x_flatten

        # print(test_x.shape)


        self.test = test_x
    def get_mat(self):
        return self.test

# a = test_data()
# print(a.get_mat())
