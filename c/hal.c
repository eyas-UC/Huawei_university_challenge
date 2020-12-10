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

/** \file	hal.c
 *  \brief	Hardware Abstraction Layer Sources.
 *
 *  This file contains the sources of the HAL for Erika Enterprise.
 *
 *  \author	Giuseppe Serano
 *  \date	2018
 */

/* Header */
#include "hal.h"

#ifdef	OS_EE_LIB_STM32_CUBE_F4
/* STM32F4 DISCOVERY BSP. */
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"
#include "stm32f429i_discovery_gyroscope.h"
#include "stm32f4xx_hal_uart.h"
#include "../Components/l3gd20/l3gd20.c"
#include "ee3logo.h"
#include "evilogo.h"
#include <stdio.h>
#include <string.h>
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */

#ifdef	OS_EE_LIB_STM32_CUBE_F4
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */

int error = 5;
static FUNC(void, APPL_CODE) SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
       clocked below the maximum system frequency, to update the voltage scaling value
       regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	/* Activate the Over-Drive mode */
	HAL_PWREx_EnableOverDrive();

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
       clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}	/* SystemClock_Config() */
//GYRO_DrvTypeDef L3gd20Drv;
//float xyz[3];


FUNC(void,APPL_CODE) hal_gyro_init(void)
{


}

static FUNC(void, APPL_CODE) Lcd_Config(void)
{
	/*##-1- Initialize the LCD #################################################*/
	/* Initialize the LCD */
	BSP_LCD_Init();

	/* Initialize the LCD Layers */
	BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER);

	/* Set LCD Foreground Layer  */
	BSP_LCD_SelectLayer(1);

	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

	/* Clear the LCD */
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	/* Set the LCD Text Color */
	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);

	/* Display LCD messages */
	BSP_LCD_DisplayStringAt(0, 10, (uint8_t*)"STM32F429I", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 35, (uint8_t*)"Discovery", CENTER_MODE);

	/* Draw Bitmap */
	BSP_LCD_DrawBitmap(20, 65, (uint8_t *)ee3logo);
	BSP_LCD_DrawBitmap(0, 130, (uint8_t *)evilogo);

	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 40, (uint8_t*)"Copyright (c) 2020", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 20, (uint8_t*)"Evidence Srl", CENTER_MODE);

	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillRect(0, BSP_LCD_GetYSize()/2 + 15, BSP_LCD_GetXSize(), 60);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_RED);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 25, (uint8_t*)"TASK Demo:", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 40, (uint8_t*)"Press USER Button to Act Task2", CENTER_MODE);
}	/* Lcd_Config() */
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */

FUNC(void, APPL_CODE) DemoHAL_Init( void )
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	HAL_Init();

	SystemClock_Config();
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */

#if (defined(OSEE_CORTEX_M_TIM3_ISR) && defined(OSEE_SYSTEM_TIMER))
	DemoHAL_TimerInit(1U);
#endif
}

#if (defined(OSEE_CORTEX_M_TIM3_ISR) && defined(OSEE_SYSTEM_TIMER))
ISR1(HALTickISR)
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	HAL_IncTick();
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
	DemoHAL_TimerAck();
}

FUNC(void, APPL_CODE) DemoHAL_Delay(
	VAR(MemSize, AUTOMATIC)	interval
)
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	HAL_Delay(interval);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
}
#else
#if (defined(OSEE_SYSTEM_TIMER) && defined(OSEE_SYSTEM_TIMER_DEVICE) && (OSEE_SYSTEM_TIMER_DEVICE == OSEE_CORTEX_M_SYSTICK))
FUNC(void, APPL_CODE) DemoHAL_Delay(
	VAR(MemSize, AUTOMATIC)	interval
)
{
	TickType	start, tmp, elapsed;

	GetCounterValue(OSEE_SYSTEM_TIMER, &start);

	do {
		tmp = start;
		GetElapsedValue(OSEE_SYSTEM_TIMER, &tmp, &elapsed);
	} while (elapsed < interval);
}
#else
#if	(								\
		!(							\
			defined(OSEE_CORTEX_M_SYSTICK_ISR_TID) &&	\
			(OSEE_CORTEX_M_SYSTICK_ISR_CAT == 2)		\
		) && !(							\
			defined(OSEE_CORTEX_M_SYSTICK_ISR) &&		\
			(OSEE_CORTEX_M_SYSTICK_ISR_CAT == 1)		\
		)							\
)
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
FUNC(void, APPL_CODE) SysTick_Handler(void)
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	HAL_IncTick();
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
}
#endif	/* OSEE_CORTEX_M_SYSTICK_ISR */

FUNC(void, APPL_CODE) DemoHAL_Delay(
	VAR(MemSize, AUTOMATIC)	interval
)
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	HAL_Delay(interval);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
}
#endif
#endif

FUNC(void, APPL_CODE) DemoHAL_MainFunction( void ) {int x = 5;}

/* Leds HAL */
#define	HAL_LCD_LED1_STR	(uint8_t *)"1\r\n"
#define	HAL_LCD_LED2_STR	(uint8_t *)"2\r\n"
#define	HAL_LCD_LED3_STR	(uint8_t *)"3\r\n"
#define	HAL_LCD_LED4_STR	(uint8_t *)"4\r\n"
#define	HAL_LCD_LED5_STR	(uint8_t *)"5\r\n"
#define	HAL_LCD_LED6_STR	(uint8_t *)"6\r\n"
#define	HAL_LCD_LED7_STR	(uint8_t *)"7\r\n"
#define	HAL_LCD_LED8_STR	(uint8_t *)"8\r\n"
#define HAL_LCD_LED_STR_SZ	3U

static CONSTP2VAR(uint8_t, OS_APPL_DATA, OS_APPL_DATA) halLedArray[DEMO_HAL_BUTTON_NUM] = {
	HAL_LCD_LED1_STR, HAL_LCD_LED2_STR, HAL_LCD_LED3_STR, HAL_LCD_LED4_STR,
	HAL_LCD_LED5_STR, HAL_LCD_LED6_STR, HAL_LCD_LED7_STR, HAL_LCD_LED8_STR
};

#ifdef	OS_EE_LIB_STM32_CUBE_F4
#define	BSP_LCD_LED1_STR	(uint8_t *)"1"
#define	BSP_LCD_LED2_STR	(uint8_t *)"2"
#define	BSP_LCD_LED3_STR	(uint8_t *)"3"
#define	BSP_LCD_LED4_STR	(uint8_t *)"4"
#define	BSP_LCD_LED5_STR	(uint8_t *)"5"
#define	BSP_LCD_LED6_STR	(uint8_t *)"6"
#define	BSP_LCD_LED7_STR	(uint8_t *)"7"
#define	BSP_LCD_LED8_STR	(uint8_t *)"8"

#define	LED_SIZE	(BSP_LCD_GetXSize() >> 3)
#define	LED_Y		BSP_LCD_GetYSize()/2 + 82

static CONSTP2VAR(uint8_t, OS_APPL_DATA, OS_APPL_DATA) bspLcdLedArray[DEMO_HAL_BUTTON_NUM] = {
	BSP_LCD_LED1_STR, BSP_LCD_LED2_STR, BSP_LCD_LED3_STR, BSP_LCD_LED4_STR,
	BSP_LCD_LED5_STR, BSP_LCD_LED6_STR, BSP_LCD_LED7_STR, BSP_LCD_LED8_STR
};

static VAR(int, OS_APPL_DATA) ledStatus[DEMO_HAL_BUTTON_NUM];

static FUNC(void, APPL_CODE) BSP_LCD_LedOn(
	VAR(DemoHAL_Led, AUTOMATIC)				led
)
{
	ledStatus[led] = 1U;
	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_FillRect(2 + led * LED_SIZE, BSP_LCD_GetYSize()/2 + 77, LED_SIZE - 4, 31);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
	BSP_LCD_DisplayStringAt(7 + led * LED_SIZE, BSP_LCD_GetYSize()/2 + 82, bspLcdLedArray[led], LEFT_MODE);
}

static FUNC(void, APPL_CODE) BSP_LCD_LedOff(
	VAR(DemoHAL_Led, AUTOMATIC)				led
)
{
	ledStatus[led] = 0U;
	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(2 + led * LED_SIZE, BSP_LCD_GetYSize()/2 + 77, LED_SIZE - 4, 31);
	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(7 + led * LED_SIZE, BSP_LCD_GetYSize()/2 + 82, bspLcdLedArray[led], LEFT_MODE);
}

FUNC(void, APPL_CODE) BSP_LCD_LedToggle(
	VAR(DemoHAL_Led, AUTOMATIC)				led
)
{
	if  (ledStatus[led]) {
		BSP_LCD_LedOff(led);
	} else {
		BSP_LCD_LedOn(led);
	}
}
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */

FUNC(void, APPL_CODE) DemoHAL_LedInit( void )
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	uint8_t i;

	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);

	Lcd_Config();

	/* Draw Graphical LEDs */
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillRect(0, BSP_LCD_GetYSize()/2 + 75, BSP_LCD_GetXSize(), 35);

	for (i = 0; i < 8; ++i) {
		BSP_LCD_LedOff(i);
	}

	DemoHAL_SerialInit();
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
}

FUNC(void, APPL_CODE) DemoHAL_LedOn(
	VAR(DemoHAL_Led, AUTOMATIC)				led
)
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	BSP_LCD_LedOn(led);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */

	//DemoHAL_SerialWrite(halLedArray[led], HAL_LCD_LED_STR_SZ);

	switch (led) {
	case DEMO_HAL_LED_0:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_On(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_1:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_On(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_2:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_On(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_3:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_On(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_4:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_On(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_5:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_On(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_6:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_On(LED4);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_7:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_On(LED4);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	default:
		break;
	}
}

FUNC(void, APPL_CODE) DemoHAL_LedOff(
	VAR(DemoHAL_Led, AUTOMATIC)	led
)
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	BSP_LCD_LedOff(led);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */

	switch (led) {
	case DEMO_HAL_LED_0:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Off(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_1:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Off(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_2:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Off(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_3:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Off(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_4:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Off(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_5:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Off(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_6:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Off(LED4);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_7:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Off(LED4);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	default:
		break;
	}
}

FUNC(void, APPL_CODE) DemoHAL_LedToggle(
	VAR(DemoHAL_Led, AUTOMATIC)				led
)
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	BSP_LCD_LedToggle(led);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */

	switch (led) {
	case DEMO_HAL_LED_0:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Toggle(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_1:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Toggle(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_2:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Toggle(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_3:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Toggle(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_4:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Toggle(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_5:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Toggle(LED3);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_6:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Toggle(LED4);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_LED_7:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_LED_Toggle(LED4);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	default:
		break;
	}
}

/* Buttons HAL */
FUNC(void, APPL_CODE) DemoHAL_ButtonInit( void )
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	/* Configure Touch Screen */
	uint8_t status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
	if (status != TS_OK)
	{
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 95, (uint8_t*)"ERROR", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()- 80, (uint8_t*)"Touchscreen cannot be initialized", CENTER_MODE);
		DemoHAL_LedOn(DEMO_HAL_LED_1);
		for(;;);
	}
	/* Configure USER Button */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
}

FUNC(OsEE_bool, APPL_CODE) DemoHAL_ButtonRead(
	VAR(DemoHAL_Button, AUTOMATIC)	button
) {
	VAR(OsEE_bool, AUTOMATIC)		value = 0U;
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	VAR(TS_StateTypeDef, AUTOMATIC)	tState = { 0 };
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */


	switch (button) {
	case DEMO_HAL_BUTTON_0:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		value = (BSP_PB_GetState(BUTTON_KEY) == RESET);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_BUTTON_1:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_TS_GetState(&tState);
		value = tState.TouchDetected;
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_BUTTON_2:
	case DEMO_HAL_BUTTON_3:
	case DEMO_HAL_BUTTON_4:
	case DEMO_HAL_BUTTON_5:
	case DEMO_HAL_BUTTON_6:
	case DEMO_HAL_BUTTON_7:
	default:
		break;
	}
	return !value;
}

FUNC(void, APPL_CODE) DemoHAL_ButtonInterruptEnable(
	VAR(DemoHAL_Button, AUTOMATIC)	button
) {
	switch (button) {
	case DEMO_HAL_BUTTON_0:
#ifdef	OS_EE_LIB_STM32_CUBE_F4

#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_BUTTON_1:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		BSP_TS_ITConfig();
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_BUTTON_2:
	case DEMO_HAL_BUTTON_3:
	case DEMO_HAL_BUTTON_4:
	case DEMO_HAL_BUTTON_5:
	case DEMO_HAL_BUTTON_6:
	case DEMO_HAL_BUTTON_7:
	default:
		break;
	}
}

FUNC(void, APPL_CODE) DemoHAL_ButtonInterruptDisable(
	VAR(DemoHAL_Button, AUTOMATIC)	button
) {
	switch (button) {
	case DEMO_HAL_BUTTON_0:
#ifdef	OS_EE_LIB_STM32_CUBE_F4

#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_BUTTON_1:
#ifdef	OS_EE_LIB_STM32_CUBE_F4

#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_BUTTON_2:
	case DEMO_HAL_BUTTON_3:
	case DEMO_HAL_BUTTON_4:
	case DEMO_HAL_BUTTON_5:
	case DEMO_HAL_BUTTON_6:
	case DEMO_HAL_BUTTON_7:
	default:
		break;
	}
}

FUNC(void, APPL_CODE) DemoHAL_ButtonInterruptAck(
	VAR(DemoHAL_Button, AUTOMATIC)	button
) {
	switch (button) {
	case DEMO_HAL_BUTTON_0:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_BUTTON_1:
#ifdef	OS_EE_LIB_STM32_CUBE_F4
		HAL_GPIO_EXTI_IRQHandler(STMPE811_INT_PIN);
		BSP_TS_ITClear();
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
		break;
	case DEMO_HAL_BUTTON_2:
	case DEMO_HAL_BUTTON_3:
	case DEMO_HAL_BUTTON_4:
	case DEMO_HAL_BUTTON_5:
	case DEMO_HAL_BUTTON_6:
	case DEMO_HAL_BUTTON_7:
	default:
		break;
	}
}



/* Timer HAL */
#ifdef	OS_EE_LIB_STM32_CUBE_F4
/* User can use this section to tailor TIMx instance used and associated
   resources */
/* Definition for TIMx clock resources */
#define TIMx                           TIM3
#define TIMx_CLK_ENABLE                __HAL_RCC_TIM3_CLK_ENABLE

/* Definition for TIMx's NVIC */
#define TIMx_IRQn                      TIM3_IRQn
#define TIMx_IRQHandler                TIM3_IRQHandler

static VAR(TIM_HandleTypeDef, OS_APPL_DATA)	TimHandle;

#if (defined(OSEE_CORTEX_M_TIM3_ISR) && defined(OSEE_SYSTEM_TIMER))
FUNC(void, APPL_CODE) HAL_TIM_Base_MspInit(
	P2VAR(TIM_HandleTypeDef, AUTOMATIC, AUTOMATIC)	htim
)
{
  /*##-2- Configure the NVIC for TIMx ########################################*/
  /* Set the TIMx priority */
  HAL_NVIC_SetPriority(TIMx_IRQn, 0, OSEE_CORTEX_M_TIM3_ISR_PRI);

  /* Enable the TIMx global Interrupt */
  HAL_NVIC_EnableIRQ(TIMx_IRQn);
}
#endif
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */

FUNC(void, APPL_CODE) DemoHAL_TimerInit(
	VAR(MemSize, AUTOMATIC)					period
) {
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	VAR(uint16_t, AUTOMATIC)				uwPrescalerValue = 0;

	/*##-0- Enable peripherals and GPIO Clocks #################################*/
	/* TIMx Peripheral clock enable */
	TIMx_CLK_ENABLE();

	/*##-1- Configure the TIM peripheral #######################################*/
	/* -----------------------------------------------------------------------
	   In this example TIM3 input clock (TIM3CLK) is set to 2 * APB1 clock (PCLK1),
	   since APB1 prescaler is different from 1.
	     TIM3CLK = 2 * PCLK1
	     PCLK1 = HCLK / 4
	     => TIM3CLK = HCLK / 2 = SystemCoreClock /2
	   To get TIM3 counter clock at 10 KHz, the Prescaler is computed as following:
	   Prescaler = (TIM3CLK / TIM3 counter clock) - 1
	   Prescaler = ((SystemCoreClock /2) /10 KHz) - 1

	   Note:
	     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
	     Each time the core clock (HCLK) changes, user had to update SystemCoreClock
	     variable value. Otherwise, any configuration based on this variable will be incorrect.
	     This variable is updated in three ways:
	      1) by calling CMSIS function SystemCoreClockUpdate()
	      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
	      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
	  ----------------------------------------------------------------------- */

	/* Compute the prescaler value to have TIM3 counter clock equal to 10 KHz */
	uwPrescalerValue = (uint32_t) ((SystemCoreClock /2) / (period * 1000000)) - 1;

	/* Set TIMx instance */
	TimHandle.Instance = TIMx;

	/* Initialize TIM3 peripheral as follows:
	   + Period = 10000 - 1
	   + Prescaler = ((SystemCoreClock/2)/10000) - 1
	   + ClockDivision = 0
	   + Counter direction = Up
	 */
	TimHandle.Init.Period = (period * 1000) - 1;
	TimHandle.Init.Prescaler = uwPrescalerValue;
	TimHandle.Init.ClockDivision = 0;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if(HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
	{
		/* Initialization Error */
		DemoHAL_LedOn(DEMO_HAL_LED_1);
		for(;;);
	}

	/*##-2- Start the TIM Base generation in interrupt mode ####################*/
	/* Start Channel1 */
	if(HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
	{
		/* Starting Error */
		DemoHAL_LedOn(DEMO_HAL_LED_1);
		for(;;);
	}
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
}	/* DemoHAL_TimerInit() */

FUNC(void, APPL_CODE) DemoHAL_TimerDelay(
	VAR(MemSize, AUTOMATIC)	interval
) { (void)interval; }

FUNC(void, APPL_CODE) DemoHAL_TimerAck( void )
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	HAL_TIM_IRQHandler(&TimHandle);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
}

/* Serial HAL */
#ifdef	OS_EE_LIB_STM32_CUBE_F4
/* Definition for USARTx clock resources */
#define USARTx                           USART1
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF7_USART1
#define USARTx_RX_PIN                    GPIO_PIN_10
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_AF                     GPIO_AF7_USART1

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART1_IRQn
#define USARTx_IRQHandler                USART1_IRQHandler

static VAR(UART_HandleTypeDef, OS_APPL_DATA)	UartHandle;
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
/*
ISR1(SerialISR)
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	HAL_UART_IRQHandler(&UartHandle);
#endif	// OS_EE_LIB_STM32_CUBE_F4
}
*/
ISR2(UART_ISR)
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	HAL_UART_IRQHandler(&UartHandle);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */

}
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef &UartHandle)
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
  if (UartHandle->Instance == USART1)
  {
    //Receive one byte in interrupt mode
    //HAL_UART_Receive_IT(&huart2, &byte, 1);
	  DemoHAL_Lcd_Print("Gyroscope is working");

  }
#endif
}*/



FUNC(void, APPL_CODE) DemoHAL_SerialInit( void )
{
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	GPIO_InitTypeDef  GPIO_InitStruct;

	/*##-0- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	USARTx_TX_GPIO_CLK_ENABLE();
	USARTx_RX_GPIO_CLK_ENABLE();
	/* Enable USART1 clock */
	USARTx_CLK_ENABLE();

	/*##-1- Configure peripheral GPIO ##########################################*/
	/* UART TX GPIO pin configuration  */
	GPIO_InitStruct.Pin       = USARTx_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = USARTx_TX_AF;

	HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

	/* UART RX GPIO pin configuration  */
	GPIO_InitStruct.Pin = USARTx_RX_PIN;
	GPIO_InitStruct.Alternate = USARTx_RX_AF;

	HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);

	/*##-2- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART1 configured as follow:
	   - Word Length = 8 Bits
	   - Stop Bit = One Stop bit
	   - Parity = None
	   - BaudRate = 9600 baud
	   - Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance          = USARTx;

	UartHandle.Init.BaudRate     = 128000;
	UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits     = UART_STOPBITS_1;
	UartHandle.Init.Parity       = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode         = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if(HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		DemoHAL_LedOn(DEMO_HAL_LED_1);
		for(;;);
	}
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
}
/*
FUNC(void, APPL_CODE) DemoHAL_SerialWrite(
	P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA)		buffer,
	VAR(MemSize, AUTOMATIC)					length
) {
#ifdef	OS_EE_LIB_STM32_CUBE_F4
	HAL_UART_Transmit_IT(&UartHandle, (uint8_t *)buffer, length);
#endif	// OS_EE_LIB_STM32_CUBE_F4
}
*/

FUNC(void, APPL_CODE) DemoHAL_SerialRead(char * buffer)
{

volatile char * retcode ="nothing";
volatile HAL_StatusTypeDef status;

//#ifdef	OS_EE_LIB_STM32_CUBE_F4
status = HAL_UART_Receive(&UartHandle, (uint8_t *)buffer, 40960, 5000);

//#endif
}
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
error = 0;

}*/
/*
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
	error = 1;
}*/




FUNC(void, APPL_CODE) read(char * len,char* ret_code,char * buffer) {
    volatile HAL_StatusTypeDef status;
    volatile char * retcode =ret_code;
    //DemoHAL_SerialRead((uint8_t const *)msg, strlen(msg));

    int length= strlen(buffer);

    //P2CONST(uint8_t, AUTOMATIC, OS_APPL_DATA)		buffer=len ;

    //char buffer[10];
    if (len == "Ok")

    {
		#ifdef	OS_EE_LIB_STM32_CUBE_F4
    	//__HAL_UART_CLEAR_FLAG(&UartHandle, UART_FLAG_FE);
        status = HAL_UART_Receive(&UartHandle, (uint8_t *)buffer, 100, 5000);
        #endif	/* OS_EE_LIB_STM32_CUBE_F4 */
        if (status == HAL_OK)
                	retcode = len;

                else
                   retcode = "Error";
    }
}


/*FUNC(void, APPL_CODE) DemoHAL_Lcd_Print(char * msg) {
#ifdef OS_EE_LIB_STM32_CUBE_F4
	//static char msg[] =   "     xxxxx \0";
	//sprintf(msg, "     %d  \0", tmr);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_RED);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 55, msg, CENTER_MODE);
#endif	// OS_EE_LIB_STM32_CUBE_F4
}*/

FUNC(void, APPL_CODE) DemoHAL_Lcd_Print(int tmr) {
#ifdef OS_EE_LIB_STM32_CUBE_F4
	char msg[10];
	sprintf(msg, "TMR %d", tmr);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_RED);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2 + 55,(uint8_t*) msg, CENTER_MODE);
#endif	/* OS_EE_LIB_STM32_CUBE_F4 */
}
/*
FUNC(void, APPL_CODE) DemoHAL_GyroInit(void){
GPIO_InitTypeDef GPIO_InitStructure;
// Enable CS GPIO clock and  Configure GPIO PIN for Gyroscope Chip select
 GYRO_CS_GPIO_CLK_ENABLE();
 GPIO_InitStructure.Pin = GYRO_CS_PIN;
 GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
 GPIO_InitStructure.Pull  = GPIO_NOPULL;
 GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
 HAL_GPIO_Init(GYRO_CS_GPIO_PORT, &GPIO_InitStructure);
 //HAL_NVIC_SetPriority(GYRO_INT2_EXTI_IRQn, 2, 0);
 //HAL_NVIC_EnableIRQ(GYRO_INT2_EXTI_IRQn);
 // Deselect: Chip Select high
 GYRO_CS_HIGH();

 // Enable INT1, INT2 GPIO clock and Configure GPIO PINs to detect Interrupts
 GYRO_INT_GPIO_CLK_ENABLE();
 GPIO_InitStructure.Pin = GYRO_INT1_PIN | GYRO_INT2_PIN;
 GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
 GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
 GPIO_InitStructure.Pull= GPIO_NOPULL;
 HAL_GPIO_Init(GYRO_INT_GPIO_PORT, &GPIO_InitStructure);

 //SPIx_Init();

}*/
