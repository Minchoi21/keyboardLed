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
static uint16_t leds_offset[] = { LED_CH_1,
								LED_CH_2,
								LED_CH_3,
								LED_CH_4,
								LED_CH_5,
								LED_CH_6,
								LED_CH_7,
								LED_CH_8,
								LED_CH_9,
								LED_CH_10,
								LED_CH_11,
								LED_CH_12 };

/* Private function prototypes -----------------------------------------------*/
static inline void TLC5971_setPackageValue(void) ;

/* Functions ---------------------------------------------------------*/
void TLC5971_init(void)
{
	tlc5971_drv.luminosity = 0x0000;

	for(uint8_t num = 0; num < TLC5971_NUM_DRIVERS; num++)	{
		tlc5971_drv.PAC[num].CF[0] = 0x96;
		tlc5971_drv.PAC[num].CF[1] = 0x5F;
		tlc5971_drv.PAC[num].CF[2] = 0xFF;
		tlc5971_drv.PAC[num].CF[3] = 0xFF;
	}

	TLC5971_clrLedAll();
}

//------------------------------------------------------------------------------
void TLC5971_setLed( en_TLC5971_led_t led)
{
	if(led & LED_ALL_MASK) {

			tlc5971_drv.LDS |= led;
	}
	TLC5971_setPackageValue();
}

//------------------------------------------------------------------------------
void TLC5971_clrLed( en_TLC5971_led_t led)
{

	if(led & LED_ALL_MASK) {
		tlc5971_drv.LDS &= (~led);
	}
	TLC5971_setPackageValue();
}

//------------------------------------------------------------------------------
void TLC5971_setLedAll( void )
{
	tlc5971_drv.LDS |= LED_ALL_MASK;
	TLC5971_setPackageValue();
}

//------------------------------------------------------------------------------
void TLC5971_clrLedAll( void )
{
	tlc5971_drv.LDS &= ~LED_ALL_MASK;
	TLC5971_setPackageValue();
}

//------------------------------------------------------------------------------
void TLC5971_setLuminosity( uint16_t lum )
{
	tlc5971_drv.luminosity = (uint16_t)(lum*(65535/511)); 	// calculate luminosity
}

//------------------------------------------------------------------------------
void TLC5971_sendPacket(SPI_TypeDef* SPIx)
{
	/* Disable interrupts */
//	__disable_irq();

	/* Send package */
	SPI_DMA_transmit8bits(SPIx, (uint8_t*)&tlc5971_drv.PAC, NULL, (uint16_t)TLC5971_ALL_PAC_LEN);

	/* Enable interrupts back */
//	__enable_irq();
}


/* Private functions ---------------------------------------------------------*/
static inline void TLC5971_setPackageValue(void)
{
	uint8_t pac_num, led_num;

	for(uint8_t i = 1; i <= TLC5971_ALL_NUM_LED; i++ ) {
		pac_num = (uint8_t)((TLC5971_ALL_NUM_LED - i) / TLC5971_NUM_LED);
		led_num = (uint8_t)((TLC5971_ALL_NUM_LED - i) % TLC5971_NUM_LED);
		if(tlc5971_drv.LDS & (0x01 << (i-1))) {
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
