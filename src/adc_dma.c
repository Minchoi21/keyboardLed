/*
 * adc_dma.c
 *
 *  Created on: 04.02.2019
 *      Author: Daniel
 */


/* Includes ------------------------------------------------------------------*/
#include "adc_dma.h"

/* Typedef -----------------------------------------------------------*/

/* Define ------------------------------------------------------------*/
/* Macro -------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/
/* Functions ---------------------------------------------------------*/

void ADC_DMA_init(ADC_TypeDef* ADCx, uint16_t* RX_Buffer)
{
	/* Initializes the given ADC */
	ADC_init(ADCx);

	/* Clear configuration of DMAx Streamx */
	DMA_deinit(DMA2_Stream0);

	st_dma_flags.adc_dma_tcmpl = FALSE;

	/* Configure DMAx Streamx for ADCx */
	DMA2_Stream0->CR &= ~(DMA_SxCR_CHSEL_Msk);                            //!< Channel 0 selected (ADC1)
	DMA2_Stream0->CR |= (1U << DMA_SxCR_PL_Pos);                          //!< Priority level (Medium)
	DMA2_Stream0->CR |= (1U << DMA_SxCR_MSIZE_Pos);                       //!< Memory data size: half-word (16-bit)
	DMA2_Stream0->CR |= (1U << DMA_SxCR_PSIZE_Pos);                       //!< Peripheral data size: half-word (16-bit)
	DMA2_Stream0->CR |= (1U << DMA_SxCR_MINC_Pos);                        //!< Memory address pointer is increment after each data transfer
	DMA2_Stream0->CR |= (1U << DMA_SxCR_CIRC_Pos);                        //!< Circular mode enabled
	DMA2_Stream0->CR |= (1U << DMA_SxCR_TCIE_Pos);                        //!< Transfer complete interrupt enable
	DMA2_Stream0->CR |= (1U << DMA_SxCR_TEIE_Pos);                        //!< Transfer error interrupt enable
	DMA2_Stream0->CR |= (1U << DMA_SxCR_DMEIE_Pos);                       //!< Transfer direction mode error interrupt enable

	DMA2_Stream0->NDTR = ADC_NUMBER_CHANNELS;                             //!< Number of data items to be transferred
	DMA2_Stream0->PAR = (uint32_t)(&ADCx->DR);                            //!< Peripheral address register
	DMA2_Stream0->M0AR = (uint32_t)RX_Buffer;           				  //!< Memory address register
	DMA2_Stream0->CR |= (DMA_SxCR_EN);                                    //!< Stream Enable

	ADCx->CR2 |= ADC_CR2_ADON;				//!< Enable ADC
}
