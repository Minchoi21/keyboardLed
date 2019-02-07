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
#define GET_STREAM_NUMBER_DMA1(stream)    (((uint32_t)(stream) - (uint32_t)DMA1_Stream0) / (0x18))
#define GET_STREAM_NUMBER_DMA2(stream)    (((uint32_t)(stream) - (uint32_t)DMA2_Stream0) / (0x18))
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Offsets for bits */
const static uint8_t DMA_Flags_Bit_Pos[4] = {
	0, 6, 16, 22
};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void DMA_clearFlag(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t flag)
{
	uint32_t location;
	uint32_t stream_number;

	/* Check stream value */
	if (DMAy_Streamx < DMA2_Stream0) {
		location = (uint32_t)&DMA1->LIFCR;
		stream_number = GET_STREAM_NUMBER_DMA1(DMAy_Streamx);
	} else {
		location = (uint32_t)&DMA2->LIFCR;
		stream_number = GET_STREAM_NUMBER_DMA2(DMAy_Streamx);
	}

	/* Get register offset */
	if (stream_number >= 4) {
		/* High registers for DMA clear */
		location += 4;

		/* Do offset for high DMA registers */
		stream_number -= 4;
	}

	/* Clear flags */
	*(__IO uint32_t *)location = (flag & DMA_FLAG_ALL) << DMA_Flags_Bit_Pos[stream_number];
}

void DMA_init(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t channel, en_DMA_MemoryDataSize_t mem_size, en_DMA_PeripheralDataSize_t periph_size)
{
	/* Disable DMA TX Stream */
	DMAy_Streamx->CR &= ~((uint32_t)DMA_SxCR_EN);

	/* Clear peripheral and memory data size fields */
	DMAy_Streamx->CR &= ~((uint32_t)DMA_SxCR_PSIZE | (uint32_t)DMA_SxCR_MSIZE);

	/* Set DMA options for TX Stream */
	DMAy_Streamx->CR |= channel;

	/* Set DMA peripheral and memory data size */
	DMAy_Streamx->CR |= (mem_size | periph_size);

	/* Enable DMA stream interrupts */
	DMAy_Streamx->CR |= DMA_SxCR_TCIE | DMA_SxCR_HTIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE;
	DMAy_Streamx->FCR |= DMA_SxFCR_FEIE;


//	/* Enable DMA TX stream */
//	DMAy_Streamx->CR |= DMA_SxCR_EN;
}


void DMA_deinit(DMA_Stream_TypeDef* DMAy_Streamx)
{
	 /* Disable the selected DMAy Streamx */
	DMAy_Streamx->CR &= ~((uint32_t)DMA_SxCR_EN);

	  /* Reset DMAy Streamx control register */
	DMAy_Streamx->CR  = 0;

	  /* Reset DMAy Streamx Number of Data to Transfer register */
	DMAy_Streamx->NDTR = 0;

	  /* Reset DMAy Streamx peripheral address register */
	DMAy_Streamx->PAR  = 0;

	  /* Reset DMAy Streamx memory 0 address register */
	DMAy_Streamx->M0AR = 0;

	  /* Reset DMAy Streamx memory 1 address register */
	DMAy_Streamx->M1AR = 0;

	  /* Reset DMAy Streamx FIFO control register */
	DMAy_Streamx->FCR = (uint32_t)0x00000021;

	/* Reset interrupt pending bits for DMAy_Streamx */
	DMA_clearFlag(DMAy_Streamx, DMA_FLAG_ALL);

//    /* Reset interrupt pending bits for DMA1 Stream4 */
//	DMA1->HIFCR |= DMA_HIFCR_CFEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CHTIF4| DMA_HIFCR_CTCIF4;

}

/*****************************************************************/
/*                 DMA INTERRUPT USER CALLBACKS                  */
/*****************************************************************/
void DMA_transferCompleteHandler(DMA_Stream_TypeDef* DMA_Stream) {
	/* NOTE: This function should not be modified, when the callback is needed,
            the TM_DMA_TransferCompleteHandler could be implemented in the user file
	*/
	if (DMA_Stream == DMA2_Stream0) {
			st_dma_flags.adc_dma_tcmpl = TRUE;
	}
}

void DMA_halfTransferCompleteHandler(DMA_Stream_TypeDef* DMA_Stream) {
	/* NOTE: This function should not be modified, when the callback is needed,
            the TM_DMA_HalfTransferCompleteHandler could be implemented in the user file
	*/
}

void DMA_transferErrorHandler(DMA_Stream_TypeDef* DMA_Stream) {
	/* NOTE: This function should not be modified, when the callback is needed,
            the TM_DMA_TransferErrorHandler could be implemented in the user file
	*/
}

void DMA_directModeErrorHandler(DMA_Stream_TypeDef* DMA_Stream) {
	/* NOTE: This function should not be modified, when the callback is needed,
            the TM_DMA_DirectModeErrorHandler could be implemented in the user file
	*/
}

void DMA_FIFOErrorHandler(DMA_Stream_TypeDef* DMA_Stream) {
	/* NOTE: This function should not be modified, when the callback is needed,
            the TM_DMA_FIFOErrorHandler could be implemented in the user file
	*/
}


/* DMA Interrupt Functions for DMA1 Stream 4 */
static void DMA_INT_processInterrupt(DMA_Stream_TypeDef* DMA_Stream) {

	/* Call user callback function */

	/* Check transfer complete flag */
	if (DMA_Stream->CR & DMA_SxCR_TCIE) {
		DMA_transferCompleteHandler(DMA_Stream);
	}
	/* Check half-transfer complete flag */
	if ((DMA_Stream->CR & DMA_SxCR_HTIE)) {
		DMA_halfTransferCompleteHandler(DMA_Stream);
	}
	/* Check transfer error flag */
	if ((DMA_Stream->CR & DMA_SxCR_TEIE)) {
		DMA_transferErrorHandler(DMA_Stream);
	}
	/* Check direct error flag */
	if ((DMA_Stream->CR & DMA_SxCR_DMEIE)) {
		DMA_directModeErrorHandler(DMA_Stream);
	}
	/* Check FIFO error flag */
	if ((DMA_Stream->FCR & DMA_SxFCR_FEIE)) {
		DMA_FIFOErrorHandler(DMA_Stream);
	}
}


#ifndef DMA1_STREAM3_DISABLE_IRQHANDLER
void DMA1_Stream3_IRQHandler(void) {
	NVIC_ClearPendingIRQ(DMA1_Stream3_IRQn);
	/* Clear all flags */
	DMA_clearFlag(DMA1_Stream3, DMA_FLAG_ALL);
//	DMA1->HIFCR |= DMA_HIFCR_CFEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CHTIF4| DMA_HIFCR_CTCIF4;
	/* Call user function */
	DMA_INT_processInterrupt(DMA1_Stream3);

}
#endif
#ifndef DMA1_STREAM4_DISABLE_IRQHANDLER
void DMA1_Stream4_IRQHandler(void) {
	NVIC_ClearPendingIRQ(DMA1_Stream4_IRQn);
	/* Clear all flags */
	DMA_clearFlag(DMA1_Stream4, DMA_FLAG_ALL);
//	DMA1->HIFCR |= DMA_HIFCR_CFEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CHTIF4| DMA_HIFCR_CTCIF4;
	/* Call user function */
	DMA_INT_processInterrupt(DMA1_Stream4);

}
#endif
#ifndef DMA2_STREAM0_DISABLE_IRQHANDLER
void DMA2_Stream0_IRQHandler(void) {
	NVIC_ClearPendingIRQ(DMA2_Stream0_IRQn);
	/* Clear all flags */
	DMA_clearFlag(DMA2_Stream0, DMA_FLAG_ALL);
//	DMA1->HIFCR |= DMA_HIFCR_CFEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CHTIF4| DMA_HIFCR_CTCIF4;
	/* Call user function */
	DMA_INT_processInterrupt(DMA2_Stream0);

}
#endif
#ifndef DMA2_STREAM2_DISABLE_IRQHANDLER
void DMA2_Stream2_IRQHandler(void) {
	NVIC_ClearPendingIRQ(DMA2_Stream2_IRQn);
	/* Clear all flags */
	DMA_clearFlag(DMA2_Stream2, DMA_FLAG_ALL);
//	DMA1->HIFCR |= DMA_HIFCR_CFEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CHTIF4| DMA_HIFCR_CTCIF4;
	/* Call user function */
	DMA_INT_processInterrupt(DMA2_Stream2);

}
#endif
#ifndef DMA2_STREAM3_DISABLE_IRQHANDLER
void DMA2_Stream3_IRQHandler(void) {
	NVIC_ClearPendingIRQ(DMA2_Stream3_IRQn);
	/* Clear all flags */
	DMA_clearFlag(DMA2_Stream3, DMA_FLAG_ALL);
//	DMA1->HIFCR |= DMA_HIFCR_CFEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CHTIF4| DMA_HIFCR_CTCIF4;
	/* Call user function */
	DMA_INT_processInterrupt(DMA2_Stream3);

}
#endif

