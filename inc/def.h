/*
 * def.h
 *
 *  Created on: 08.01.2019
 *      Author: Daniel
 */

#ifndef DEF_H_
#define DEF_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <math.h>


/* Private typedef -----------------------------------------------------------*/

union value_short {
	uint16_t val;
	uint8_t arr[2];
};

union value_float {
	float val;
	uint8_t arr[4];
};

/* Private define ------------------------------------------------------------*/

#ifndef __cplusplus
#define NULL ((void *)0)
#else   /* C++ */
#define NULL 0
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


#endif /* DEF_H_ */
