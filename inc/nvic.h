/*
 * nvic.h
 *
 *  Created on: 04.01.2019
 *      Author: Daniel
 */

#ifndef NVIC_H_
#define NVIC_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*!
 * @brief  Initialize NVIC for GPIO, EXTI, SPI, DMA
 * @warning none
 * @param  	none
 * @return 	none
 */
void NVIC_init(void);

/*!
 * @brief  Deinitialization NVIC
 * @warning none
 * @param  	none
 * @return 	none
 */
void NVIC_DeInit(void);

#endif /* NVIC_H_ */
