/*
 * nvic.c
 *
 *  Created on: 04.01.2019
 *      Author: Daniel
 */

/* Includes ------------------------------------------------------------------*/
#include "nvic.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void NVIC_init(void)
{
	/* Disable interrupt */
	__disable_irq();

/* EXTI */
	/* Set the EXTI Interrupt to the lowest priority */
	NVIC_SetPriority(EXTI0_IRQn,0x00);
	/* Clear the pending bit */
	NVIC_ClearPendingIRQ(EXTI0_IRQn);
	/* Enable Interrupt on EXTI Line0 */
	NVIC_EnableIRQ(EXTI0_IRQn);

/* DMA SPI1 TX */
	NVIC_SetPriority(DMA2_Stream3_IRQn, 0x01);
	/* Clear the pending bit */
	NVIC_ClearPendingIRQ(DMA2_Stream3_IRQn);
	/* Enable Interrupt on DMA1 Stream4 */
	NVIC_EnableIRQ(DMA2_Stream3_IRQn);

/* DMA SPI1 RX */
	NVIC_SetPriority(DMA2_Stream2_IRQn, 0x01);
	/* Clear the pending bit */
	NVIC_ClearPendingIRQ(DMA2_Stream2_IRQn);
	/* Enable Interrupt on DMA1 Stream4 */
	NVIC_EnableIRQ(DMA2_Stream2_IRQn);

/* DMA SPI2 TX */
	NVIC_SetPriority(DMA1_Stream4_IRQn, 0x01);
	/* Clear the pending bit */
	NVIC_ClearPendingIRQ(DMA1_Stream4_IRQn);
	/* Enable Interrupt on DMA1 Stream4 */
	NVIC_EnableIRQ(DMA1_Stream4_IRQn);

/* DMA SPI2 RX */
	NVIC_SetPriority(DMA1_Stream3_IRQn, 0x01);
	/* Clear the pending bit */
	NVIC_ClearPendingIRQ(DMA1_Stream3_IRQn);
	/* Enable Interrupt on DMA1 Stream4 */
	NVIC_EnableIRQ(DMA1_Stream3_IRQn);


/* */
/* */

	/* Enable interrupt */
	__enable_irq();
}

void NVIC_DeInit(void)
{
	;
}

