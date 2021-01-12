In the notebook, the training of the model has been developed using neural network that can detect the existence of a car in an image. The images used were 64 x 64 pixels and the half of the images contain a car as part of it and others shows only empty street. Our neural network consist of 4 hidden layers including the output layer with different neurons [4096, 6, 8, 4, 1]. The input layer "4096 is the size of the image after converting it to numpy array and it's not 12288 becuase it's a grey scale not RGB!", three hidden layers (6:6:5) every hidden layer consist of activation function and an output layer which is one of the binary number (0,1) where "1" represents car found or not "0" otherwise. The final values of the Weight and Bias are stored and used to test against incoming images that are sent via virtual COMM to the STM to decide either the image containing a car or not and display the result on the screen. 


linear_activation_forward(activation = "relu")->linear_forward(X,W1,b1)--->Z1----activation(relu)--->A1

linear_activation_forward(activation = "relu")->linear_forward(A1,W2,b2)--->Z2----activation(relu)--->A2

linear_activation_forward(activation = "relu")->linear_forward(A2,W3,b)--->Z3----activation(relu)--->A3

linear_activation_forward(activation = "sigmoid")->linear_forward(A3,W4,b)--->Z----activation(sigmoid)--->A4
