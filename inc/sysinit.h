/*
 * initStmDev.h
 *
 *  Created on: 27.11.2018
 *      Author: Daniel
 */

#ifndef SYSINIT_H_
#define SYSINIT_H_

/* Includes ------------------------------------------------------------------*/
#include "def.h"
#include <stmeval_led.h>
#include "flash.h"
#include "rcc.h"
#include "nvic.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SYS_TICK_DELAY_1 1000
#define SYS_TICK_DELAY_2 500
#define SYS_TICK_DELAY_3 20

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
BOOL SysTick_time1_flag;
BOOL SysTick_time2_flag;
BOOL SysTick_time3_flag;

/* Private function prototypes -----------------------------------------------*/

/*!
 * @fcn SYS_init
 * @brief   Initialize configured peripherals, Initializes the Flash interface, RCC and the Systick
 * @warning none
 * @param  	none
 * @return 	none
 */
void SYS_init(void);
/* Private functions ---------------------------------------------------------*/

#endif /* SYSINIT_H_ */
