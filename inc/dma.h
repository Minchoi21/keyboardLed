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

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/

/* DMA definition for interrupt flags */
#define DMA_FLAG_TCIF    ((uint32_t)0x00000020) /*!< DMA stream transfer complete */
#define DMA_FLAG_HTIF    ((uint32_t)0x00000010) /*!< DMA stream half transfer complete */
#define DMA_FLAG_TEIF    ((uint32_t)0x00000008) /*!< DMA stream transfer error */
#define DMA_FLAG_DMEIF   ((uint32_t)0x00000004) /*!< DMA stream direct mode error */
#define DMA_FLAG_FEIF    ((uint32_t)0x00000001) /*!< DMA stream FIFO error */
#define DMA_FLAG_ALL     ((uint32_t)0x0000003D) /*!< DMA stream all flags */

/* DMA1 preemption priority */
#ifndef DMA1_NVIC_PREEMPTION_PRIORITY
#define DMA1_NVIC_PREEMPTION_PRIORITY   0x01
#endif

/* DMA2 preemption priority */
#ifndef DMA2_NVIC_PREEMPTION_PRIORITY
#define DMA2_NVIC_PREEMPTION_PRIORITY   0x01
#endif

#define DMA_Channel_0                     ((uint32_t)0x00000000)
#define DMA_Channel_1                     ((uint32_t)0x02000000)
#define DMA_Channel_2                     ((uint32_t)0x04000000)
#define DMA_Channel_3                     ((uint32_t)0x06000000)
#define DMA_Channel_4                     ((uint32_t)0x08000000)
#define DMA_Channel_5                     ((uint32_t)0x0A000000)
#define DMA_Channel_6                     ((uint32_t)0x0C000000)
#define DMA_Channel_7                     ((uint32_t)0x0E000000)

/* Macro -------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
/* Functions ---------------------------------------------------------*/
/*!
 * @brief  	Clears selected DMA interrupt flag
 * @warning none
 * @param  *DMAy_Streamx: Pointer to @ref DMA_Stream_TypeDef DMA stream where you want to clear flags
 * 			where y can be 1 or 2 to select the DMA and x can be 0 to 7 to select the DMA Stream.
 * @param  flags: Flag(s) which you wanna clear:
 *           - DMA_FLAG_TCIF: Transfer complete interrupt flag
 *           - DMA_FLAG HTIF: Half transfer complete interrupt flag
 *           - DMA_FLAG_TEIF: Transfer error interrupt flag
 *           - DMA_FLAG_DMEIF: Direct mode error interrupt flag
 *           - DMA_FLAG_FEIF: FIFO error interrupt flag
 *           - DMA_FLAG_ALL: All flags
 * @return 	none
 */
void DMA_clearFlag(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t flags);

/*!
 * @brief  	Initializes the selected DMA Stream and Channel.
 * @warning none
 * @param	*DMAy_Streamx: Pointer to @ref DMA_Stream_TypeDef DMA stream which you want initialize
 * 			where y can be 1 or 2 to select the DMA and x can be 0 to 7 to select the DMA Stream.
 * @param  	channel: Select DMA channel for your SPI in specific DMA Stream.
 * 			This parameter can be a value of @ref DMA_Channel_x definitions.
 * @return 	none
 */
void DMA_init(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t channel);

/*!
 * @brief  	Deinitializes the selected DMA Streams
 * @warning none
 * @param	DMAy_Streamx: where y can be 1 or 2 to select the DMA and x can be 0
 *         	to 7 to select the DMA Stream.
 * @return 	none
 */
void DMA_deinit(DMA_Stream_TypeDef* DMAy_Streamx);


#endif /* DMA_H_ */
