/*
 * tlc5971.h
 *
 *  Created on: 04.12.2018
 *      Author: Daniel
 */

#ifndef TLC5971_H_
#define TLC5971_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "spi.h"
#include <math.h>

/* Private define ------------------------------------------------------------*/
/******************** Channel Bit definition for LED Driver  ********************/
#define LED_CH_NU1                          	0x0001U       /*!<Led not used */
#define LED_CH_NU2                          	0x0002U       /*!<Led not used */
#define LED_CH_NU3                          	0x0004U       /*!<Led not used */
#define LED_CH_SI                        		0x0008U       /*!<Led first series */
#define LED_CH_LS                         		0x0010U       /*!<Led length series */
#define LED_CH_PWR                          	0x0020U       /*!<Led power voltage */
#define LED_CH_SII                          	0x0040U       /*!<Led second series */
#define LED_CH_SIII                          	0x0080U       /*!<Led third series */
#define LED_CH_SIV                          	0x0100U       /*!<Led fourth series */
#define LED_CH_SM                          		0x0200U       /*!<Led serial mode */
#define LED_CH_CM                          		0x0400U       /*!<Led continuous mode */
#define LED_CH_MOD                          	0x0800U       /*!<Led fire mode */

#define LED_CLR_ALL_MASK						0x0000U
#define LED_SET_ALL_MASK						0x0FFFU
#define LED_SERIES_MASK							( 0x0008U + 0x0040U + 0x0080U + 0x0100U )
#define LED_MODE_MASK							( 0x0200U + 0x0400U )

#define TLC5971_NUM_LED 						12			// number of Channel OUTxx
#define TLC5971_PAC_LEN							28			// the length of the message sent to the TLC5971 using SPI

#define TLC5971_SET_LED(led)					TLC5971_set_led(led)
#define TLC5971_CLR_LED(led)					TLC5971_clr_led(led)

#define TLC5971_SET_LED_ALL()					TLC5971_set_led_all()
#define TLC5971_CLR_LED_ALL()					TLC5971_clr_led_all()

#define TLC5971_SEND_PACKET(spix)				TLC5971_send_packet(spix)


//#define TLC5971_SPI_CLK_L				(GPIOA->ODR &= ~GPIO_ODR_ODR_5)
//#define TLC5971_SPI_CLK_H				(GPIOA->ODR |= GPIO_ODR_ODR_5)
//
//#define TLC5971_SPI_D_L				(GPIOA->ODR &= ~GPIO_ODR_ODR_7)
//#define TLC5971_SPI_D_H				(GPIOA->ODR |= GPIO_ODR_ODR_7)

/* Private typedef -----------------------------------------------------------*/
typedef enum {
	TLC5971_OutR0,
	TLC5971_OutG0,
	TLC5971_OutB0,
	TLC5971_OutR1,
	TLC5971_OutG1,
	TLC5971_OutB1,
	TLC5971_OutR2,
	TLC5971_OutG2,
	TLC5971_OutB2,
	TLC5971_OutR3,
	TLC5971_OutG3,
	TLC5971_OutB3
} en_TLC5971_Channel_t;

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
//----------------------------------------------------------------------------------------------------~ ~ ~ ~ ~ ~ ~ ~ ~-------------------------------------
//|		CF[0]   |	  CF[1]	  |	    CF[2]    |   CF[3]      |    GS[0]   |    GS[1]   |    GS[2]   |    GS[3-8]     |    GS[9]   |   GS[10]   |   GS[11]   |
//|	  1byte	    |	 1byte    |	   1byte     |	  1byte     |  2 x 1byte |  2 x 1byte |  2 x 1byte |  12 x 1byte    |  2 x 1byte |  2 x 1byte |  2 x 1byte |
//----------------------------------------------------------------------------------------------------~ ~ ~ ~ ~ ~ ~ ~ ~-------------------------------------
//|   CMD    |    FC    |  BC RED   |  BC GREEN |  BC BLUE  |  GS OUTB3  |  GS OUTG3  |  GS OUTR3  |       ...      |  GS OUTB0  |  GS OUTG0  |  GS OUTR0  |
//|  6bits   |  5bits   |   7bits	|   7bits 	|   7bits	|   16bits   |   16bits   |   16bits   |    6x16Bits    |   16bits   |   16bits   |   16bits   |
//----------------------------------------------------------------------------------------------------~ ~ ~ ~ ~ ~ ~ ~ ~-------------------------------------
//  100101      10010      1111111     1111111     1111111     Channel_1    Channel_2    Channel_3     Channel_4-9    Channel_10   Channel_11   Channel_12
//	10010110      01011111		 11111111		11111111

typedef struct TLC5971_pac {
uint8_t CF[4];					// 32 bits driver configuration
uint16_t GS[TLC5971_NUM_LED];   // 12 -> number of channels. Takes values from 0 - 65535
}st_tlc5971_pac_t;


typedef struct TLC5971 {
st_tlc5971_pac_t PAC;	// LED data packet configuration
uint16_t LDS;			// LED data status
uint16_t luminosity;	// LED brightness
} st_tlc5971_t;




/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void TLC5971_init( void );
void TLC5971_set_led( uint16_t led );
void TLC5971_set_led_all( void );
void TLC5971_clr_led( uint16_t led );
void TLC5971_clr_led_all( void );
void TLC5971_set_luminosity( uint16_t lum );
void TLC5971_send_packet( SPI_TypeDef* SPIx );

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
