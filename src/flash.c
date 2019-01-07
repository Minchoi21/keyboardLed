/*
 * flash.c
 *
 *  Created on: 27.11.2018
 *      Author: Daniel
 */

/* Includes ------------------------------------------------------------------*/
#include "flash.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void FLASH_init(void) {
	/* Flash settings (see RM0090 rev9, p80) */
	FLASH->ACR =
	            FLASH_ACR_LATENCY_5WS               /* 6 CPU cycle wait */
	          | FLASH_ACR_PRFTEN                    /* enable prefetch */
	          | FLASH_ACR_ICEN                      /* instruction cache enable */
	          | FLASH_ACR_DCEN;                     /* data cache enable */
}

