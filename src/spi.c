/*
 * spi.c
 *
 *  Created on: 04.12.2018
 *      Author: Daniel
 */

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

void SPI_init(SPI_TypeDef* SPIx, en_SPI_PinsPack_t pinspack)
{
	/* Init pins */
	SPI_initPinsPack(SPIx, pinspack);

	/* Disable SPIx first */
	SPIx->CR1 &= ~SPI_CR1_SPE;

	/* Master selection, BR: Fpclk/SPI_BR_DIV_xxx, CPOL and CPHA at zero (rising first edge) */
	SPIx->CR1 = SPI_CR1_MSTR|(SPI_BR_DIV_64 << SPI_CR1_BR_Pos)|SPI_CR1_SSM|SPI_CR1_SSI; //|SPI_CR1_SSM|SPI_CR1_SSI
	/* Set 8-bit data frame format */
	SPIx->CR1 &= ~SPI_CR1_DFF;

//	SPIx->CR2 = SPI_CR2_SSOE|SPI_CR2_RXNEIE|SPI_CR2_TXEIE|SPI_CR2_FRF;
	/* Enable SPIx */
	SPIx->CR1 |= SPI_CR1_SPE;
}

void SPI_initPinsPack(SPI_TypeDef* SPIx, en_SPI_PinsPack_t pinspack)
{
	/* Init SPI1 pins */
	#ifdef USE_SPI1
		if (SPIx == SPI1) {
			#if defined(GPIOA)
				if (pinspack == SPI_PINSPACK_1) {
					GPIO_initAlternate(GPIOA, GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AF_5);
				}
			#endif
			#if defined(GPIOB)
				if (pinspack == SPI_PINSPACK_2) {
					GPIO_initAlternate(GPIOB, GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AF_5);
				}
			#endif
		}
	#endif
	/* Init SPI2 pins */
	#ifdef USE_SPI2
		if (SPIx == SPI2) {
			#if defined(GPIOB) && defined(GPIOC)
				if (pinspack == SPI_PINSPACK_1) {
					GPIO_initAlternate(GPIOB, GPIO_Pin_10, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AF_5);
					GPIO_initAlternate(GPIOC, GPIO_Pin_2|GPIO_Pin_3, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AF_5);
				}
			#endif
			#if defined(GPIOB)
				if (pinspack == SPI_PINSPACK_2) {
					GPIO_initAlternate(GPIOB, GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AF_5);
				}
			#endif
			#if defined(GPIOI)
				if (pinspack == SPI_PINSPACK_3) {
					GPIO_initAlternate(GPIOI, GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AF_5);
				}
			#endif
		}
	#endif
	/* Init SPI3 pins */
	#ifdef USE_SPI3
		if (SPIx == SPI3) {
			#if defined(GPIOB)
				if (pinspack == SPI_PINSPACK_1) {
					GPIO_initAlternate(GPIOB, GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AF_5);
				}
			#endif
			#if defined(GPIOC)
				if (pinspack == SPI_PINSPACK_2) {
					GPIO_initAlternate(GPIOC, GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AF_5);
				}
			#endif
		}
	#endif
}

void SPI_txData8bit(SPI_TypeDef* SPIx, uint8_t *pData, uint32_t size)
{
	uint32_t i;

	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);

	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPIx);

	for (i = 0; i < size; i++) {
		/* Fill output buffer with data */
		SPIx->DR = pData[i];
		/* Wait for SPI to end everything */
		SPI_WAIT(SPIx);
	}

//	/* Check if SPI is enabled */
//	SPI_CHECK_ENABLED(SPI1);
//
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//
//	for (i = 0; i < size; i++) {
//		/* Fill output buffer with data */
//		SPI1->DR = pData[i];
//
//		/* Wait for SPI to end everything */
//		SPI_WAIT(SPI1);
//
//		/* Read data register */
//		dataIn = SPI1->DR;
//	}
}

void SPI_txData16bit(SPI_TypeDef* SPIx, uint16_t *pData, uint32_t size)
{
	uint32_t i;

	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);

	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPIx);

	for (i = 0; i < size; i++) {
		/* Fill output buffer with data */
		SPIx->DR = pData[i];
		/* Wait for SPI to end everything */
		SPI_WAIT(SPIx);
	}

}
