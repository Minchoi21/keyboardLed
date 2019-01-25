/*
 * max7301.c
 *
 *  Created on: 22.01.2019
 *      Author: Daniel
 */


/* Includes ------------------------------------------------------------------*/
#include "max7301.h"

/* Typedef -----------------------------------------------------------*/

/* Define ------------------------------------------------------------*/
/* Macro -------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
	static uint16_t TX_buffer= 0x0000;
	static uint16_t RX_buffer = 0;
/* Function prototypes -----------------------------------------------*/
/* Functions ---------------------------------------------------------*/

static uint16_t MAX7301_createPackage(uint8_t address, uint8_t data)
{
	uint16_t buffer = 0x00;

	buffer |= (uint16_t) ((uint16_t) address << 8);
	buffer |= (uint8_t)data;
	return buffer;
}

void MAX7301_init(void)
{
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPI1);

	TX_buffer = MAX7301_createPackage(CONFIGURATION_REGISTER, 0x81);

	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);

	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);


	TX_buffer = MAX7301_createPackage(MAX7301_P07_P06_P05_P04, MAX7301_INPUT_NO_PULLUP);
	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);

	TX_buffer = MAX7301_createPackage(MAX7301_P11_P10_P09_P08, MAX7301_INPUT_NO_PULLUP);
	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);

	TX_buffer = MAX7301_createPackage(MAX7301_P15_P14_P13_P12, MAX7301_INPUT_NO_PULLUP);
	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);

	TX_buffer = MAX7301_createPackage(MAX7301_P19_P18_P17_P16, MAX7301_INPUT_NO_PULLUP);
	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);

	TX_buffer = MAX7301_createPackage(MAX7301_P23_P22_P21_P20, MAX7301_INPUT_NO_PULLUP);
	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);

	TX_buffer = MAX7301_createPackage(MAX7301_P27_P26_P25_P24, MAX7301_INPUT_NO_PULLUP);
	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);

	TX_buffer = MAX7301_createPackage(MAX7301_P31_P30_P29_P28, MAX7301_INPUT_NO_PULLUP);
	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);
}

uint16_t MAX7301_readData(void)
{

	uint16_t address = MAX7301_READ_PORT_04_TO_11;

	TX_buffer = 0x8000;
	TX_buffer = TX_buffer | (uint16_t) ((uint16_t) address << 8);


	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);

	TX_buffer = 0x0000;
	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	RX_buffer = SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);

	return RX_buffer;

}

