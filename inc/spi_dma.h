/*
 * spi_dma.h
 *
 *  Created on: 08.01.2019
 *      Author: oem
 */

#ifndef SPI_DMA_H_
#define SPI_DMA_H_

/* Default DMA streams and channels:
SPIx     | DMA  | DMA TX Stream | DMA TX Channel | DMA RX Stream | DMA RX Channel

SPI1     | DMA2 | DMA Stream 3  | DMA Channel 3  | DMA Stream 2  | DMA Channel 3
SPI2     | DMA1 | DMA Stream 4  | DMA Channel 0  | DMA Stream 3  | DMA Channel 0
SPI3     | DMA1 | DMA Stream 5  | DMA Channel 0  | DMA Stream 0  | DMA Channel 0
*/

/* Includes ------------------------------------------------------------------*/
#include "def.h"
#include "stm32f4xx.h"
#include "spi.h"
#include "dma.h"
#include "rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*!
 * @brief  Initializes SPI peripheral DMA.
 * @note   This function initializes TX and RX DMA streams for SPIx.
 * @note   SPI HAVE TO be previously initialized using @ref SPI library.
 * @param  *SPIx: Pointer to SPI peripheral where you want to enable DMA.
 * @return none
 */
void SPI_DMA_init(SPI_TypeDef* SPIx);


/*!
 * @brief  Deinitializes SPI peripheral DMA.
 * @note   This function deinitializes TX and RX DMA streams for SPIx.
 * @param  *SPIx: Pointer to SPI peripheral where you want to disable DMA.
 * @return none
 */
void SPI_DMA_deinit(SPI_TypeDef* SPIx);

/*!
 * @brief  	Transmit 8-bits data over SPI using DMA.
 * @note
 * @param  	*SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 3
 * @param  	*TX_Buffer: Pointer to TX_Buffer where DMA will take data to sent over SPI
 * 				Set this parameter to NULL, if you want to sent "0x00" and only receive data into *RX_Buffer pointer
 * @param  	*RX_Buffer: Pointer to RX_Buffer where DMA will save data from SPI.
 * 				Set this parameter to NULL, if you don't want to receive any data, only sent from TX_Buffer
 * @param	size: number of bytes to send/receive over SPI
 * @return 	Sending status about started transmision:
 *            - 0: DMA has not started with sending data
 *            - > 0: DMA has started with sending data
 */
uint8_t SPI_DMA_transmit8bits(SPI_TypeDef* SPIx, uint8_t* TX_Buffer, uint8_t* RX_Buffer, uint16_t count);

/*!
 * @brief  	Transmit 16-bits data over SPI using DMA.
 * @note
 * @param  	*SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 3
 * @param  	*TX_Buffer: Pointer to TX_Buffer where DMA will take data to sent over SPI
 * 				Set this parameter to NULL, if you want to sent "0x0000" and only receive data into *RX_Buffer pointer
 * @param  	*RX_Buffer: Pointer to RX_Buffer where DMA will save data from SPI.
 * 				Set this parameter to NULL, if you don't want to receive any data, only sent from TX_Buffer
 * @param	size: number of bytes to send/receive over SPI
 * @return 	Sending status about started transmision:
 *            - 0: DMA has not started with sending data
 *            - > 0: DMA has started with sending data
 */
uint16_t SPI_DMA_transmit16bits(SPI_TypeDef* SPIx, uint16_t* TX_Buffer, uint16_t* RX_Buffer, uint16_t count);

#endif /* SPI_DMA_H_ */
