/*
 * max7301.h
 *
 *  Created on: 22.01.2019
 *      Author: oem
 */

#ifndef MAX7301_H_
#define MAX7301_H_

/*!
 * @brief  MAX7301 4-wires serial-interfaced I/O expander
 * The I/O expander is controlled through an SPI-compatible 4-wire serial interface.
 */

/* Includes ------------------------------------------------------------------*/
#include "def.h"
#include "spi.h"
#include "spi_dma.h"

/* Define --------------------------------------------------------------------*/

#define CONFIGURATION_REGISTER 0x04

#define MAX7301_INPUT_NO_PULLUP   0xAA
#define MAX7301_INPUT_PULLUP      0xFF

#define MAX7301_P07_P06_P05_P04   0x09
#define MAX7301_P11_P10_P09_P08   0x0A
#define MAX7301_P15_P14_P13_P12   0x0B
#define MAX7301_P19_P18_P17_P16   0x0C
#define MAX7301_P23_P22_P21_P20   0x0D
#define MAX7301_P27_P26_P25_P24   0x0E
#define MAX7301_P31_P30_P29_P28   0x0F

#define MAX7301_READ_PORT_04_TO_11 0x44
#define MAX7301_READ_PORT_12_TO_19 0x4C
#define MAX7301_READ_PORT_20_TO_27 0x54
#define MAX7301_READ_PORT_28_TO_31 0x5C

/* Typedef -------------------------------------------------------------------*/
/* Macro ---------------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function prototypes -------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/

/*!
 * @brief Configure each expander port as a no-push-pull input using SPI
 * @note
 * @warning none
 * @param  	none
 * @return 	none
 */
void MAX7301_init( void );

uint16_t MAX7301_readData( void );



#endif /* MAX7301_H_ */
