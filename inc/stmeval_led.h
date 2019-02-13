/*
 * stmeval_gpio.h
 *
 *  Created on: 26.11.2018
 *      Author: Daniel
 */

#ifndef STMEVAL_LED_H_
#define STMEVAL_LED_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "gpio.h"
#include "exti.h"
#include "spi_dma.h"
#include "tlc5971.h"
#include "max7301.h"
#include "adc_dma.h"


/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  BUTTON_USER = 0
} Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} en_TypeDef_buttonMode_t;

/* Private define ------------------------------------------------------------*/
#define LEDn							4

#define LED_G_PIN						GPIO_Pin_12
#define LED_O_PIN						GPIO_Pin_13
#define LED_R_PIN						GPIO_Pin_14
#define LED_B_PIN						GPIO_Pin_15
#define LED_GPIO_PORT					GPIOD


#define BUTTONn                        1

#define USER_BUTTON_PIN                GPIO_Pin_0
#define USER_BUTTON_GPIO_PORT          GPIOA

#define USER_BUTTON_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOA
#define USER_BUTTON_EXTI_PIN_SOURCE    EXTI_PinSource0
#define USER_BUTTON_EXTI_IRQn          EXTI0_IRQn


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*------------------------------------------------------------------------------
Initialize the GPIO PIN as a output
*------------------------------------------------------------------------------*/
void STM_EVAL_initLed(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/*------------------------------------------------------------------------------
Initialize the LED connected to PD12, PD13, PD14, PD15
*------------------------------------------------------------------------------*/
void STM_EVAL_initAllLeds(void);

/*------------------------------------------------------------------------------
Turn On Led pin
*------------------------------------------------------------------------------*/
void STM_EVAL_ledOn(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/*------------------------------------------------------------------------------
Turn off Led pin
*------------------------------------------------------------------------------*/
void STM_EVAL_ledOff(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/*------------------------------------------------------------------------------
Switch Led pin state to the oposite
*------------------------------------------------------------------------------*/
void STM_EVAL_ledToggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/*------------------------------------------------------------------------------
Initialize the GPIO and the external interrupt
*------------------------------------------------------------------------------*/
void STM_EVAL_initButton(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/*------------------------------------------------------------------------------
Initialize the LEDs and USER BUTTON on the evaluation board DISCOVERY
*------------------------------------------------------------------------------*/
void STM_EVAL_initBoard(void);

#endif /* STMEVAL_LED_H_ */
