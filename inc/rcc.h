/*
 * rcc.h
 *
 *  Created on: 27.11.2018
 *      Author: Daniel
 */

#ifndef RCC_H_
#define RCC_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RCC_GPIOA_CLK_ENABLE			SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN)
#define RCC_GPIOB_CLK_ENABLE			SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN)
#define RCC_GPIOC_CLK_ENABLE			SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN)
#define RCC_GPIOD_CLK_ENABLE			SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN)
#define RCC_GPIOE_CLK_ENABLE			SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN)
#define RCC_GPIOF_CLK_ENABLE			SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOFEN)
#define RCC_GPIOG_CLK_ENABLE			SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOGEN)
#define RCC_GPIOH_CLK_ENABLE			SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOHEN)
#define RCC_GPIOI_CLK_ENABLE			SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOIEN)
#define RCC_GPIOJ_CLK_ENABLE			SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOJEN)
#define RCC_GPIOK_CLK_ENABLE			SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOKEN)

#define RCC_SYSCFG_CLK_ENABLE			SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN)
#define RCC_SPI1_CLK_ENABLE				SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN)
#define RCC_SPI2_CLK_ENABLE				SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN)

#define RCC_DMA1_CLK_ENABLE				SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN)
#define RCC_DMA2_CLK_ENABLE				SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA2EN)

#define RCC_ADC1_CLK_ENABLE				SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN)
#define RCC_ADC2_CLK_ENABLE				SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC2EN)
#define RCC_ADC3_CLK_ENABLE				SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC3EN)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void RCC_initHsePll(void);
void RCC_enableGpioClock(void);
void RCC_enableSysConfClock(void);
void RCC_enableSpiClock(void);
void RCC_enableDmaClock(void);
void RCC_enableAdcClock(void);
/* Private functions ---------------------------------------------------------*/

#endif /* RCC_H_ */
