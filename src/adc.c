/*
 * adc.c
 *
 *  Created on: 04.02.2019
 *      Author: Daniel
 */


/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* Typedef -----------------------------------------------------------*/

/* Define ------------------------------------------------------------*/
/* Macro -------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/
/* Functions ---------------------------------------------------------*/

void ADC_init(ADC_TypeDef* ADCx)
{
	/* Enable DMA clock */
	if (ADCx == ADC1) {
		/* Enable ADC1 clock */
		RCC_ADC1_CLK_ENABLE;
	} else if(ADCx == ADC2) {
		/* Enable ADC2 clock */
		RCC_ADC2_CLK_ENABLE;
	} else {
		/* Enable ADC3 clock */
		RCC_ADC3_CLK_ENABLE;
	}
	/* Enable DMA2 Clock for ADC */
	RCC_DMA2_CLK_ENABLE;

	/* Configure Port and Pins for ADC Channels */
	GPIO_init(GPIOB, GPIO_Pin_0, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Low);

	ADCx->CR2 &= ~ADC_CR2_ADON;							//!< Disable ADCx
	ADCx->CR1 |= (ADC_RESOLUTION_10b << ADC_CR1_RES_Pos);				//!< Set 10bit resolution

	/* Interrupts Configure */
	ADCx->CR1 |= (1U << ADC_CR1_OVRIE_Pos);				//!< Enable overrun interrupt


	/* DMA Configure */
	ADCx->CR2 |= (1U << ADC_CR2_DMA_Pos);				//!< Enable DMA module
	ADCx->CR2 |= (1U << ADC_CR2_DDS_Pos);				//!< DMA requests are issued as long as data are converted


	/* Continuous Conversion */
	ADCx->CR2 |= (1U << ADC_CR2_CONT_Pos);				//!< Enable continuous conversion

	/* Sampling Time Section */
	ADCx->SMPR1 |= (ADC_SAMPLETIME_480CYCLES << ADC_SMPR1_SMP17_Pos);           //!< Set 112 cycles sampling time on ADC-ref channel
	ADCx->SMPR2 |= (ADC_SAMPLETIME_480CYCLES << ADC_SMPR2_SMP8_Pos);            //!< Set 112 cycles sampling time on ADCx channel 8

	/* Other Configure Section */
	ADCx->CR1 |= (1U << ADC_CR1_SCAN_Pos);				//!< Enable scan mode
	ADCx->SQR1 |= (1U << ADC_SQR1_L_Pos);				//!< Regular channel sequence length

	/* Scanning Sequence Section */
	ADCx->SQR3 |= (8U << ADC_SQR3_SQ1_Pos);				//!< First channel 8 (PB0)
	ADCx->SQR3 |= (17U << ADC_SQR3_SQ2_Pos);			//!< Second channel 17 (Vref)

	/* Power Section */
	ADC->CCR |= (1U << ADC_CCR_TSVREFE_Pos);			//!< Enable temperature sensor and Vref
	ADC->CCR |= (ADC_DIV_4 << ADC_CCR_ADCPRE_Pos);		//!< Set PCLK2 divider on 6
}

void ADC_startConv(ADC_TypeDef* ADCx)
{
	ADCx->CR2 |= (1U << ADC_CR2_SWSTART_Pos);
}
