/*
 * spi_dma.c
 *
 *  Created on: 08.01.2019
 *      Author: oem
 */

/* Includes ------------------------------------------------------------------*/
#include "spi_dma.h"

/* Private typedef -----------------------------------------------------------*/
/* Private structure */
typedef struct {
	uint32_t TX_Channel;
	DMA_Stream_TypeDef* TX_Stream;
	uint32_t RX_Channel;
	DMA_Stream_TypeDef* RX_Stream;
	uint32_t Dummy32;
	uint16_t Dummy16;
} st_SPI_DMA_settings_t;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void SPI_DMA_init(SPI_TypeDef* SPIx) {
	/* Init DMA TX mode */
	/* Assuming SPI is already initialized and clock is enabled */

	/* Get SPIx settings */
	st_SPI_DMA_settings_t* st_settings = SPI_DMA_getSettings(SPIx);

	/* Enable DMA clock */
	if (Settings->TX_Stream >= DMA2_Stream0) {
		/* Enable DMA2 clock */
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	} else {
		/* Enable DMA1 clock */
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	}

	/* Enable DMA clock */
	if (Settings->RX_Stream >= DMA2_Stream0) {
		/* Enable DMA2 clock */
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	} else {
		/* Enable DMA1 clock */
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	}

	/* Set DMA options for TX stream */
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Low;
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
}

uint8_t SPI_DMA_transmit(SPI_TypeDef* SPIx, uint8_t* TX_Buffer, uint16_t count) {

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
