/**
  ******************************************************************************
  * @file    stm32f429i_discovery_io.h
  * @author  polito_sudan
  * @brief   This file contains all the functions prototypes for the
  *          stm32f429i_discovery_io.c driver.
  ******************************************************************************
  ******************************************************************************/
#include <math.h>

#ifdef __cplusplus
 extern "C" {
#endif


void mat_mul(float* A, float* B, float* C, int row_a, int column_a, int column_b);
void mat_add(float* A, float* B, float* C, uint8_t row_a, uint8_t column_a, uint8_t column_b);
void relu(float* A, uint8_t column_b);
float sigmoid(float x);


#if (defined(__cplusplus))
}
#endif

