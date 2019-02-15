/*
 * adc.c
 *
 *  Created on: 04.02.2019
 *      Author: Daniel
 */


/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "stdlib.h"

/* Typedef -----------------------------------------------------------*/

/* Define ------------------------------------------------------------*/
/* Macro -------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
st_ADC_measure_t st_adc_measure;
/* Function prototypes -----------------------------------------------*/

/* Private functions -------------------------------------------------*/
void ADC_initChannel_0(ADC_TypeDef* ADCx);
void ADC_initChannel_1(ADC_TypeDef* ADCx);
void ADC_initChannel_2(ADC_TypeDef* ADCx);
void ADC_initChannel_3(ADC_TypeDef* ADCx);
void ADC_initChannel_4(ADC_TypeDef* ADCx);
void ADC_initChannel_5(ADC_TypeDef* ADCx);
void ADC_initChannel_6(ADC_TypeDef* ADCx);
void ADC_initChannel_7(ADC_TypeDef* ADCx);
void ADC_initChannel_8(ADC_TypeDef* ADCx);
void ADC_initChannel_9(ADC_TypeDef* ADCx);
void ADC_initChannel_10(ADC_TypeDef* ADCx);
void ADC_initChannel_11(ADC_TypeDef* ADCx);
void ADC_initChannel_12(ADC_TypeDef* ADCx);
void ADC_initChannel_13(ADC_TypeDef* ADCx);
void ADC_initChannel_14(ADC_TypeDef* ADCx);
void ADC_initChannel_15(ADC_TypeDef* ADCx);

/* Functions ---------------------------------------------------------*/

void ADC_init(ADC_TypeDef* ADCx, en_ADC_Channel_t channel)
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

	/* Configure GPIO for ADC Channel */
	ADC_initChannel(ADCx, channel);

	ADCx->CR2 &= ~ADC_CR2_ADON;							//!< Disable ADCx
	ADCx->CR1 |= (ADC_RESOLUTION_12b << ADC_CR1_RES_Pos);				//!< Set 10bit resolution

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

void ADC_initChannel(ADC_TypeDef* ADCx, en_ADC_Channel_t channel) {

	if (channel == ADC_CHANNEL_0) {
		ADC_initChannel_0(ADCx);
	} else if (channel == ADC_CHANNEL_1) {
		ADC_initChannel_1(ADCx);
	} else if (channel == ADC_CHANNEL_2) {
		ADC_initChannel_2(ADCx);
	} else if (channel == ADC_CHANNEL_3) {
		ADC_initChannel_3(ADCx);
	} else if (channel == ADC_CHANNEL_4) {
		ADC_initChannel_4(ADCx);
	} else if (channel == ADC_CHANNEL_5) {
		ADC_initChannel_5(ADCx);
	} else if (channel == ADC_CHANNEL_6) {
		ADC_initChannel_6(ADCx);
	} else if (channel == ADC_CHANNEL_7) {
		ADC_initChannel_7(ADCx);
	} else if (channel == ADC_CHANNEL_8) {
		ADC_initChannel_8(ADCx);
	} else if (channel == ADC_CHANNEL_9) {
		ADC_initChannel_9(ADCx);
	} else if (channel == ADC_CHANNEL_10) {
		ADC_initChannel_10(ADCx);
	} else if (channel == ADC_CHANNEL_11) {
		ADC_initChannel_11(ADCx);
	} else if (channel == ADC_CHANNEL_12) {
		ADC_initChannel_12(ADCx);
	} else if (channel == ADC_CHANNEL_13) {
		ADC_initChannel_13(ADCx);
	} else if (channel == ADC_CHANNEL_14) {
		ADC_initChannel_14(ADCx);
	} else if (channel == ADC_CHANNEL_15) {
		ADC_initChannel_15(ADCx);
	}
}


void ADC_startConv(ADC_TypeDef* ADCx)
{
	ADCx->CR2 |= (1U << ADC_CR2_SWSTART_Pos);
}

void ADC_initAverageStructure(void)
{
	st_adc_measure.st_avg.num_samples = 0;
	st_adc_measure.st_avg.data_ready = FALSE;
	for(uint8_t i = 0; i < ADC_QUANTITY_CHANNEL; i++) {
		st_adc_measure.st_avg.avg_val[i] = 0;
		for(uint8_t j = 0; j < ADC_QUANTITY_SAMPLES; j++) {
			st_adc_measure.st_avg.samples_sort[i][j] = 0;
			st_adc_measure.st_avg.samples[i][j] = 0;
		}
	}
}

void ADC_acquisitionData(void)
{
	for(uint8_t i = 0; i < ADC_QUANTITY_CHANNEL; i++) {
		st_adc_measure.st_avg.samples[i][st_adc_measure.st_avg.num_samples] = st_adc_measure.raw_data[i];
	}
	if((++st_adc_measure.st_avg.num_samples) >= ADC_QUANTITY_SAMPLES ) {
		st_adc_measure.st_avg.num_samples = 0;
	}
}

int comp (const void * elem1, const void * elem2)
{
    uint16_t f = *((uint16_t*)elem1);
    uint16_t s = *((uint16_t*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

void ADC_averageFunction(void)
{
	/* Copy raw samples into the median filtration table */
	for(uint8_t y = 0; y < ADC_QUANTITY_CHANNEL; y++) {
		for(uint8_t z = 0; z < ADC_QUANTITY_SAMPLES; z++) {
			st_adc_measure.st_avg.samples_sort[y][z] = st_adc_measure.st_avg.samples[y][z];
		}
	}

	/* Calculate mediane */
	for(uint8_t i = 0; i < ADC_QUANTITY_CHANNEL; i++) {
		qsort(st_adc_measure.st_avg.samples_sort[i],
				sizeof(st_adc_measure.st_avg.samples_sort[i]) / sizeof(*(st_adc_measure.st_avg.samples_sort[i])),
				sizeof(*(st_adc_measure.st_avg.samples_sort[i])),
				comp);

		if((st_adc_measure.st_avg.avg_val[i] > (st_adc_measure.st_avg.samples_sort[i][(ADC_QUANTITY_SAMPLES)/2] / 8))
				&& ((st_adc_measure.st_avg.samples_sort[i][(ADC_QUANTITY_SAMPLES)/2] % 8) < HYST_HIGH_LEVEL)) {
			st_adc_measure.st_avg.avg_val[i] = ((st_adc_measure.st_avg.samples_sort[i][(ADC_QUANTITY_SAMPLES)/2]) / 8);
		} else if((st_adc_measure.st_avg.avg_val[i] < (st_adc_measure.st_avg.samples_sort[i][(ADC_QUANTITY_SAMPLES)/2] / 8))
				&& ((st_adc_measure.st_avg.samples_sort[i][(ADC_QUANTITY_SAMPLES)/2] % 8) > HYST_LOW_LEVEL)) {
			st_adc_measure.st_avg.avg_val[i] = ((st_adc_measure.st_avg.samples_sort[i][(ADC_QUANTITY_SAMPLES)/2]) / 8);
		}

/*
//		if(st_adc_measure.st_avg.avg_val[i] <= 1) {
//			st_adc_measure.st_avg.avg_val[i] = 0;
//		}
*/
	}
}

st_ADC_measure_t* ADC_accessAdcMeasure(void)
{
	return &st_adc_measure;
}


/* Private functions */
void ADC_initChannel_0(ADC_TypeDef* ADCx) {
	/* Configure Port and Pins for ADC Channels */
	GPIO_init(GPIOA, GPIO_Pin_0, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
}

void ADC_initChannel_1(ADC_TypeDef* ADCx) {
	/* Configure Port and Pins for ADC Channels */
	GPIO_init(GPIOA, GPIO_Pin_1, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
}

void ADC_initChannel_2(ADC_TypeDef* ADCx) {
	/* Configure Port and Pins for ADC Channels */
	GPIO_init(GPIOA, GPIO_Pin_2, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
}

void ADC_initChannel_3(ADC_TypeDef* ADCx) {
	/* Configure Port and Pins for ADC Channels */
	GPIO_init(GPIOA, GPIO_Pin_3, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
}

void ADC_initChannel_4(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		/* Configure Port and Pins for ADC Channels */
		GPIO_init(GPIOA, GPIO_Pin_4, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
	}
	if (ADCx == ADC3) {
		#if defined(GPIOF)
			/* Configure Port and Pins for ADC Channels */
			GPIO_init(GPIOF, GPIO_Pin_6, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
		#endif
	}
}

void ADC_initChannel_5(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		/* Configure Port and Pins for ADC Channels */
		GPIO_init(GPIOA, GPIO_Pin_5, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
	}
	if (ADCx == ADC3) {
		#if defined(GPIOF)
			/* Configure Port and Pins for ADC Channels */
			GPIO_init(GPIOF, GPIO_Pin_7, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
		#endif
	}
}

void ADC_initChannel_6(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		/* Configure Port and Pins for ADC Channels */
		GPIO_init(GPIOA, GPIO_Pin_6, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
	}
	if (ADCx == ADC3) {
		#if defined(GPIOF)
			/* Configure Port and Pins for ADC Channels */
			GPIO_init(GPIOF, GPIO_Pin_8, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
		#endif
	}
}

void ADC_initChannel_7(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		/* Configure Port and Pins for ADC Channels */
		GPIO_init(GPIOA, GPIO_Pin_7, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
	}
	if (ADCx == ADC3) {
		#if defined(GPIOF)
			/* Configure Port and Pins for ADC Channels */
			GPIO_init(GPIOF, GPIO_Pin_9, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
		#endif
	}
}

void ADC_initChannel_8(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		/* Configure Port and Pins for ADC Channels */
		GPIO_init(GPIOB, GPIO_Pin_0, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
	}
	if (ADCx == ADC3) {
		#if defined(GPIOF)
			/* Configure Port and Pins for ADC Channels */
			GPIO_init(GPIOF, GPIO_Pin_10, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
		#endif
	}
}

void ADC_initChannel_9(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		/* Configure Port and Pins for ADC Channels */
		GPIO_init(GPIOB, GPIO_Pin_1, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
	}
	if (ADCx == ADC3) {
		#if defined(GPIOF)
			/* Configure Port and Pins for ADC Channels */
			GPIO_init(GPIOF, GPIO_Pin_3, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
		#endif
	}
}

void ADC_initChannel_10(ADC_TypeDef* ADCx) {
	/* Configure Port and Pins for ADC Channels */
	GPIO_init(GPIOC, GPIO_Pin_0, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
}

void ADC_initChannel_11(ADC_TypeDef* ADCx) {
	/* Configure Port and Pins for ADC Channels */
	GPIO_init(GPIOC, GPIO_Pin_1, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
}

void ADC_initChannel_12(ADC_TypeDef* ADCx) {
	/* Configure Port and Pins for ADC Channels */
	GPIO_init(GPIOC, GPIO_Pin_2, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
}

void ADC_initChannel_13(ADC_TypeDef* ADCx) {
	/* Configure Port and Pins for ADC Channels */
	GPIO_init(GPIOC, GPIO_Pin_3, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
}

void ADC_initChannel_14(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		/* Configure Port and Pins for ADC Channels */
		GPIO_init(GPIOC, GPIO_Pin_4, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
	}
	if (ADCx == ADC3) {
		#if defined(GPIOF)
			/* Configure Port and Pins for ADC Channels */
			GPIO_init(GPIOF, GPIO_Pin_4, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
		#endif
	}
}

void ADC_initChannel_15(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		/* Configure Port and Pins for ADC Channels */
		GPIO_init(GPIOC, GPIO_Pin_5, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
	} else if (ADCx == ADC3) {
		#if defined(GPIOF)
			/* Configure Port and Pins for ADC Channels */
			GPIO_init(GPIOF, GPIO_Pin_5, GPIO_Mode_AN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast);
		#endif
	}
}
