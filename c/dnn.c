#include <math.h>
#include "dnn.h"

void mat_add(float* A, float* B, float* C, uint8_t row_a, uint8_t column_a, uint8_t column_b) {
	// Check which one should be the column counter
	int columnMatrix = column_a; // Initial select
	if(column_b > column_a) // But if....
		columnMatrix = column_b;
	// Add all values
	for (int i = 0; i < row_a; i++) {
		for (int j = 0; j < columnMatrix; j++) {

			if (column_b == 1 && column_a > 1)
				*(C++) = *(A++) + *(B + i); // Matrix + Vector
			else if (column_b > 1 && column_a == 1)
				*(C++) = *(A + i) + *(B++); // Vector + Matrix
			else
				*(C++) = *(A++) + *(B++); // Matrix + Matrix or Vector + Vector
		}
	}
}

void mat_mul(float* A, float* B, float* C, int row_a, int column_a, int column_b) {


	float* data_a = A;
	float* data_b = B;
	//float* C = C; // No need
{
		// Do regular mutiplication. In MATLAB it is A*A
		// Let's take our a matrix
		for (int i = 0; i < row_a; i++) {

			// Then we go through every column of b
			for (int j = 0; j < column_b; j++) {
				data_a = &A[i * column_a];
				data_b = &B[j];

				*C = 0; // Reset
				// And we multiply rows from a with columns of b
				for (int k = 0; k < column_a; k++) {
					*C += *data_a * *data_b;
					data_a++;
					data_b += column_b;
				}
				C++;
			}
		}
	}
}

void relu(float* A, uint8_t vector_lenght)
{
	uint8_t i;
	//for each element if negative change to zero
	for (i = 0 ; i< vector_lenght ; i++)
	{
		if(A[i]<0)
		{
			A[i]=0;
		}
	}
}



float sigmoid(float x) {
 return ( 1 / (1 + exp(-x))  );
}
