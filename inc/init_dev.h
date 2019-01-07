/*
 * initStmDev.h
 *
 *  Created on: 27.11.2018
 *      Author: Daniel
 */

#ifndef INIT_DEV_H_
#define INIT_DEV_H_

/* Includes ------------------------------------------------------------------*/
#include <stmeval_led.h>
#include "flash.h"
#include "rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SYS_TICK_DELAY 1000
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void DEV_init(void);
/* Private functions ---------------------------------------------------------*/

#endif /* INIT_DEV_H_ */
