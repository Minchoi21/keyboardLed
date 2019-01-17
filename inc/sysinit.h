/*
 * initStmDev.h
 *
 *  Created on: 27.11.2018
 *      Author: Daniel
 */

#ifndef SYSINIT_H_
#define SYSINIT_H_

/* Includes ------------------------------------------------------------------*/
#include <stmeval_led.h>
#include "flash.h"
#include "rcc.h"
#include "nvic.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SYS_TICK_DELAY 1000
#define SYS_TICK_DELAY_2 200
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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
