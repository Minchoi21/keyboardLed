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
	static uint16_t TX_buffer = 0x0000;
	static uint16_t RX_buffer = 0x0000;
/* Function prototypes -----------------------------------------------*/
/* Functions ---------------------------------------------------------*/

static uint16_t MAX7301_createPackage(uint8_t address, uint8_t data)
{
	TX_buffer = 0x0000;

	TX_buffer |= (uint16_t) ((uint16_t) address << 8);
	TX_buffer |= (uint8_t)data;

	GPIO_resetPin(GPIOA, GPIO_Pin_4);
	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer, (uint16_t*)&RX_buffer);
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT(SPI1);
	GPIO_setPin(GPIOA, GPIO_Pin_4);

	return RX_buffer;
}

void MAX7301_init(void)
{
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPI1);

	MAX7301_createPackage(CONFIGURATION_REGISTER, 0x81);
	MAX7301_createPackage(CONFIGURATION_REGISTER, 0x81);
	MAX7301_createPackage(MAX7301_P07_P06_P05_P04, MAX7301_INPUT_NO_PULLUP);
	MAX7301_createPackage(MAX7301_P11_P10_P09_P08, MAX7301_INPUT_NO_PULLUP);
	MAX7301_createPackage(MAX7301_P15_P14_P13_P12, MAX7301_INPUT_NO_PULLUP);
	MAX7301_createPackage(MAX7301_P19_P18_P17_P16, MAX7301_INPUT_NO_PULLUP);
	MAX7301_createPackage(MAX7301_P23_P22_P21_P20, MAX7301_INPUT_NO_PULLUP);
	MAX7301_createPackage(MAX7301_P27_P26_P25_P24, MAX7301_INPUT_NO_PULLUP);
	MAX7301_createPackage(MAX7301_P31_P30_P29_P28, MAX7301_INPUT_NO_PULLUP);
}

uint16_t MAX7301_readData(void)
{
	static uint16_t buffer_in = 0x0000;

	  /* Choose version  of keyboard pinout */
	#if defined(WORK_KEYBOARD)
		MAX7301_createPackage(0x80 | MAX7301_READ_PORT_12_TO_19, 0x00);
		buffer_in = ((MAX7301_createPackage(0x00, 0x00)) << 8);
		MAX7301_createPackage(0x80 | MAX7301_READ_PORT_04_TO_11, 0x00);
		buffer_in |= ( (MAX7301_createPackage(0x00, 0x00)) & 0xFF);

		return (0xFFF & ~(buffer_in << 1));
	#else
		MAX7301_createPackage(0x80 | MAX7301_READ_PORT_12_TO_19, 0x00);
		buffer_in = ((MAX7301_createPackage(0x00, 0x00) & 0x1E ) << 6);
		MAX7301_createPackage(0x80 | MAX7301_READ_PORT_04_TO_11, 0x00);
		buffer_in |= ( (MAX7301_createPackage(0x00, 0x00)) & 0x7E);

		return (0xFFF & ~(buffer_in << 1));

	#endif /* STM32F446xx */
}


//void MAX7301_init(void)
//{
//	/* Check if SPI is enabled */
//	SPI_CHECK_ENABLED(SPI1);
//
//	TX_buffer = MAX7301_createPackage(CONFIGURATION_REGISTER, 0x81);
//
//	TX_buffer = MAX7301_createPackage(MAX7301_P07_P06_P05_P04, MAX7301_INPUT_NO_PULLUP);
//	GPIO_resetPin(GPIOA, GPIO_Pin_4);
//	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//	GPIO_setPin(GPIOA, GPIO_Pin_4);
//
//	TX_buffer = MAX7301_createPackage(MAX7301_P11_P10_P09_P08, MAX7301_INPUT_NO_PULLUP);
//	GPIO_resetPin(GPIOA, GPIO_Pin_4);
//	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//	GPIO_setPin(GPIOA, GPIO_Pin_4);
//
//	TX_buffer = MAX7301_createPackage(MAX7301_P15_P14_P13_P12, MAX7301_INPUT_NO_PULLUP);
//	GPIO_resetPin(GPIOA, GPIO_Pin_4);
//	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//	GPIO_setPin(GPIOA, GPIO_Pin_4);
//
//	TX_buffer = MAX7301_createPackage(MAX7301_P19_P18_P17_P16, MAX7301_INPUT_NO_PULLUP);
//	GPIO_resetPin(GPIOA, GPIO_Pin_4);
//	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//	GPIO_setPin(GPIOA, GPIO_Pin_4);
//
//	TX_buffer = MAX7301_createPackage(MAX7301_P23_P22_P21_P20, MAX7301_INPUT_NO_PULLUP);
//	GPIO_resetPin(GPIOA, GPIO_Pin_4);
//	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//	GPIO_setPin(GPIOA, GPIO_Pin_4);
//
//	TX_buffer = MAX7301_createPackage(MAX7301_P27_P26_P25_P24, MAX7301_INPUT_NO_PULLUP);
//	GPIO_resetPin(GPIOA, GPIO_Pin_4);
//	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//	GPIO_setPin(GPIOA, GPIO_Pin_4);
//
//	TX_buffer = MAX7301_createPackage(MAX7301_P31_P30_P29_P28, MAX7301_INPUT_NO_PULLUP);
//	GPIO_resetPin(GPIOA, GPIO_Pin_4);
//	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//	GPIO_setPin(GPIOA, GPIO_Pin_4);
//}
//
//uint16_t MAX7301_readData(void)
//{
//	RX_buffer = 0x0000;
//	TX_buffer = 0x8000 | (uint16_t) ((uint16_t) MAX7301_READ_PORT_12_TO_19 << 8);
//
//	GPIO_resetPin(GPIOA, GPIO_Pin_4);
//	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//	GPIO_setPin(GPIOA, GPIO_Pin_4);
//
//	TX_buffer = 0x0000;
//	GPIO_resetPin(GPIOA, GPIO_Pin_4);
//	RX_buffer = ((SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer)) << 8);
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//	GPIO_setPin(GPIOA, GPIO_Pin_4);
//
//	TX_buffer = 0x8000 | (uint16_t) ((uint16_t) MAX7301_READ_PORT_04_TO_11 << 8);
//
//	GPIO_resetPin(GPIOA, GPIO_Pin_4);
//	SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer);
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//	GPIO_setPin(GPIOA, GPIO_Pin_4);
//
//	TX_buffer = 0x0000;
//	GPIO_resetPin(GPIOA, GPIO_Pin_4);
//	RX_buffer |= ((SPI_txRxDataHalfWord(SPI1, (uint16_t*)&TX_buffer)) & 0xFF);
//	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
//	SPI_WAIT(SPI1);
//	GPIO_setPin(GPIOA, GPIO_Pin_4);
//
//	return (0x3FF & ~(RX_buffer << 1));
//
//}



