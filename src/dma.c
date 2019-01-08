/*
 * dma.c
 *
 *  Created on: 08.01.2019
 *      Author: Daniel
 */

/* Includes ------------------------------------------------------------------*/
#include "dma.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void DMA_init()
{

	/* Disable DMA TX Stream */
	DMA1_Stream4->CR &= ~((uint32_t)DMA_SxCR_EN);

	/* Set DMA options for TX Stream */
	DMA1_Stream4->CR &= ~((uint32_t)DMA_SxCR_CHSEL); 			/* Channel0 for SPI DMA TX*/


	/* Enable SPI2 TX DMA */
	SPI2->CR2 |= SPI_CR2_TXDMAEN;

//	/* Enable DMA TX stream */
//	DMA1_Stream4->CR |= DMA_SxCR_EN;
}

/* Deinitializes the DMA */
void DMA_DeInit(void)
{
	;
}

