/*
 * dma.h
 *
 *  Created on: 08.01.2019
 *      Author: Daniel
 */

#ifndef DMA_H_
#define DMA_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* DMA1 preemption priority */
#ifndef DMA1_NVIC_PREEMPTION_PRIORITY
#define DMA1_NVIC_PREEMPTION_PRIORITY   0x01
#endif

/* DMA2 preemption priority */
#ifndef DMA2_NVIC_PREEMPTION_PRIORITY
#define DMA2_NVIC_PREEMPTION_PRIORITY   0x01
#endif
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*!
 * @brief  Initializes the selected DMA Streams.
 * @warning none
 * @param	none
 * @return 	none
 */
void DMA_init(void);

/*!
 * @brief  Deinitializes the selected DMA Streams
 * @warning none
 * @param  	none
 * @return 	none
 */
void DMA_deinit(void);


#endif /* DMA_H_ */
