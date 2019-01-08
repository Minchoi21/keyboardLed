/*
 * spi_dma.h
 *
 *  Created on: 08.01.2019
 *      Author: oem
 */

#ifndef SPI_DMA_H_
#define SPI_DMA_H_

/* Includes ------------------------------------------------------------------*/
#include "def.h"
#include "stm32f4xx.h"
#include "spi.h"
#include "dma.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
 * @brief  	Transmit data over SPI using DMA.
 * @warning none
 * @param  	*SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 3
 * @param  	*TX_Buffer: Pointer to TX_Buffer where DMA will take data to sent over SPI
 * @param	size: number of bytes to send/receive over SPI
 * @return 	Sending status about started transmision:
 *            - 0: DMA has not started with sending data
 *            - > 0: DMA has started with sending data
 */
uint8_t SPI_DMA_transmit(SPI_TypeDef* SPIx, uint8_t* TX_Buffer, uint16_t count);

#endif /* SPI_DMA_H_ */
