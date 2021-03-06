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
	DMA_Stream_TypeDef* TX_Stream;
	uint32_t TX_Channel;
	DMA_Stream_TypeDef* RX_Stream;
	uint32_t RX_Channel;
} st_SPI_DMA_settings_t;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* SPIx TX and RX default settings */
#ifdef SPI1
static st_SPI_DMA_settings_t st_spi1_dma = {DMA2_Stream3, DMA_Channel_3, DMA2_Stream2, DMA_Channel_3};
#endif
#ifdef SPI2
static st_SPI_DMA_settings_t st_spi2_dma = {DMA1_Stream4, DMA_Channel_0, DMA1_Stream3, DMA_Channel_0};
#endif
#ifdef SPI3
static st_SPI_DMA_settings_t st_spi3_dma = {DMA1_Stream5, DMA_Channel_0, DMA1_Stream0, DMA_Channel_0};
#endif

/* Private function prototypes -----------------------------------------------*/
static st_SPI_DMA_settings_t* SPI_DMA_getSettings(SPI_TypeDef* SPIx);

/* Functions ---------------------------------------------------------*/

void SPI_DMA_init(SPI_TypeDef* SPIx)
{
	/* Assuming SPI is already initialized and clock is enabled */

	en_DMA_MemoryDataSize_t mem_size;
	en_DMA_PeripheralDataSize_t periph_size;
	/* Checking which data frame size is set for specified SPIx */
	en_SPI_dataSize_t data_size = (SPIx->CR1 & SPI_CR1_DFF) ? SPI_DATASIZE_16b : SPI_DATASIZE_8b;

	/* Get DMA Stream and Channel for SPIx */
	st_SPI_DMA_settings_t* st_settings = SPI_DMA_getSettings(SPIx);

	/* Enable DMA clock */
	if (st_settings->TX_Stream >= DMA2_Stream0) {
		/* Enable DMA2 clock */
		RCC_DMA2_CLK_ENABLE;
	} else {
		/* Enable DMA1 clock */
		RCC_DMA1_CLK_ENABLE;
	}

	/* Enable DMA clock */
	if (st_settings->RX_Stream >= DMA2_Stream0) {
		/* Enable DMA2 clock */
		RCC_DMA2_CLK_ENABLE;
	} else {
		/* Enable DMA1 clock */
		RCC_DMA1_CLK_ENABLE;
	}

	if (data_size == SPI_DATASIZE_8b) {
		mem_size = DMA_MDATASIZE_8b;
		periph_size = DMA_PDATASIZE_8b;
	} else {
		mem_size = DMA_MDATASIZE_16b;
		periph_size = DMA_PDATASIZE_16b;
	}

	/* Init TX stream */
	DMA_init(st_settings->TX_Stream, st_settings->TX_Channel, mem_size, periph_size);
	/* Init RX stream */
	DMA_init(st_settings->RX_Stream, st_settings->RX_Channel, mem_size, periph_size);
}

void SPI_DMA_deinit(SPI_TypeDef* SPIx)
{
	/* Get DMA Stream and Channel for SPIx */
	st_SPI_DMA_settings_t* st_settings = SPI_DMA_getSettings(SPIx);

	/* Deinit DMA Streams */
	DMA_deinit(st_settings->TX_Stream);
	DMA_deinit(st_settings->RX_Stream);
}

uint8_t SPI_DMA_transmit8bits(SPI_TypeDef* SPIx, uint8_t* TX_Buffer, uint8_t* RX_Buffer, uint16_t count)
{

	/* Get DMA Stream and Channel for SPIx */
	st_SPI_DMA_settings_t* st_settings = SPI_DMA_getSettings(SPIx);

	/* Check if DMA available */
	if (
		st_settings->TX_Stream->NDTR ||
		st_settings->TX_Stream->NDTR ||
		(TX_Buffer == NULL && RX_Buffer == NULL)||
		SPI_IS_BUSY(SPIx)
	) {
		return 0;
	}

	/* Enable SPI RX & TX DMA */
	SPIx->CR2 |= SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN;

/* TX */
	/* Set DMA peripheral address and count */
	st_settings->TX_Stream->PAR = (uint32_t) &SPIx->DR;
	st_settings->TX_Stream->NDTR = count;

	/* Configure TX DMA direction */
	st_settings->TX_Stream->CR |= DMA_SxCR_DIR_0; 		/* Direction Memory to Peripheral */

	if(TX_Buffer != NULL) {
		/* Set DMA memory address and memory increment mode as a enabled*/
		st_settings->TX_Stream->M0AR = (uint32_t) TX_Buffer;
		st_settings->TX_Stream->CR |= DMA_SxCR_MINC;
	} else {
		st_settings->TX_Stream->M0AR = (uint32_t)0x0000;
		st_settings->TX_Stream->CR &= ~((uint32_t)DMA_SxCR_MINC);
	}

	/* Deinit first TX stream (clear DMA stream IRQ flags) */
	DMA_clearFlag(st_settings->TX_Stream, DMA_FLAG_ALL);

/* RX */
	/* Set DMA peripheral address and count */
	st_settings->RX_Stream->PAR = (uint32_t) &SPIx->DR;
	st_settings->RX_Stream->NDTR = count;

	/* Configure RX DMA direction */
	st_settings->RX_Stream->CR &= ~((uint32_t)DMA_SxCR_DIR); 		/* Direction Peripheral to Memory */

	if(RX_Buffer != NULL) {
		/* Set DMA memory address and memory increment mode as a enabled*/
		st_settings->RX_Stream->M0AR = (uint32_t) RX_Buffer;
		st_settings->RX_Stream->CR |= DMA_SxCR_MINC;
	} else {
		st_settings->RX_Stream->M0AR = (uint32_t)0x0000;
		st_settings->RX_Stream->CR &= ~((uint32_t)DMA_SxCR_MINC);
	}

	/* Deinit first RX stream (clear DMA stream IRQ flags) */
	DMA_clearFlag(st_settings->RX_Stream, DMA_FLAG_ALL);


	/* Enable TX stream */
	st_settings->TX_Stream->CR |= DMA_SxCR_EN;
	/* Enable RX stream */
	st_settings->RX_Stream->CR |= DMA_SxCR_EN;

	/* Return OK */
	return 1;
}

uint16_t SPI_DMA_transmit16bits(SPI_TypeDef* SPIx, uint16_t* TX_Buffer, uint16_t* RX_Buffer, uint16_t count)
{

	/* Get DMA Stream and Channel for SPIx */
	st_SPI_DMA_settings_t* st_settings = SPI_DMA_getSettings(SPIx);

	/* Check if DMA available */
	if (
		st_settings->TX_Stream->NDTR ||
		(TX_Buffer == NULL)||
		SPI_IS_BUSY(SPIx)
	) {
		return 0;
	}

	/* Enable SPIx TX DMA */
	SPIx->CR2 |= SPI_CR2_TXDMAEN;

	/* Set memory size */


	/* Set DMA peripheral address and count */
	st_settings->TX_Stream->PAR = (uint32_t) &SPIx->DR;
	st_settings->TX_Stream->NDTR = count;

	/* Configure TX DMA direction */
	st_settings->TX_Stream->CR |= DMA_SxCR_DIR_0; 		/* Direction Memory to Peripheral */

	/* Set DMA memory address and memory increment mode as a enabled*/
	st_settings->TX_Stream->M0AR = (uint32_t) TX_Buffer;
	st_settings->TX_Stream->CR |= DMA_SxCR_MINC;

	/* Deinit first TX stream (clear flags) */
	DMA_clearFlag(st_settings->TX_Stream, DMA_FLAG_ALL);
//	DMA1->HIFCR |= DMA_HIFCR_CFEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CHTIF4| DMA_HIFCR_CTCIF4;

	/* Enable TX stream */
	st_settings->TX_Stream->CR |= DMA_SxCR_EN;

	/* Return OK */
	return 1;
}


/* Private functions */
static st_SPI_DMA_settings_t* SPI_DMA_getSettings(SPI_TypeDef* SPIx)
{
	st_SPI_DMA_settings_t* ret_settings;
	#ifdef SPI1
		if (SPIx == SPI1) {
			ret_settings = &st_spi1_dma;
		}
	#endif
	#ifdef SPI2
		if (SPIx == SPI2) {
			ret_settings = &st_spi2_dma;
		}
	#endif
	#ifdef SPI3
		if (SPIx == SPI3) {
			ret_settings = &st_spi3_dma;
		}
	#endif

	return ret_settings;
}
