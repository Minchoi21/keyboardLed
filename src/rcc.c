/*
 * rcc.c
 *
 *  Created on: 27.11.2018
 *      Author: Daniel
 */

/* Includes ------------------------------------------------------------------*/
#include "rcc.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Configure source clock as PLL */
void RCC_initHsePll(void)
{
	/* Clock control register */
	RCC->CR = RCC_CR_HSEON;         /* Enable external oscillator */

	/* Wait for locked external oscillator */
	while((RCC->CR & RCC_CR_HSERDY) != RCC_CR_HSERDY);

	/* PLL config */
	RCC->PLLCFGR =
	          RCC_PLLCFGR_PLLSRC_HSE                /* PLL source */
	        | (4 << 0)                              /* PLL input division */
	        | (168 << 6)                            /* PLL multiplication */
	        | (0 << 16)                             /* PLL sys clock division */
	        | (7 << 24);                            /* PLL usb clock division =48MHz */

	/* crystal:  8MHz
	 * PLL in:   2MHz (div 4)
	 * PLL loop: 336MHz (mul 168)
	 * PLL out:  168MHz (div 2)
	 * PLL usb:  48MHz (div 7)
	 */

	/* Enable PLL */
	RCC->CR |= RCC_CR_PLLON;

	/* Wait for locked PLL */
	while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

	/* Configure clocks
	 * Max SYSCLK: 168MHz
	 * Max AHB:  SYSCLK
	 * Max APB1: SYSCLK/4 = 48MHz
	 * Max APB2: SYSCLK/2 = 86MHz
	 * + enable sys clock output 2 with clock divider = 4 */
	RCC->CFGR =
	          0x0                           /* Clock output 2 is SYSCLK (RCC_CFGR_MCO2) */
	        | ( 0x6 << 27)                  /* Clock output divider */
	        | RCC_CFGR_PPRE2_DIV2           /* APB2 prescaler */
	        | RCC_CFGR_PPRE1_DIV4;          /* APB1 prescaler */

	/* select system clock */
	RCC->CFGR &= ~RCC_CFGR_SW; /* clear */
	RCC->CFGR |= RCC_CFGR_SW_PLL;   /* SYSCLK is PLL */

	/* Wait for SYSCLK to be PPL */
	while((RCC->CFGR & RCC_CFGR_SW_PLL) != RCC_CFGR_SW_PLL);

	SystemCoreClockUpdate();
}

/* Enable the all GPIO Clock */
void RCC_enableGpioClock(void)
{
//	RCC_GPIOA_CLK_ENABLE;
//	RCC_GPIOB_CLK_ENABLE;
//	RCC_GPIOC_CLK_ENABLE;
//	RCC_GPIOD_CLK_ENABLE;
//	RCC_GPIOE_CLK_ENABLE;
//	RCC_GPIOF_CLK_ENABLE;
//	RCC_GPIOG_CLK_ENABLE;
//	RCC_GPIOH_CLK_ENABLE;
}

/* Enable clock for SYSCFG */
void RCC_enableSysConfClock(void)
{
	RCC_SYSCFG_CLK_ENABLE;
}

/* Enable the SPI's Clock */
void RCC_enableSpiClock(void)
{
	RCC_SPI1_CLK_ENABLE;
	RCC_SPI2_CLK_ENABLE;
}

/* Enable the DMA1 and DMA2 Clock */
void RCC_enableDmaClock(void)
{
	RCC_DMA1_CLK_ENABLE;
	RCC_DMA2_CLK_ENABLE;
}



