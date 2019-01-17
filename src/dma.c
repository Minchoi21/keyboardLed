/*
 * dma.c
 *
 *  Created on: 08.01.2019
 *      Author: Daniel
 */

/* Includes ------------------------------------------------------------------*/
#include "dma.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void DMA_init()
{

	/* Disable DMA TX Stream */
	DMA1_Stream4->CR &= ~((uint32_t)DMA_SxCR_EN);

	/* Set DMA options for TX Stream */
	DMA1_Stream4->CR &= ~((uint32_t)DMA_SxCR_CHSEL); 			/* Channel0 for SPI DMA TX*/

	/* Enable DMA stream interrupts */
	DMA1_Stream4->CR |= DMA_SxCR_TCIE; //| DMA_SxCR_HTIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE
//	DMA1_Stream4->FCR |= DMA_SxFCR_FEIE;

	/* Enable SPI2 TX DMA */
	SPI2->CR2 |= SPI_CR2_TXDMAEN;

//	/* Enable DMA TX stream */
//	DMA1_Stream4->CR |= DMA_SxCR_EN;
}


void DMA_DeInit(void)
{
	 /* Disable the selected DMAy Streamx */
	DMA1_Stream4->CR &= ~((uint32_t)DMA_SxCR_EN);

	  /* Reset DMAy Streamx control register */
	DMA1_Stream4->CR  = 0;

	  /* Reset DMAy Streamx Number of Data to Transfer register */
	DMA1_Stream4->NDTR = 0;

	  /* Reset DMAy Streamx peripheral address register */
	DMA1_Stream4->PAR  = 0;

	  /* Reset DMAy Streamx memory 0 address register */
	DMA1_Stream4->M0AR = 0;

	  /* Reset DMAy Streamx memory 1 address register */
	DMA1_Stream4->M1AR = 0;

	  /* Reset DMAy Streamx FIFO control register */
	DMA1_Stream4->FCR = (uint32_t)0x00000021;

    /* Reset interrupt pending bits for DMA1 Stream4 */
	DMA1->HIFCR |= DMA_HIFCR_CFEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CHTIF4| DMA_HIFCR_CTCIF4;

}

/*****************************************************************/
/*                 DMA INTERRUPT USER CALLBACKS                  */
/*****************************************************************/
void TM_DMA_TransferCompleteHandler(DMA_Stream_TypeDef* DMA_Stream) {
	/* NOTE: This function should not be modified, when the callback is needed,
            the TM_DMA_TransferCompleteHandler could be implemented in the user file
	*/
}

void TM_DMA_HalfTransferCompleteHandler(DMA_Stream_TypeDef* DMA_Stream) {
	/* NOTE: This function should not be modified, when the callback is needed,
            the TM_DMA_HalfTransferCompleteHandler could be implemented in the user file
	*/
}

void TM_DMA_TransferErrorHandler(DMA_Stream_TypeDef* DMA_Stream) {
	/* NOTE: This function should not be modified, when the callback is needed,
            the TM_DMA_TransferErrorHandler could be implemented in the user file
	*/
}

void TM_DMA_DirectModeErrorHandler(DMA_Stream_TypeDef* DMA_Stream) {
	/* NOTE: This function should not be modified, when the callback is needed,
            the TM_DMA_DirectModeErrorHandler could be implemented in the user file
	*/
}

void TM_DMA_FIFOErrorHandler(DMA_Stream_TypeDef* DMA_Stream) {
	/* NOTE: This function should not be modified, when the callback is needed,
            the TM_DMA_FIFOErrorHandler could be implemented in the user file
	*/
}


/* DMA Interrupt Functions for DMA1 Stream 4 */
static void TM_DMA_INT_ProcessInterrupt(DMA_Stream_TypeDef* DMA_Stream) {

	/* Call user callback function */

	/* Check transfer complete flag */
	if (DMA_Stream->CR & DMA_SxCR_TCIE) {
		TM_DMA_TransferCompleteHandler(DMA_Stream);
	}
	/* Check half-transfer complete flag */
	if ((DMA_Stream->CR & DMA_SxCR_HTIE)) {
		TM_DMA_HalfTransferCompleteHandler(DMA_Stream);
	}
	/* Check transfer error flag */
	if ((DMA_Stream->CR & DMA_SxCR_TEIE)) {
		TM_DMA_TransferErrorHandler(DMA_Stream);
	}
	/* Check direct error flag */
	if ((DMA_Stream->CR & DMA_SxCR_DMEIE)) {
		TM_DMA_DirectModeErrorHandler(DMA_Stream);
	}
	/* Check FIFO error flag */
	if ((DMA_Stream->FCR & DMA_SxFCR_FEIE)) {
		TM_DMA_FIFOErrorHandler(DMA_Stream);
	}
}

#ifndef DMA1_STREAM4_DISABLE_IRQHANDLER
void DMA1_Stream4_IRQHandler(void) {
	NVIC_ClearPendingIRQ(DMA1_Stream4_IRQn);
	/* Clear all flags */
	DMA1->HIFCR |= DMA_HIFCR_CFEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CHTIF4| DMA_HIFCR_CTCIF4;
	/* Call user function */
	TM_DMA_INT_ProcessInterrupt(DMA1_Stream4);

}
#endif

