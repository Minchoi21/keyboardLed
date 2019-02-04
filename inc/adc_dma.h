/*
 * adc_dma.h
 *
 *  Created on: 04.02.2019
 *      Author: Daniel
 */

#ifndef ADC_DMA_H_
#define ADC_DMA_H_


/* Includes ------------------------------------------------------------------*/
#include "def.h"
#include "adc.h"

/* Define --------------------------------------------------------------------*/
#define V_REFIN_CAL (*(uint16_t*)0x1FFF7A2A)
#define V_MEASURMENT_CONDITIONS 3300
#define ADC_RESOLUTION 4095 				//12-bit

#define ADC_QUANTITY_CHANNELS           3U
#define ADC_QUANTITY_REF_CHANNEL        1U

#define ADC_CH1_POS                     0U
#define ADC_CH2_POS                     1U
#define ADC_REF                         2U

/* Typedef -------------------------------------------------------------------*/
/* Macro ---------------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function prototypes -------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/

/*!
 * @brief  Initializes ADC peripheral DMA.
 * @note   This function initializes RX DMA streams for ADCx.
 * @note   ADC HAVE TO be previously initialized using @ref ADC library.
 * @param  *ADCx: Pointer to ADC peripheral where you want to enable DMA.
 * @return none
 */
void ADC_DMA_init(ADC_TypeDef* ADCx);



#endif /* ADC_DMA_H_ */
