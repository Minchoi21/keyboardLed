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
void EXTI_init(uint16_t EXTI_line, EXTITrigger_TypeDef trigger);
void EXTI_DeInit(void);

#endif /* EXTI_H_ */
