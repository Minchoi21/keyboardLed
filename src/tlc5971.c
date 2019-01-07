/*
 * tlc5971.c
 *
 *  Created on: 04.12.2018
 *      Author: Daniel
 */

/* Includes ------------------------------------------------------------------*/
#include "tlc5971.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static st_tlc5971_t tlc5971_drv;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

//------------------------------------------------------------------------------
//! @fcn TLC5971_Init
//!  Set the initial value of LED driver TLC5971
//! @warning none
//! @param  none
//! @return none
//------------------------------------------------------------------------------
void TLC5971_init(void) {

	tlc5971_drv.luminosity = 0x0000;

	tlc5971_drv.PAC.CF[0] = 0x96;
	tlc5971_drv.PAC.CF[1] = 0x5F;
	tlc5971_drv.PAC.CF[2] = 0xFF;
	tlc5971_drv.PAC.CF[3] = 0xFF;

	TLC5971_CLR_LED_ALL();
	TLC5971_SEND_PACKET(SPI2);
}

//------------------------------------------------------------------------------
//! @fcn TLC5971_set_led
//! Set single LED to light up
//! @warning none
//! @param  	uint8_t led  ->  12 number of led. Takes values from 0 - 11
//! @return none
//------------------------------------------------------------------------------
void TLC5971_set_led( uint16_t led) {

	if(led & LED_SET_ALL_MASK) {
		if(led & LED_SERIES_MASK) {
			tlc5971_drv.LDS &= (~LED_SERIES_MASK);
		}
		else if(led & LED_MODE_MASK) {
			tlc5971_drv.LDS &= (~LED_MODE_MASK);
		}
		tlc5971_drv.LDS |= led;
	}
}

//------------------------------------------------------------------------------
//! @fcn TLC5971_clr_led
//! Set single LED to light off
//! @warning none
//! @param  	uint8_t led  ->  12 number of led. Takes values from 0 - 11
//! @return none
//------------------------------------------------------------------------------
void TLC5971_clr_led( uint16_t led) {

	if(led & LED_SET_ALL_MASK) {
		tlc5971_drv.LDS &= (~led);
	}
}

//------------------------------------------------------------------------------
//! @fcn TLC5971_set_led_all
//! Set all LED light up
//! @warning none
//! @param  none
//! @return none
//------------------------------------------------------------------------------
void TLC5971_set_led_all( void ) {
	  tlc5971_drv.LDS |= LED_SET_ALL_MASK;
}

//------------------------------------------------------------------------------
//! @fcn TLC5971_clr_led_all
//! Set all LED light off
//! @warning none
//! @param  none
//! @return none
//------------------------------------------------------------------------------
void TLC5971_clr_led_all( void ) {
	  tlc5971_drv.LDS = LED_CLR_ALL_MASK;
}

//------------------------------------------------------------------------------
//! @fcn TLC5971_set_luminosity
//! Set the brightness of the LEDs
//! @warning none
//! @param  	uint16_t lum  ->  luminosity LED. Takes values from 0 - 1024
//! @return none
//------------------------------------------------------------------------------
void TLC5971_set_luminosity( uint16_t lum ) {
//	tlc5971_drv.luminosity = (uint16_t)(lum*(65535/1023)); //scaling value

//	lum = 1023 - lum;
//	lum = pow( (float)lum / (float)1023, 2.8 ) * 255 + 0.5;
//	tlc5971_drv.luminosity = lum;
	tlc5971_drv.luminosity = lum;
}


//------------------------------------------------------------------------------
//! @fcn TLC5971_send_packet
//! Set data packet and send to LED driver
//! @warning none
//! @param  none
//! @return none
//------------------------------------------------------------------------------
void TLC5971_send_packet(SPI_TypeDef* SPIx) {
	uint8_t i = 0;

	for( i = 0; i < TLC5971_NUM_LED; i++ ) {
		if(tlc5971_drv.LDS & (0x01 << i)) {
			tlc5971_drv.PAC.GS[i] = tlc5971_drv.luminosity;
		}
		else tlc5971_drv.PAC.GS[i] = 0x0000;
	}

	/* Disable interrupts */
	__disable_irq();
	/* Send package */
	SPI_txData8bit(SPIx, (uint8_t*)&tlc5971_drv.PAC, (uint16_t)TLC5971_PAC_LEN);
	/* Enable interrupts back */
	__enable_irq();


}
