/*
 * gpio.c
 *
 *  Created on: 27.11.2018
 *      Author: Daniel
 */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
uint16_t GPIO_getPinSource(uint16_t GPIO_Pin) {
	uint16_t pinsource = 0;

	/* Get pinsource */
	while (GPIO_Pin > 1) {
		/* Increase pinsource */
		pinsource++;
		/* Shift right */
		GPIO_Pin >>= 1;
	}

	/* Return source */
	return pinsource;
}

uint16_t GPIO_getPortSource(GPIO_TypeDef* GPIOx)
{
	/* Get port source number */
	/* Offset from GPIOA                       Difference between 2 GPIO addresses */
	return ((uint32_t)GPIOx - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE));
}

void GPIO_enableClock(GPIO_TypeDef* GPIOx)
{
	/* Set bit according to the 1 << portsourcenumber */
	RCC->AHB1ENR |= (1 << GPIO_getPortSource(GPIOx));
}

void GPIO_disableClock(GPIO_TypeDef* GPIOx)
{
	/* Clear bit according to the 1 << portsourcenumber */
	RCC->AHB1ENR &= ~(1 << GPIO_getPortSource(GPIOx));
}

/* Configure pin(s) on port GPIOx and enables clock for GPIOx port */
void GPIO_init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_Mode_t GPIO_Mode, GPIO_OType_t GPIO_OType, GPIO_PuPd_t GPIO_PuPd, GPIO_Speed_t GPIO_Speed)
{
	uint8_t pinpos;

	/* Check input */
	if (GPIO_Pin == 0x00) {
		return;
	}

	/* Enable GPIOx clock */
	GPIO_enableClock(GPIOx);

	/* Go through all pins */
	for (pinpos = 0; pinpos < 0x10; pinpos++) {
		/* Check if pin available */
		if ((GPIO_Pin & (1 << pinpos)) == 0) {
			continue;
		}

		/* Set GPIO PUPD register */
		GPIOx->PUPDR = (GPIOx->PUPDR & ~(0x03 << (2 * pinpos))) | ((uint32_t)(GPIO_PuPd << (2 * pinpos)));

		/* Set GPIO MODE register */
		GPIOx->MODER = (GPIOx->MODER & ~((uint32_t)(0x03 << (2 * pinpos)))) | ((uint32_t)(GPIO_Mode << (2 * pinpos)));

		/* Set only if output or alternate functions */
		if (GPIO_Mode == GPIO_Mode_OUT || GPIO_Mode == GPIO_Mode_AF) {
			/* Set GPIO OTYPE register */
			GPIOx->OTYPER = (GPIOx->OTYPER & ~(uint16_t)(0x01 << pinpos)) | ((uint16_t)(GPIO_OType << pinpos));

			/* Set GPIO OSPEED register */
			GPIOx->OSPEEDR = (GPIOx->OSPEEDR & ~((uint32_t)(0x03 << (2 * pinpos)))) | ((uint32_t)(GPIO_Speed << (2 * pinpos)));
		}
	}
}

/* Configure pin(s) on port GPIOx as alternate function */
void GPIO_initAlternate(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_OType_t GPIO_OType, GPIO_PuPd_t GPIO_PuPd, GPIO_Speed_t GPIO_Speed, GPIO_AlternateFcn_t GPIO_Alternate)
{
	uint32_t pinpos;

	/* Check input */
	if (GPIO_Pin == 0x00) {
		return;
	}

	/* Enable GPIOx clock */
	GPIO_enableClock(GPIOx);

	/* Set alternate functions for all pins */
	for (pinpos = 0; pinpos < 0x10; pinpos++) {
		/* Check pin */
		if ((GPIO_Pin & (1 << pinpos)) == 0) {
			continue;
		}

		/* Set alternate function */
		GPIOx->AFR[pinpos >> 0x03] = (GPIOx->AFR[pinpos >> 0x03] & ~(0x0F << (4 * (pinpos & 0x07)))) | (GPIO_Alternate << (4 * (pinpos & 0x07)));
	}

	/* Do initialization */
	GPIO_init(GPIOx, GPIO_Pin, GPIO_Mode_AF, GPIO_OType, GPIO_PuPd, GPIO_Speed);
}

/* Set PINx on port GPIOx */
inline void GPIO_setPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	GPIOx->BSRR = GPIO_Pin;
}

/* Reset PINx on port GPIOx */
inline void GPIO_resetPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
}

/* Toggle PINx on port GPIOx */
inline void GPIO_togglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	GPIOx->ODR ^= GPIO_Pin;
}

