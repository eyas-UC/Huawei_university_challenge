/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 - 2018 Evidence s.r.l.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License, version 2, for more details.
 * 
 * You should have received a copy of the GNU General Public License,
 * version 2, along with this program; if not, see
 * < www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
 * 
 * This program is distributed to you subject to the following
 * clarifications and special exceptions to the GNU General Public
 * License, version 2.
 * 
 * THIRD PARTIES' MATERIALS
 * 
 * Certain materials included in this library are provided by third
 * parties under licenses other than the GNU General Public License. You
 * may only use, copy, link to, modify and redistribute this library
 * following the terms of license indicated below for third parties'
 * materials.
 * 
 * In case you make modified versions of this library which still include
 * said third parties' materials, you are obligated to grant this special
 * exception.
 * 
 * The complete list of Third party materials allowed with ERIKA
 * Enterprise version 3, together with the terms and conditions of each
 * license, is present in the file THIRDPARTY.TXT in the root of the
 * project.
 * ###*E*### */

/** \file	code.c
 *  \brief	Main application.
 *
 *  This file contains the code of main application for Erika Enterprise.
 *
 *  \author	Paolo Gai
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* ERIKA Enterprise. */
#include "ee.h"
//#include <"math.h">
#include <math.h>
/* HAL */
#include "stm32f429i_discovery_gyroscope.h"
#include "stm32f429i_discovery_lcd.h"
#include <stdlib.h>
#include <string.h>
#include "hal.h"
#include "dnn.h"
#include "var.h"
//#include "stm32f429i_discovery_lcd.h"
#define	HAL_TIMER_MS	     1U

#define	HAL_DELAY_MS	   300U
#define	HAL_SMALLDELAY_MS  100U

extern float w1[6][4096];
extern float w2[8][6];
extern float w3[4][8];
extern float w4[1][4];

extern float b1[6][1];
extern float b2[8][1];
extern float b3[4][1];
extern float b4;
extern float x[4096][1];

//UART_HandleTypeDef huart2;

/* Single byte to store input */
uint8_t byte;

/* A few counters incremented at each event
 * (alarm, button press or task activation...)
 */
volatile uint8_t timer_fired;
volatile uint8_t button_fired;
volatile uint8_t touch_fired;
volatile uint8_t task1_fired;
volatile uint8_t task2_fired;
float xyz[3];



/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(Task3);

//Giving example using fake X


void mat_add(float* A, float* B, float* C, uint8_t row_a, uint8_t column_a, uint8_t column_b) {
	// Check which one should be the column counter
	int columnMatrix = column_a; // Initial select
	if(column_b > column_a) // But if....
		columnMatrix = column_b;
	// Add all values
	int i;
	for (i = 0; i < row_a; i++) {
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

void led_blink(uint8_t theled)
{
  DisableAllInterrupts();
  DemoHAL_LedOn(theled);
  EnableAllInterrupts();

  DemoHAL_Delay(HAL_DELAY_MS);

  DisableAllInterrupts();
  DemoHAL_LedOff(theled);
  EnableAllInterrupts();

  DemoHAL_Delay(HAL_SMALLDELAY_MS);
}



/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  char buffer[100];
  task1_fired++;
  char * i="HI";
  char *ok ;
  ok = "Ok";
  read(ok,i,buffer);
  //DemoHAL_Lcd_Print(buffer);
  /* First half of the christmas tree */
  /*led_blink(DEMO_HAL_LED_0);
  led_blink(DEMO_HAL_LED_1);
  led_blink(DEMO_HAL_LED_2)*/
  
  /* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
#ifdef MYSCHEDULE
  Schedule();
#endif

  /* Second half of the christmas tree */
 /* led_blink(DEMO_HAL_LED_3);
  led_blink(DEMO_HAL_LED_4);
  led_blink(DEMO_HAL_LED_5);
  */
  TerminateTask();
}


/* Task2: Print the counters on the UART */
TASK(Task2)

{/*
	float Z1[6][1];
	float Z2[8][1];
	float Z3[4][1];
	float Z4[1][1]= {{0}};
	float Z44;
	float A4;
	volatile float prediction;
	float output[1] = {0};
	volatile int car;
	char buffer1[40960];
	//char buffer1[161];
	char * buffer;

	DisableAllInterrupts();
	DemoHAL_SerialRead(buffer1);

	//DemoHAL_Lcd_Print((int)s);
	char *unconverted;
	const char delimeter[1] = " ";


	buffer =(buffer1);
	float X[4096];
	char *token;
	int i =0 ;
	//printf("%lu \n",strlen(buffer));

	while( (token = strsep(&buffer," ")) != NULL )
	{
	//printf("%s \n",token);
	X[i] = strtod(token, NULL);
	//printf("%f \n",X[i]);
	i++;
	}


	  // shared resource
		//DisableAllInterrupts();
	  //uint8_t msg[10];
	   // sprintf(msg, "                             ");
	  //char copy[200];
	  //serial_print(msg);
	  //*copy = *msg;
		int m;
		float input [4096][1];
	  //DemoHAL_Lcd_Print("%f",i);
	  for (m = 0; m < 4096; ++m)
	  {
	       input[m][1] = X[m];
	        }
		mat_mul(*w1,*input,*Z1,  6, 4096,  1);
		mat_add(*Z1,*b1,*Z1,  6, 1,  1);//Z1----->  Z1
		relu(*Z1,6);					//Z1 ---->  A1

		mat_mul(*w2,*Z1,*Z2,  8, 6,  1);
		mat_add(*Z2,*b2,*Z2,  8,1 ,  1);//Z2----->  Z2
		relu(*Z2,8);					//Z2 ---->  A2

		mat_mul(*w3,*Z2,*Z3,  4, 8,  1);
		mat_add(*Z3,*b3,*Z3,  4, 1,  1);//Z1----->  Z2
		relu(*Z2,8);					//Z2 ---->  A2

		mat_mul(*w4,*Z3,*Z4,  1, 4,  1);//Z4-----> Z4

		//float b44 = b4[0][0];
		Z44 = Z4[0][0];
		A4 = Z44+b4;
		//mat_add(*Z4,*b4,*Z4, 1 , 1,  1);			//Z4-----> A4

		prediction = sigmoid(A4);//Z2 ---->  A2

		  if (prediction>=0.5)
		  {
			  // there is a car
			  car = 1;
		  }
		  else
		  {
			  car = 0;
		  }

*/
	/*static uint16_t alternate_blink = 0U;


  // BSP_GYRO_Reset();
  //count the number of Task2 activations
  task2_fired++;

  if (alternate_blink) {
	led_blink(DEMO_HAL_LED_6);
	alternate_blink = 0U;
  }
  else {
	led_blink(DEMO_HAL_LED_7);
	alternate_blink = 1U;
  }*/
  

	uint16_t xyz[3];

	while(1)
{

	BSP_GYRO_Init();


	//BSP_GYRO_ReadID();
	BSP_GYRO_ITConfig(interruptconfig);
	//BSP_GYRO_EnableIT(1);

	//BSP_GYRO_Reset();
	BSP_GYRO_GetXYZ(xyz);
	BSP_GYRO_Reset();
	DemoHAL_Lcd_Print(xyz[2]);
}
  EnableAllInterrupts();
  //DemoHAL_Lcd_Print(timer_fired, button_fired+touch_fired, task1_fired, task2_fired);


  TerminateTask();
}


void serial_print(uint8_t const * msg)
{
  //SuspendAllInterrupts();
  //DemoHAL_SerialRead((uint8_t const *)msg, strlen(msg));
  //ResumeAllInterrupts();
}




TASK(Task3)
{/*
	int i;
	float Z1[6][1];
	float Z2[8][1];
	float Z3[4][1];
	float Z4[1][1]= {{0}};
	float Z44;
	float A4;
	volatile float prediction;
	float output[1] = {0};
	volatile int car;
  // shared resource
	DisableAllInterrupts();
  //uint8_t msg[10];
   // sprintf(msg, "                             ");
  //char copy[200];
  //serial_print(msg);
  //*copy = *msg;

  //DemoHAL_Lcd_Print("%f",i);
for(i=0;i<1000;i++){
	mat_mul(*w1,*x,*Z1,  6, 4096,  1);
	mat_add(*Z1,*b1,*Z1,  6, 1,  1);//Z1----->  Z1
	relu(*Z1,6);					//Z1 ---->  A1

	mat_mul(*w2,*Z1,*Z2,  8, 6,  1);
	mat_add(*Z2,*b2,*Z2,  8,1 ,  1);//Z2----->  Z2
	relu(*Z2,8);					//Z2 ---->  A2

	mat_mul(*w3,*Z2,*Z3,  4, 8,  1);
	mat_add(*Z3,*b3,*Z3,  4, 1,  1);//Z1----->  Z2
	relu(*Z2,8);					//Z2 ---->  A2

	mat_mul(*w4,*Z3,*Z4,  1, 4,  1);//Z4-----> Z4

	//float b44 = b4[0][0];
	Z44 = Z4[0][0];
	A4 = Z44+b4;
	//mat_add(*Z4,*b4,*Z4, 1 , 1,  1);			//Z4-----> A4

	prediction = sigmoid(A4);//Z2 ---->  A2
	output[0] = prediction;
	  if (prediction>=0.5)
	  {
		  // there is a car
		  car = 1;
	  }
	  else
	  {
		  car = 0;
	  }
}

	  EnableAllInterrupts();

	  TerminateTask();
	  */
}


/* 
 * This is an ISR Type 2 which is attached to the Timer peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */

volatile int timer_divisor = 0;
ISR2(TimerISR)
{
  timer_divisor++;
  if (timer_divisor=5000) {
	  ActivateTask(Task2);
	  timer_divisor = 0;
    timer_fired++;

  }
  if (timer_divisor==2000) {
      //timer_divisor = 0; // the period is choese in the (slowest task)
      timer_fired++;
      //ActivateTask(Task3);
    }
  DemoHAL_TimerAck();



}

/*
 * Handle button interrupts activates Task2.
 */
ISR2(ButtonsISR)
{
  /* count the number of button presses */
  button_fired++;
  DemoHAL_ButtonInterruptAck(DEMO_HAL_BUTTON_0);
  //ActivateTask(Task2);
}



/*
 * Handle touch screen interrupts activates Task2.
 */
ISR2(TouchISR)
{
  /* count the number of button presses */
  touch_fired++;
  DemoHAL_ButtonInterruptAck(DEMO_HAL_BUTTON_1);
  //ActivateTask(Task2);
}

/* 
 * The StartupHook in this case is used to initialize the Button and timer
 * interrupts
 */



/* **************/






void StartupHook(void)
{
  DemoHAL_TimerInit(HAL_TIMER_MS);
}

void idle_hook ( void ) {
  DemoHAL_MainFunction();// do nothing
}



int main(void)
{

  DemoHAL_Init();
  //DemoHAL_GyroInit();
  DemoHAL_SerialInit();
  DemoHAL_LedInit();

  DemoHAL_ButtonInit();
  DemoHAL_ButtonInterruptEnable(DEMO_HAL_BUTTON_0);
  DemoHAL_ButtonInterruptEnable(DEMO_HAL_BUTTON_1);

  //hal_gyro_init();
 // DemoHAL_GyroInit();


  /*if (BSP_GYRO_Init() != GYRO_OK)


  /* let's start the multiprogramming environment...*/

  StartOS(OSDEFAULTAPPMODE);
  
  return 0;
}
