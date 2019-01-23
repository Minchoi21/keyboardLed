/*
 * spi.h
 *
 *  Created on: 04.12.2018
 *      Author: Daniel
 */

#ifndef SPI_H_
#define SPI_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "gpio.h"


/* Private typedef -----------------------------------------------------------*/
/*!
 * @brief SPI baud rate control enumeration
 */
typedef enum {
	SPI_BR_DIV_2 		= 0x00, 	/*!< 000: fPCLK/2 */
	SPI_BR_DIV_4 		= 0x01,     /*!< 001: fPCLK/4 */
	SPI_BR_DIV_8 		= 0x02,    	/*!< 010: fPCLK/8 */
	SPI_BR_DIV_16 		= 0x03, 	/*!< 011: fPCLK/16 */
	SPI_BR_DIV_32 		= 0x04,     /*!< 100: fPCLK/32 */
	SPI_BR_DIV_64 		= 0x05,    	/*!< 101: fPCLK/64 */
	SPI_BR_DIV_128 		= 0x06, 	/*!< 110: fPCLK/128 */
	SPI_BR_DIV_256 		= 0x07,     /*!< 111: fPCLK/256 */
} en_SPI_Baudrate_t;

/*!
 * @brief  SPI PinsPack enumeration to select pins combination for SPI
 *
 *         |PINS PACK 1            |PINS PACK 2            |PINS PACK 3
 * SPIX    |MOSI   MISO    SCK     |MOSI   MISO    SCK     |MOSI   MISO    SCK
 * SPI1    |PA7    PA6     PA5     |PB5    PB4     PB3     |
 * SPI2    |PC3    PC2     PB10    |PB15   PB14    PB13    |PI3    PI2     PI0
 * SPI3    |PB5    PB4     PB3     |PC12   PC11    PC10    |
 */
typedef enum {
	SPI_PINSPACK_1,
	SPI_PINSPACK_2,
	SPI_PINSPACK_3,
} en_SPI_PinsPack_t;

/*!
 * @brief SPI Data size enumeration
 */
typedef enum {
	SPI_DATASIZE_8b, 	/*!< SPI in 8-bits mode */
	SPI_DATASIZE_16b 	/*!< SPI in 16-bits mode */
} en_SPI_dataSize_t;

/* Private define ------------------------------------------------------------*/


/*!
 * @brief Specify which SPI can be use
 */
#define USE_SPI1
#define USE_SPI2
#define USE_SPI3

/*!
 * @brief  Check SPI busy status
 */
#define SPI_IS_BUSY(SPIx) (((SPIx)->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0 || ((SPIx)->SR & SPI_SR_BSY))

/*!
 * @brief  SPI wait till end
 */
#define SPI_WAIT(SPIx)            while (SPI_IS_BUSY(SPIx))

/*!
 * @brief  Checks if SPI is enabled
 */
#define SPI_CHECK_ENABLED(SPIx)   if (!((SPIx)->CR1 & SPI_CR1_SPE)) {return;}

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*!
 * @brief  Initializes SPIx peripheral with default settings.
 * Master mode, 8 data bits, clock polarity low, data sampled at first edge,
 * prescaler set to 32, firstbit MSB, software SS pin configure, direction is full duplex 3 wires.
 * @warning none
 * @param  	*SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 3.
 * @param  	pinspack: Pinspack you will use from default SPI table. This parameter can be a value of @ref en_SPI_PinsPack_t enumeration.
 * @param  	data_size: SPI data size which will be used. This parameter can be a value of @ref en_SPI_dataSize_t enumeration.
 * @return 	none
 */
void SPI_init(SPI_TypeDef* SPIx, en_SPI_PinsPack_t pinspack, en_SPI_dataSize_t data_size);

/*!
 * @brief  Initializes SPIx pins.
 * @warning none
 * @param  	*SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 3
 * @param  	pinspack: Pinspack you will use from default SPI table. This parameter can be a value of @ref en_SPI_PinsPack_t enumeration
 * @return 	none
 */
void SPI_initPinsPack(SPI_TypeDef* SPIx, en_SPI_PinsPack_t pinspack);
/*!
 * @brief Writes multiple bytes over SPI
 * @warning none
 * @param  	*SPIx: pointer to SPIx peripheral you will use, where x is between 1 to 3
 * @param  	*pData: pointer to data where DMA will take data to sent over SPI
 * @param	size: number of bytes to send over SPI
 * @return 	none
 */
void SPI_txData8bit(SPI_TypeDef* SPIx, uint8_t* pData, uint32_t size);

/*!
 * @brief Writes multiple bytes over SPI
 * @warning none
 * @param  	*SPIx: pointer to SPIx peripheral you will use, where x is between 1 to 3
 * @param  	*pData: 16-bit data size to send over SPI
 * @param	size: number of bytes to send over SPI
 * @return 	none
 */
void SPI_txData16bit(SPI_TypeDef* SPIx, uint16_t* pData, uint32_t size);

/*!
 * @brief Enable SPI peripheral
 * @warning none
 * @param  	*SPIx: pointer to SPIx peripheral you will use, where x is between 1 to 3
 * @return 	none
 */
__INLINE void SPI_enable(SPI_TypeDef* SPIx)
{
	/* Enable SPIx */
	SPIx->CR1 |= SPI_CR1_SPE;
}

/*!
 * @brief Disable SPI peripheral
 * @warning none
 * @param  	*SPIx: pointer to SPIx peripheral you will use, where x is between 1 to 3
 * @return 	none
 */
__INLINE void SPI_disable(SPI_TypeDef* SPIx)
{
	/* Disable SPIx */
	SPIx->CR1 &= ~SPI_CR1_SPE;
}



#endif /* SPI_H_ */
