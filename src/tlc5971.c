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
static inline void TLC5971_setPackageValue(void) ;

/* Functions ---------------------------------------------------------*/
void TLC5971_init(void)
{
	tlc5971_drv.luminosity = 0x0000;
	TLC5971_resetColorLeds();

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


void TLC5971_toggleLed( en_TLC5971_led_t led )
{
	if(led & LED_ALL_MASK) {
			tlc5971_drv.LDS ^= led;
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
void TLC5971_resetColorLeds()
{
	uint8_t* tmp = (uint8_t*)&tlc5971_drv.color;
	for(uint8_t i = 0; i < TLC5971_ALL_NUM_LED; i++) {
		*(tmp+(i/2)) &= ~(C_WHITE << ((i%2)*0x04));
		//tlc5971_drv.color |= (st_TLC5971_color_leds_t)(C_NONE << (i*0x04));
	}
}

//------------------------------------------------------------------------------
void TLC5971_setColorLed(en_TLC5971_colors_t color, en_TLC5971_led_offset_t led)
{
	uint8_t* tmp = (uint8_t*)&tlc5971_drv.color;

	*(tmp+(led/2)) &= ~(color << ((led%2)*0x04));
	*(tmp+(led/2)) |= color << ((led%2)*0x04);
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
	uint8_t* tmp = (uint8_t*)&tlc5971_drv.color;
	uint8_t pac_num, led_num;

	for(uint8_t i = 1, c = 0; i <= TLC5971_ALL_NUM_LED; i++ , c++) {
		pac_num = (uint8_t)((TLC5971_ALL_NUM_LED - i) / TLC5971_NUM_LED);
		led_num = (uint8_t)((TLC5971_ALL_NUM_LED - i) % TLC5971_NUM_LED);
		if(tlc5971_drv.LDS & (0x01 << (i-1))) {
			uint8_t mask_color = (*(tmp+(c/2)) >>  ((c%2)*0x04));
			if(	mask_color & 0x04U ) {
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_red.arr[0] = (uint8_t)(tlc5971_drv.luminosity >> 8);
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_red.arr[1] = (uint8_t)(tlc5971_drv.luminosity & 0xff);
			}
			if(	mask_color & 0x02U ) {
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_green.arr[0] = (uint8_t)(tlc5971_drv.luminosity >> 8);
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_green.arr[1] = (uint8_t)(tlc5971_drv.luminosity & 0xff);
			}
			if(	mask_color & 0x01U ) {
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_blue.arr[0] = (uint8_t)(tlc5971_drv.luminosity >> 8);
				tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_blue.arr[1] = (uint8_t)(tlc5971_drv.luminosity & 0xff);
			}
		}
		else {
			tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_red.val = 0x0000;
			tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_green.val = 0x0000;
			tlc5971_drv.PAC[pac_num].rgb_led[led_num].GS_blue.val = 0x0000;
		}
	}
}
