/*
 * gpio.h
 *
 *  Created on: 28.11.2018
 *      Author: Daniel
 */

#ifndef GPIO_H_
#define GPIO_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Private typedef -----------------------------------------------------------*/
/*!
 * @brief GPIO Mode enumeration
 */
typedef enum {
	GPIO_Mode_IN 	= 0x00,  	/*!< GPIO Pin as General Purpose Input */
	GPIO_Mode_OUT 	= 0x01, 	/*!< GPIO Pin as General Purpose Output */
	GPIO_Mode_AF 	= 0x02,  	/*!< GPIO Pin as Alternate Function */
	GPIO_Mode_AN	= 0x03  	/*!< GPIO Pin as Analog */
} GPIO_Mode_t;

/*!
 * @brief GPIO Output type enumeration
 */
typedef enum {
	GPIO_OType_PP 	= 0x00, 	/*!< GPIO Output Type Push-Pull */
	GPIO_OType_OD 	= 0x01  	/*!< GPIO Output Type Open-Drain */
} GPIO_OType_t;

/*!
 * @brief  GPIO Speed enumeration
 */
typedef enum {
	GPIO_Speed_Low 		= 0x00,    	/*!< GPIO Speed Low */
	GPIO_Speed_Medium 	= 0x01, 	/*!< GPIO Speed Medium */
	GPIO_Speed_Fast 	= 0x02,   	/*!< GPIO Speed Fast */
	GPIO_Speed_High 	= 0x03    	/*!< GPIO Speed High */
} GPIO_Speed_t;

/*!
 * @brief GPIO pull resistors enumeration
 */
typedef enum {
	GPIO_PuPd_NOPULL 	= 0x00, 	/*!< No pull resistor */
	GPIO_PuPd_UP 		= 0x01,     /*!< Pull up resistor enabled */
	GPIO_PuPd_DOWN 		= 0x02    	/*!< Pull down resistor enabled */
} GPIO_PuPd_t;

/*!
 * @brief GPIO alternate function enumeration
 */
typedef enum {
	GPIO_AF_0 		= 0x00, 	/*!< Alternate function 0 */
	GPIO_AF_1 		= 0x01,     /*!< Alternate function 1 */
	GPIO_AF_2 		= 0x02,    	/*!< Alternate function 2 */
	GPIO_AF_3 		= 0x03, 	/*!< Alternate function 3 */
	GPIO_AF_4 		= 0x04,     /*!< Alternate function 4 */
	GPIO_AF_5 		= 0x05,    	/*!< Alternate function 5 */
	GPIO_AF_6 		= 0x06, 	/*!< Alternate function 6 */
	GPIO_AF_7 		= 0x07,     /*!< Alternate function 7 */
	GPIO_AF_8 		= 0x08,    	/*!< Alternate function 8 */
	GPIO_AF_9 		= 0x09, 	/*!< Alternate function 9 */
	GPIO_AF_10 		= 0x0A,     /*!< Alternate function 10 */
	GPIO_AF_11 		= 0x0B,    	/*!< Alternate function 11 */
	GPIO_AF_12 		= 0x0C, 	/*!< Alternate function 12 */
	GPIO_AF_13 		= 0x0D,     /*!< Alternate function 13 */
	GPIO_AF_14 		= 0x0E,    	/*!< Alternate function 14 */
	GPIO_AF_15 		= 0x0F    	/*!< Alternate function 15 */
} GPIO_AlternateFcn_t;



/* Private define ------------------------------------------------------------*/
#ifndef GPIO_Pin_0
#define GPIO_Pin_0		((uint16_t)0x0001)
#define GPIO_Pin_1		((uint16_t)0x0002)
#define GPIO_Pin_2		((uint16_t)0x0004)
#define GPIO_Pin_3		((uint16_t)0x0008)
#define GPIO_Pin_4		((uint16_t)0x0010)
#define GPIO_Pin_5		((uint16_t)0x0020)
#define GPIO_Pin_6		((uint16_t)0x0040)
#define GPIO_Pin_7		((uint16_t)0x0080)
#define GPIO_Pin_8		((uint16_t)0x0100)
#define GPIO_Pin_9		((uint16_t)0x0200)
#define GPIO_Pin_10		((uint16_t)0x0400)
#define GPIO_Pin_11		((uint16_t)0x0800)
#define GPIO_Pin_12		((uint16_t)0x1000)
#define GPIO_Pin_13		((uint16_t)0x2000)
#define GPIO_Pin_14		((uint16_t)0x4000)
#define GPIO_Pin_15		((uint16_t)0x8000)
#define GPIO_Pin_All	((uint16_t)0xFFFF)
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint16_t GPIO_getPinSource(uint16_t GPIO_Pin);
uint16_t GPIO_getPortSource(GPIO_TypeDef* GPIOx);
void GPIO_enableClock(GPIO_TypeDef* GPIOx);
void GPIO_disableClock(GPIO_TypeDef* GPIOx);
void GPIO_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_Mode_t GPIO_Mode, GPIO_OType_t GPIO_OType, GPIO_PuPd_t GPIO_PuPd, GPIO_Speed_t GPIO_Speed);
void GPIO_initAlternate(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_OType_t GPIO_OType, GPIO_PuPd_t GPIO_PuPd, GPIO_Speed_t GPIO_Speed, GPIO_AlternateFcn_t GPIO_Alternate);
void GPIO_setPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_resetPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_togglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/* Private functions ---------------------------------------------------------*/

#endif /* GPIO_H_ */
