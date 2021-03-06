/*
 * tlc5971.h
 *
 *  Created on: 04.12.2018
 *      Author: Daniel
 */

#ifndef TLC5971_H_
#define TLC5971_H_

/* Includes ------------------------------------------------------------------*/
#include "def.h"
#include "spi.h"
#include "spi_dma.h"


/* Define --------------------------------------------------------------------*/

#define LED_CLR_ALL_MASK					0x0000U
#define LED_ALL_MASK						0x03FFU

#define TLC5971_NUM_LED 					4			// number of led's connected to the single TLC5971 drivers on the keyboard
#define TLC5971_NUM_DRIVERS					3			// number of TLC5971 drivers on the keyboard
#define TLC5971_ALL_NUM_LED 				12			// number of led's connected to the all TLC5971 drivers on the keyboard
#define TLC5971_PAC_LEN						28			// length of the message sent to the single TLC5971 using SPI
#define TLC5971_ALL_PAC_LEN					84			// length of the message sent to the three TLC5971 using SPI (three drivers on the keyboard)

#define TLC5971_ADC_RES						1023		// resolution ADC to calculate luminosity


/* Typedef -------------------------------------------------------------------*/

/*!
 * @brief  Enumeration to offset definition for LEDs position
 */
typedef enum {
	TLC5971_Led1,
	TLC5971_Led2,
	TLC5971_Led3,
	TLC5971_Led4,
	TLC5971_Led5,
	TLC5971_Led6,
	TLC5971_Led7,
	TLC5971_Led8,
	TLC5971_Led9,
	TLC5971_Led10,
	TLC5971_Led11,
	TLC5971_Led12
} en_TLC5971_led_offset_t;

/*!
 * @brief  Enumeration to bit definition for LEDs Driver
 */
typedef enum {
	LED_1 		= 0x0001U,       /*! Led channel 1 */
	LED_2 		= 0x0002U,       /*! Led channel 2 */
	LED_3 		= 0x0004U,       /*! Led channel 3 */
	LED_4 		= 0x0008U,       /*! Led channel 4 */
	LED_5 		= 0x0010U,       /*! Led channel 5 */
	LED_6 		= 0x0020U,       /*! Led channel 6 */
	LED_7 		= 0x0040U,       /*! Led channel 7 */
	LED_8 		= 0x0080U,       /*! Led channel 8 */
	LED_9 		= 0x0100U,       /*! Led channel 9 */
	LED_10 		= 0x0200U,       /*! Led channel 10 */
	LED_11 		= 0x0400U,       /*! Led not used */
	LED_12 		= 0x0800U        /*! Led not used */
} en_TLC5971_led_t;

/*!
 * @brief  Enumeration to color definition for LEDs Driver
 */
typedef enum {
	C_NONE		= 0x00U,
	C_BLUE 		= 0x01U,
	C_GREEN 	= 0x02U,
	C_CYAN 		= 0x03U,		/*! G+B */
	C_RED 		= 0x04U,
	C_MAGENTA 	= 0x05U,		/*! R+B */
	C_YELLOW 	= 0x06U,		/*! R+G */
	C_WHITE		= 0x07U			/*! R+G+B */
}en_TLC5971_colors_t;

/* Leds color configuration bits */
//-----------------------------------------~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~--------------------------------------------
//|	  RED1	   |	GREEN1  |	 BLUE1    |   REDn|GREENn|BLUEn   	|	  RED10	   |	GREEN10  |	 BLUE10    |
//|	  1 bit	   |	1 bit   |	 1 bit    |	  8 x 3 bits    		|	  1 bit	   |	1 bit    |	 1 bit     |
//-----------------------------------------~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~--------------------------------------------

typedef struct {

	uint8_t led_1		:3;
	uint8_t led_1_blink	:1;
	uint8_t led_2		:3;
	uint8_t led_2_blink	:1;

	uint8_t led_3		:3;
	uint8_t led_3_blink	:1;
	uint8_t led_4		:3;
	uint8_t led_4_blink	:1;

	uint8_t led_5		:3;
	uint8_t led_5_blink	:1;
	uint8_t led_6		:3;
	uint8_t led_6_blink	:1;

	uint8_t led_7		:3;
	uint8_t led_7_blink	:1;
	uint8_t led_8		:3;
	uint8_t led_8_blink	:1;

	uint8_t led_9		:3;
	uint8_t led_9_blink	:1;
	uint8_t led_10		:3;
	uint8_t led_10_blink:1;

	uint8_t led_11		:3;
	uint8_t led_11_blink:1;
	uint8_t led_12		:3;
	uint8_t led_12_blink:1;
}st_TLC5971_leds_color_t;


/* 224-Bit Data Packet Configuration */
// sends the LEDs data
// CMD - *Command: 6-bits (0x25 = 100101b is sent, to enable copying of the 218 bit data in the 224-bit register to the 218-bit data latch
// FC - *fc: 5-bits of Function control of TLC5971 - {OUTMG, EXTGCK, TMGRST , DSPRPT, BLANK }
// BC - *bc: 21-bits with 7-bits of each of the colours of TLC5971 for OUTRn, OUTGn, OUTBn - {}
// GS - *gs: 192-bits with 16-bits for each of the 12 channels of TLC5971-{OUTB3,..., OUTB0, OUTG3,...,OUTG0, OUTR3,..., OUTR0}
//
// ** FC - Function control **
//------------------------------------------------------------------
//|	  OUTTMG   |	EXTGCK  |	 TMGRST   |   DSPRPT   |   BLANK   |
//|	  1 bit	   |	1 bit   |	 1 bit    |	  1 bit    |   1 bit   |
//------------------------------------------------------------------
//
// MSB 																																					LSB
//-------------------------------------------------------------------------------------------------~ ~ ~ ~ ~ ~ ~ ~ ~----------------------------------------
//|		CF[0]   |	  CF[1]	  |	    CF[2]    |   CF[3]      |    GS[0]   |    GS[1]   |    GS[2]   |    GS[3-8]     |    GS[9]   |   GS[10]   |   GS[11]   |
//|	  1byte	    |	 1byte    |	   1byte     |	  1byte     |  2 x 1byte |  2 x 1byte |  2 x 1byte |  12 x 1byte    |  2 x 1byte |  2 x 1byte |  2 x 1byte |
//-------------------------------------------------------------------------------------------------~ ~ ~ ~ ~ ~ ~ ~ ~----------------------------------------
//|   CMD    |    FC    |  BC RED   |  BC GREEN |  BC BLUE  |  GS OUTB3  |  GS OUTG3  |  GS OUTR3  |       ...      |  GS OUTB0  |  GS OUTG0  |  GS OUTR0  |
//|  6bits   |  5bits   |   7bits	|   7bits 	|   7bits	|   16bits   |   16bits   |   16bits   |    6x16Bits    |   16bits   |   16bits   |   16bits   |
//-------------------------------------------------------------------------------------------------~ ~ ~ ~ ~ ~ ~ ~ ~----------------------------------------
//  100101      10010      1111111     1111111     1111111     Channel_1    Channel_2    Channel_3     Channel_4-9    Channel_10   Channel_11   Channel_12
//	10010110      01011111		 11111111		11111111

typedef struct TLC5971_rgbLed {
	union value_short GS_blue;   	// value of blue color. Takes values from 0 - 65535.
	union value_short GS_green;   	// value of green color. Takes values from 0 - 65535.
	union value_short GS_red;   	// value of red color. Takes values from 0 - 65535.
}st_TLC5971_rgbLed_t;

typedef struct TLC5971_pac {
uint8_t CF[4];									// 32 bits driver configuration
st_TLC5971_rgbLed_t rgb_led[TLC5971_NUM_LED];   // TLC5971_NUM_LED -> number of led's on single drivers
}st_tlc5971_pac_t;


typedef struct TLC5971 {
st_tlc5971_pac_t PAC[TLC5971_NUM_DRIVERS];			// LED data packet configuration
st_TLC5971_leds_color_t color;						// LED colors
uint16_t LDS;										// LED data status
uint16_t luminosity;								// LED brightness
} st_tlc5971_t;


/* Macro ---------------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function prototypes -------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/


/*!
 * @brief	Set the initial value in st_tlc5971_t structure for LED driver TLC5971
 * @note
 * @warning none
 * @param  	none
 * @return 	none
 */
void TLC5971_init( void );

/*!
 * @brief	Set LED's to light up
 * @note
 * @warning none
 * @param  	en_TLC5971_led_t led  -> the numbers of the diode to turn on. This parameter can be a value of @ref en_TLC5971_led_t enumeration
 * @return 	none
 */
void TLC5971_setLed( en_TLC5971_led_t led );

/*!
 * @brief	Set LED's to light off.
 * @note
 * @warning none
 * @param  	en_TLC5971_led_t led  -> the numbers of the diode to turn off. This parameter can be a value of @ref en_TLC5971_led_t enumeration
 * @return 	none
 */
void TLC5971_clrLed( en_TLC5971_led_t led );

/*!
 * @brief	Toggle LED's
 * @note
 * @warning none
 * @param  	en_TLC5971_led_t led  -> the numbers of the diode to toggle. This parameter can be a value of @ref en_TLC5971_led_t enumeration
 * @return 	none
 */
void TLC5971_toggleLed( en_TLC5971_led_t led );

/*!
 * @brief	Set all LED's to light up
 * @note
 * @warning none
 * @param  	none
 * @return 	none
 */
void TLC5971_setLedAll( void );

/*!
 * @brief	Set all LED's to light off
 * @note
 * @warning none
 * @param  	none
 * @return 	none
 */
void TLC5971_clrLedAll( void );

/*!
 * @brief	Set luminosity for all LED's
 * @note
 * @warning none
 * @param  	lum: value of luminosity for each colors. This parameter can be a value form 0 - 65535
 * @return 	none
 */
void TLC5971_setLuminosity( uint16_t lum );

/*!
 * @brief	Reset color for all LED's. RGB are set as C_NONE.
 * @note
 * @warning none
 * @param  	none
 * @return 	none
 */
void TLC5971_resetColorLeds();

/*!
 * @brief	Set color for LED.
 * @note
 * @warning none
 * @param  	color: value of color to set. This parameter can be a value of @ref en_TLC5971_colors_t enumeration
 * @param	led: LEDs number for which we set the color. This parameter can be a value of @ref en_TLC5971_led_offset_t enumeration
 * @return 	none
 */
void TLC5971_setColorLed(en_TLC5971_colors_t color, en_TLC5971_led_offset_t led);

/*!
 * @brief	Send data package to the all TCL5971 drivers by SPIx using DMA
 * @note
 * @warning none
 * @param  	*SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 3
 * @return 	none
 */
void TLC5971_sendPacket( SPI_TypeDef* SPIx );

// ----- FUNCTION TO SOFTWARE SPI -------------
//extern void TLC5971_set_led(uint8_t led, uint16_t intensity);
//extern void TLC5971_set_led_all(uint16_t intensity);
//extern void TLC5971_update(void);

//    uint32_t cmd: 6;
//    uint32_t OUTTMG: 1;
//    uint32_t EXTGCK: 1;
//    uint32_t TMGRST: 1;
//    uint32_t DSPRPT: 1;
//    uint32_t BLANK: 1;
//	    uint32_t BCB: 7;
//	    uint32_t BCG: 7;
//	    uint32_t BCR: 7;
#endif /* TLC5971_H_ */
