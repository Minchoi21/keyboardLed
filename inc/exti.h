/*
 * exti.h
 *
 *  Created on: 03.12.2018
 *      Author: Daniel
 */

#ifndef EXTI_H_
#define EXTI_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
 * Initializes the EXTI peripheral according to the specified parameters send to the function.
 * @warning none
 * @param	uint16_t EXTI_Line - which EXTI line to connect (in this case the same as GPIO_pin)
 * 			EXTITrigger_TypeDef trigger - defines which edge triggers an interrupt
 * @return 	none
 */
void EXTI_init(uint16_t EXTI_line, EXTITrigger_TypeDef trigger);


void EXTI_deinit(void);

#endif /* EXTI_H_ */
