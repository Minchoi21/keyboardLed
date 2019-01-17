/*
 * spi_dma.c
 *
 *  Created on: 08.01.2019
 *      Author: oem
 */

/* Includes ------------------------------------------------------------------*/
#include "spi_dma.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

uint8_t SPI_DMA_transmit(SPI_TypeDef* SPIx, uint8_t* TX_Buffer, uint16_t count) {

	while(SPI_IS_BUSY(SPIx)) {}

	/* Check if DMA available */
	if (
		DMA1_Stream4->NDTR ||
		(TX_Buffer == NULL)||
		SPI_IS_BUSY(SPIx)
	) {
		return 0;
	}

	/* Init TX stream */
	DMA_init();

	/* Set memory size */


	/* Set DMA peripheral address and count */
	DMA1_Stream4->PAR = (uint32_t) &SPIx->DR;
	DMA1_Stream4->NDTR = count;

	/* Configure TX DMA direction */
	DMA1_Stream4->CR |= DMA_SxCR_DIR_0; 		/* Direction Memory to Peripheral */

	/* Set DMA memory address and memory increment mode as a enabled*/
	DMA1_Stream4->M0AR = (uint32_t) TX_Buffer;
	DMA1_Stream4->CR |= DMA_SxCR_MINC;

	/* Deinit first TX stream (clear flags) */
	DMA1->HIFCR |= DMA_HIFCR_CFEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CHTIF4| DMA_HIFCR_CTCIF4;

	/* Enable TX stream */
	DMA1_Stream4->CR |= DMA_SxCR_EN;


	/* Return OK */
	return 1;
}
