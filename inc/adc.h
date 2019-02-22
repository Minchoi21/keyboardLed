/*
 * adc.h
 *
 *  Created on: 04.02.2019
 *      Author: Daniel
 */

#ifndef ADC_H_
#define ADC_H_

/*!
 * @brief  ADC pinout
 *	CHANNEL   ADC1   ADC2   ADC3
 *
 *	0         PA0    PA0    PA0
 *	1         PA1    PA1    PA1
 *	2         PA2    PA2    PA2
 *	3         PA3    PA3    PA3
 *	4         PA4    PA4    PF6
 *	5         PA5    PA5    PF7
 *	6         PA6    PA6    PF8
 *	7         PA7    PA7    PF9
 *	8         PB0    PB0    PF10
 *	9         PB1    PB1    PF3
 *	10        PC0    PC0    PC0
 *	11        PC1    PC1    PC1
 *	12        PC2    PC2    PC2
 *	13        PC3    PC3    PC3
 *	14        PC4    PC4    PF4
 *	15        PC5    PC5    PF5
 */

/* Includes ------------------------------------------------------------------*/
#include "def.h"
#include "rcc.h"
#include "gpio.h"

/* Define --------------------------------------------------------------------*/

#define V_REFIN_CAL (*(uint16_t*)0x1FFF7A2A)
#define V_MEASURMENT_CONDITIONS 3300
#define ADC_RESOLUTION 4095 				//12-bit

#define ADC_QUANTITY_CHANNEL           		2U
#define ADC_QUANTITY_SAMPLES				11U
#define HYST_HIGH_LEVEL						4U
#define HYST_LOW_LEVEL						3U

/* Typedef -------------------------------------------------------------------*/

typedef struct {
	uint16_t samples[ADC_QUANTITY_CHANNEL][ADC_QUANTITY_SAMPLES];
	uint16_t samples_sort[ADC_QUANTITY_CHANNEL][ADC_QUANTITY_SAMPLES];
	uint16_t avg_val[ADC_QUANTITY_CHANNEL];
	uint8_t num_samples;
	BOOL data_ready;
}st_avg_t;

typedef struct {
	uint16_t raw_data[ADC_QUANTITY_CHANNEL];
	st_avg_t st_avg;
}st_ADC_measure_t;


/*!
 * @brief  ADC available channels
 */
typedef enum {
	ADC_CHANNEL_0,  /*!< Operate with ADC channel 0 */
	ADC_CHANNEL_1,  /*!< Operate with ADC channel 1 */
	ADC_CHANNEL_2,  /*!< Operate with ADC channel 2 */
	ADC_CHANNEL_3,  /*!< Operate with ADC channel 3 */
	ADC_CHANNEL_4,  /*!< Operate with ADC channel 4 */
	ADC_CHANNEL_5,  /*!< Operate with ADC channel 5 */
	ADC_CHANNEL_6,  /*!< Operate with ADC channel 6 */
	ADC_CHANNEL_7,  /*!< Operate with ADC channel 7 */
	ADC_CHANNEL_8,  /*!< Operate with ADC channel 8 */
	ADC_CHANNEL_9,  /*!< Operate with ADC channel 9 */
	ADC_CHANNEL_10, /*!< Operate with ADC channel 10 */
	ADC_CHANNEL_11, /*!< Operate with ADC channel 11 */
	ADC_CHANNEL_12, /*!< Operate with ADC channel 12 */
	ADC_CHANNEL_13, /*!< Operate with ADC channel 13 */
	ADC_CHANNEL_14, /*!< Operate with ADC channel 14 */
	ADC_CHANNEL_15, /*!< Operate with ADC channel 15 */
	ADC_CHANNEL_16, /*!< Operate with ADC channel 16 */
	ADC_CHANNEL_17, /*!< Operate with ADC channel 17 */
	ADC_CHANNEL_18  /*!< Operate with ADC channel 18 */
} en_ADC_Channel_t;

/*!
 * @brief ADC Sampling Times enumeration
 */
typedef enum {
	 ADC_SAMPLETIME_3CYCLES    = ((uint32_t)0x00000000U),
	 ADC_SAMPLETIME_15CYCLES   = ((uint32_t)0x00000001U),
	 ADC_SAMPLETIME_28CYCLES   = ((uint32_t)0x00000002U),
	 ADC_SAMPLETIME_56CYCLES   = ((uint32_t)0x00000003U),
	 ADC_SAMPLETIME_84CYCLES   = ((uint32_t)0x00000004U),
	 ADC_SAMPLETIME_112CYCLES  = ((uint32_t)0x00000005U),
	 ADC_SAMPLETIME_144CYCLES  = ((uint32_t)0x00000006U),
	 ADC_SAMPLETIME_480CYCLES  = ((uint32_t)0x00000007U)
} en_ADC_SamplingTime_t;

/*!
 * @brief ADC Prescaler enumeration
 */
typedef enum {
	 ADC_DIV_2   = ((uint32_t)0x00000000U),
	 ADC_DIV_4   = ((uint32_t)0x00000001U),
	 ADC_DIV_6   = ((uint32_t)0x00000002U),
	 ADC_DIV_8   = ((uint32_t)0x00000003U)
} en_ADC_Prescaler_t;

/*!
 * @brief ADC Resolution enumeration
 */
typedef enum {
	 ADC_RESOLUTION_12b   = ((uint32_t)0x00000000U),
	 ADC_RESOLUTION_10b   = ((uint32_t)0x00000001U),
	 ADC_RESOLUTION_8b   = ((uint32_t)0x00000002U),
	 ADC_RESOLUTION_6b   = ((uint32_t)0x00000003U)
} en_ADC_Resolution_t;

/* Macro ---------------------------------------------------------------------*/
/* Variables -----------------------------------------------------------------*/
/* Function prototypes -------------------------------------------------------*/
/* Functions -----------------------------------------------------------------*/

/*!
 * @brief  Initializes ADC peripheral with default settings.
 * @param  *ADCx: Pointer to ADC peripheral where you want to enable ADC.
 * @param  channel: channel for ADCx. This parameter can be a value of @ref en_ADC_Channel_t enumeration.
 * @return none
 */
void ADC_init(ADC_TypeDef* ADCx, en_ADC_Channel_t channel);

/*!
 * @brief  Initializes ADC channel.
 * @param  *ADCx: Pointer to ADC peripheral where you want to enable ADC.
 * @param  channel: channel for ADCx. This parameter can be a value of @ref en_ADC_Channel_t enumeration.
 * @return none
 */
void ADC_initChannel(ADC_TypeDef* ADCx, en_ADC_Channel_t channel);

/*!
 * @brief  Start Conversion for given ADC.
 * @param  *ADCx: Pointer to ADC peripheral where you want to enable ADC.
 * @return none
 */
void ADC_startConv(ADC_TypeDef* ADCx);

/*!
 * @brief	Initializes structure to calculate average value comming from ADC.
 * @note
 * @param  	none
 * @return 	none.
 */
void ADC_initAverageStructure(void);

/*!
 * @brief	Get data from ADC channels and placing them in the median counting table.
 * @note
 * @param  	none
 * @return 	none.
 */
void ADC_acquisitionData(void);

/*!
 * @brief	Average data received from ADC channels
 * @note
 * @param  	none
 * @return 	none.
 */
void ADC_averageFunction(void);

/*!
 * @brief  Get access to structure with ADC measures.
 * @param  none
 * @return Pointer to structure with measures.
 */
st_ADC_measure_t* ADC_accessAdcMeasure(void);

#endif /* ADC_H_ */
