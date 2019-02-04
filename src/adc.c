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
		RCC_ADC3_CLK_ENABLE;
	}

	RCC_DMA2_CLK_ENABLE;

	GPIO_init(GPIOB, GPIO_Pin_0, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Low);

	/* INTERUPTS CONFIGURE SECTION */
	ADCx->CR1 |= (1U << ADC_CR1_OVRIE_Pos);               //!< Enable overrun interrupt
	/* ---INTERUPTS CONFIGURE END--- */

	/* DMA SECTION */
	ADCx->CR2 |= (1U << ADC_CR2_DMA_Pos);                 //!< Enable DMA module
	ADCx->CR2 |= (1U << ADC_CR2_DDS_Pos);                 //!< DMA requests are issued as long as data are converted
	/* DMA END */

	/* SAMPLING TIME SECTION */
	ADCx->SMPR1 |= (2U << ADC_SMPR1_SMP17_Pos);           //!< Set 15 cycles sampling time on ADC-ref channel
	ADCx->SMPR2 |= (2U << ADC_SMPR2_SMP1_Pos);            //!< Set 15 cycles sampling time on ADC-1 channel
	ADCx->SMPR2 |= (2U << ADC_SMPR2_SMP2_Pos);            //!< Set 15 cycles sampling time on ADC-2 channel
	/* ---SAMPLING TIME END--- */

	/* OTHER CONFIGURE SECTION */
	ADCx->CR1 |= (1U << ADC_CR1_SCAN_Pos);                //!< Enable scan mode
	ADCx->SQR1 |= (2U << ADC_SQR1_L_Pos);                 //!< Regular channel sequence length (3 conversion length)
	/* ---OTHER CONFIGURE END--- */

	/* SCANING SEQUENCE SECTION */
	ADCx->SQR3 |= (1U << ADC_SQR3_SQ1_Pos);               //!< First channel 1 (PA-1)
	ADCx->SQR3 |= (2U << ADC_SQR3_SQ2_Pos);               //!< Second channel 2 (PA-2)
	ADCx->SQR3 |= (17U << ADC_SQR3_SQ3_Pos);              //!< Third channel 17 (Vref)
	/* ---SCANING SEQUENCE END--- */

	/* POWER SECTION */
	ADC->CCR |= (1U << ADC_CCR_TSVREFE_Pos);              //!< Enable temperature sensor end Vref
	ADCx->CR2 |= (1U << ADC_CR2_ADON_Pos);                //!< Enable ADC
	/* ---POWER END--- */


}
