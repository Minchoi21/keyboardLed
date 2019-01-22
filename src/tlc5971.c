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

void TLC5971_init(void)
{
	tlc5971_drv.luminosity = 0x0000;

	for(uint8_t num = 0; num < TLC5971_NUM_DRIVERS; num++)	{
		tlc5971_drv.PAC[num].CF[0] = 0x96;
		tlc5971_drv.PAC[num].CF[1] = 0x5F;
		tlc5971_drv.PAC[num].CF[2] = 0xFF;
		tlc5971_drv.PAC[num].CF[3] = 0xFF;
	}

	TLC5971_clr_led_all();
}

//------------------------------------------------------------------------------
void TLC5971_set_led( en_TLC5971_led_t led)
{
	uint8_t pac_num, led_num;

	if(led & LED_SET_ALL_MASK) {
//		if(led & LED_SERIES_MASK) {
//			tlc5971_drv.LDS &= (~LED_SERIES_MASK);
//		}
//		else if(led & LED_MODE_MASK) {
//			tlc5971_drv.LDS &= (~LED_MODE_MASK);
//		}
		tlc5971_drv.LDS |= led;
	}

		for(uint8_t i = 0; i < TLC5971_ALL_NUM_LED; i++ ) {
			pac_num = (uint8_t)(i/TLC5971_NUM_LED);
			led_num = (uint8_t)(i%TLC5971_NUM_LED);
			if(tlc5971_drv.LDS & (0x01 << i)) {
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_red.arr[0] = (uint8_t)(tlc5971_drv.luminosity >> 8);
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_red.arr[1] = (uint8_t)(tlc5971_drv.luminosity & 0xff);
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_green.arr[0] = (uint8_t)(tlc5971_drv.luminosity >> 8);
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_green.arr[1] = (uint8_t)(tlc5971_drv.luminosity & 0xff);
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_blue.arr[0] = (uint8_t)(tlc5971_drv.luminosity >> 8);
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_blue.arr[1] = (uint8_t)(tlc5971_drv.luminosity & 0xff);
			}
			else {
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_red.val = 0x0000;
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_green.val = 0x0000;
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_blue.val = 0x0000;
			}
		}
}

//------------------------------------------------------------------------------
void TLC5971_clr_led( en_TLC5971_led_t led)
{

	if(led & LED_SET_ALL_MASK) {
		tlc5971_drv.LDS &= (~led);
	}
}

//------------------------------------------------------------------------------
void TLC5971_set_led_all( void )
{
	  tlc5971_drv.LDS |= LED_SET_ALL_MASK;
}

//------------------------------------------------------------------------------
void TLC5971_clr_led_all( void )
{
	  tlc5971_drv.LDS = LED_CLR_ALL_MASK;
}

//------------------------------------------------------------------------------
void TLC5971_set_luminosity( uint16_t lum )
{
//	tlc5971_drv.luminosity = (uint16_t)(lum*(65535/1023)); //scaling value

//	lum = 1023 - lum;
//	lum = pow( (float)lum / (float)1023, 2.8 ) * 255 + 0.5;
//	tlc5971_drv.luminosity = lum;
	tlc5971_drv.luminosity = lum;
}

//------------------------------------------------------------------------------
void TLC5971_send_packet(SPI_TypeDef* SPIx)
{
	/* Disable interrupts */
//	__disable_irq();

	/* Send package */
	SPI_DMA_transmit8bits(SPIx, (uint8_t*)&tlc5971_drv.PAC, NULL, (uint16_t)TLC5971_ALL_PAC_LEN);
//	SPI_txData8bit(SPI1, (uint8_t*)&tlc5971_drv.PAC, (uint16_t)TLC5971_PAC_LEN);

	/* Enable interrupts back */
//	__enable_irq();
}
