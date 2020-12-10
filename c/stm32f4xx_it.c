/**
  ******************************************************************************
  * @file    BSP/Src/stm32f4xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
#include "stdio.h"
#include <string.h>
#include "stm32f429i_discovery.h"


/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef EE_M24LR64
extern I2C_HandleTypeDef I2cHandle;
#endif /* EE_M24LR64 */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  //while (1)
  //{
  //}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
	//sprintf("TMR %d", 6);
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Enable CS GPIO clock and  Configure GPIO PIN for Gyroscope Chip select */
	 GYRO_CS_GPIO_CLK_ENABLE();
	 GPIO_InitStructure.Pin = GYRO_CS_PIN;
	 GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	 GPIO_InitStructure.Pull  = GPIO_NOPULL;
	 GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	 HAL_GPIO_Init(GYRO_CS_GPIO_PORT, &GPIO_InitStructure);
	 //HAL_NVIC_SetPriority(GYRO_INT2_EXTI_IRQn, 2, 0);
	 //HAL_NVIC_EnableIRQ(GYRO_INT2_EXTI_IRQn);
	 /* Deselect: Chip Select high */
	 GYRO_CS_HIGH();

	 /* Enable INT1, INT2 GPIO clock and Configure GPIO PINs to detect Interrupts */
	 GYRO_INT_GPIO_CLK_ENABLE();
	 GPIO_InitStructure.Pin = GYRO_INT1_PIN | GYRO_INT2_PIN;
	 GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	 GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	 GPIO_InitStructure.Pull= GPIO_NOPULL;
	 HAL_GPIO_Init(GYRO_INT_GPIO_PORT, &GPIO_InitStructure);

}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */

#ifdef EE_M24LR64
/**
  * @brief  This function handles I2C_EV interrupt request.
  * @param  None
  * @retval None
  */
void I2C3_EV_IRQHandler(void)
{
  HAL_I2C_EV_IRQHandler(&I2cHandle);
}

/**
  * @brief  This function handles I2C_ER interrupt request.
  * @param  None
  * @retval None
  */
void I2C3_ER_IRQHandler(void)
{
  HAL_I2C_ER_IRQHandler(&I2cHandle);
}

/**
  * @brief  This function handles sEE DMA TX interrupt request.
  * @param  None
  * @retval None
  */
void EEPROM_I2C_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(I2cHandle.hdmatx);
}

/**
  * @brief  This function handles sEE DMA RX interrupt request.
  * @param  None
  * @retval None
  */
void EEPROM_I2C_DMA_RX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(I2cHandle.hdmarx);
}
#endif /* EE_M24LR64 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
