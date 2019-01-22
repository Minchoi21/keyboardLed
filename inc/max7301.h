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
/* Typedef -------------------------------------------------------------------*/
/* Macro ---------------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function prototypes -------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/

/*!
 * @brief Configure
 * @note
 * @warning none
 * @param  	none
 * @return 	none
 */
void TLC5971_init( void );

#endif /* MAX7301_H_ */
