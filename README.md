# Huawei_embedded_dnn

**to predict we need parameters (W and b) in addition to the inputs.
in our case w and b are known matrices and can be entered or hard stored in the stm32

in our model layers_dims = [4096, 6,8, 4, 1]
int Relu( int x )// x will be an array
{
// add for loop to cover all the elements of the matrix x
	if (x>0)
	{
		return x
	}
	else
	{
		return 0
	}
}

layer 1 6 neurons  Activation type(Relu)
layer 2 8 neurons type(Relu)
layer 3 4 neorons type(Relu)
layer 4 1 neuron  type(sigmoid)

linear_activation_forward(activation = "relu")->linear_forward(X,W1,b1)--->Z1----activation(relu)--->A1
linear_activation_forward(activation = "relu")->linear_forward(A1,W2,b2)--->Z2----activation(relu)--->A2
linear_activation_forward(activation = "relu")->linear_forward(A2,W3,b)--->Z3----activation(relu)--->A3
linear_activation_forward(activation = "sigmoid")->linear_forward(A3,W4,b)--->Z----activation(sigmoid)--->A4

X  = image_matrix_input----- dim---->(4096, xxx)
W1  = (6, 4096)
linear_forward()
{W1*X+b}
W1*X-----dim-----> (6, 4096)*(4096, xxx)
xxx ---->training samples

in the case of one pic at a time xxx =1
(6, 4096)*(4096, 1)----> (6,1)------>dim(Z1)


A3 = predicted_output

Z1 = mat_add(mat_mul(X,W) ,b)
A1 = relu(Z1) // i think we should do a for loop to relu the whole matrix of Z1


implemntation

- receive X 
mult W1,X 
add b

get Z1
get A1













