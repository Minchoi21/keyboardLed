/*
 * adc_dma.c
 *
 *  Created on: 04.02.2019
 *      Author: Daniel
 */


/* Includes ------------------------------------------------------------------*/
#include "adc_dma.h"

/* Private typedef ---------------------------------------------------*/

/* Private structure */
typedef struct {
	DMA_Stream_TypeDef* ADC_DMA_Stream;
	uint32_t ADC_DMA_Channel;
} st_ADC_DMA_settings_t;

/* Define ------------------------------------------------------------*/
/* Macro -------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
/* Private variables -------------------------------------------------*/

/* ADCx DMA default settings */
#ifdef SPI1
static st_ADC_DMA_settings_t st_adc1_dma = {DMA2_Stream0, DMA_Channel_0};
#endif
#ifdef SPI2
static st_ADC_DMA_settings_t st_adc2_dma = {DMA2_Stream2, DMA_Channel_1};
#endif
#ifdef SPI3
static st_ADC_DMA_settings_t st_adc3_dma = {DMA2_Stream1, DMA_Channel_2};
#endif


/* Private function prototypes ---------------------------------------*/
static st_ADC_DMA_settings_t* ADC_DMA_getSettings(ADC_TypeDef* SPIx);

/* Function prototypes -----------------------------------------------*/
/* Functions ---------------------------------------------------------*/
void ADC_DMA_init(ADC_TypeDef* ADCx, en_ADC_Channel_t channel, uint16_t* RX_Buffer)
{

	/* Get DMA Stream and Channel for SPIx */
	st_ADC_DMA_settings_t* st_settings = ADC_DMA_getSettings(ADCx);

	/* Enable DMA2 Clock for ADC */
	RCC_DMA2_CLK_ENABLE;

	/* Initializes the ADCx with channel */
	ADC_init(ADCx, channel);

	/* Clear configuration of DMAx Streamx */
	DMA_deinit(st_settings->ADC_DMA_Stream);

	st_dma_flags.adc_dma_tcmpl = FALSE;

	/* Configure DMAx Streamx for ADCx */
	st_settings->ADC_DMA_Stream->CR |= st_settings->ADC_DMA_Channel;                    //!< Select channel
	st_settings->ADC_DMA_Stream->CR |= (1U << DMA_SxCR_PL_Pos);                         //!< Priority level (Medium)
	st_settings->ADC_DMA_Stream->CR |= (1U << DMA_SxCR_MSIZE_Pos);                      //!< Memory data size: half-word (16-bit)
	st_settings->ADC_DMA_Stream->CR |= (1U << DMA_SxCR_PSIZE_Pos);                      //!< Peripheral data size: half-word (16-bit)
	st_settings->ADC_DMA_Stream->CR |= (1U << DMA_SxCR_MINC_Pos);                       //!< Memory address pointer is increment after each data transfer
	st_settings->ADC_DMA_Stream->CR |= (1U << DMA_SxCR_CIRC_Pos);                       //!< Circular mode enabled
	st_settings->ADC_DMA_Stream->CR |= (1U << DMA_SxCR_TCIE_Pos);                       //!< Transfer complete interrupt enable
	st_settings->ADC_DMA_Stream->CR |= (1U << DMA_SxCR_TEIE_Pos);                       //!< Transfer error interrupt enable
	st_settings->ADC_DMA_Stream->CR |= (1U << DMA_SxCR_DMEIE_Pos);                      //!< Transfer direction mode error interrupt enable

	st_settings->ADC_DMA_Stream->NDTR = ADC_QUANTITY_CHANNEL;                           //!< Number of data items to be transferred
	st_settings->ADC_DMA_Stream->PAR = (uint32_t)(&ADCx->DR);                           //!< Peripheral address register
	st_settings->ADC_DMA_Stream->M0AR = (uint32_t)RX_Buffer;           				 	//!< Memory address register
	st_settings->ADC_DMA_Stream->CR |= (DMA_SxCR_EN);                                   //!< Stream Enable

	ADCx->CR2 |= ADC_CR2_ADON;				//!< Enable ADC
}

/* Private Functions -------------------------------------------------*/
static st_ADC_DMA_settings_t* ADC_DMA_getSettings(ADC_TypeDef* ADCx)
{
	st_ADC_DMA_settings_t* ret_settings;
	#ifdef ADC1
		if (ADCx == ADC1) {
			ret_settings = &st_adc1_dma;
		}
	#endif
	#ifdef ADC2
		if (ADCx == ADC2) {
			ret_settings = &st_adc2_dma;
		}
	#endif
	#ifdef ADC3
		if (ADCx == ADC3) {
			ret_settings = &st_adc3_dma;
		}
	#endif

	return ret_settings;
}

