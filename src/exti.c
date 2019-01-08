/*
 * exti.c
 *
 *  Created on: 03.12.2018
 *      Author: Daniel
 */

/* Includes ------------------------------------------------------------------*/
#include "exti.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void EXTI_init(uint16_t EXTI_line, EXTITrigger_TypeDef trigger)
{

	/* Clear EXTI line configuration */
	EXTI->IMR &= ~EXTI_line;
	EXTI->EMR &= ~EXTI_line;

	/* Clear Rising Falling edge configuration */
	EXTI->RTSR &= ~EXTI_line;
	EXTI->FTSR &= ~EXTI_line;

	/* Select the trigger for the selected external interrupts */
	if (trigger == EXTI_Trigger_Rising_Falling)
	{
	  /* Rising Falling edge */
		EXTI->RTSR |= EXTI_line;
		EXTI->FTSR |= EXTI_line;
	}
	else if (trigger == EXTI_Trigger_Falling)
	{
		/* Falling edge */
		EXTI->FTSR |= EXTI_line;
	}
	else if (trigger == EXTI_Trigger_Rising)
	{
		/* Rising edge */
		EXTI->RTSR |= EXTI_line;
	}

	/* Rising trigger selection */
//	EXTI->RTSR |= (1 << GPIO_Pin);
	/* Falling trigger selection */
//	EXTI->FTSR |= (1 << GPIO_Pin);
	/* Interrupt Mask */
	EXTI->IMR |= EXTI_line;
}

/* Deinitializes the EXTI peripheral registers to their default reset values. */
void EXTI_deinit(void)
{
  EXTI->IMR = 0x00000000;
  EXTI->EMR = 0x00000000;
  EXTI->RTSR = 0x00000000;
  EXTI->FTSR = 0x00000000;
  EXTI->PR = 0x007FFFFF;
}
