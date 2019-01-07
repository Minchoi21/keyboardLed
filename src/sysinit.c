/*
 * initStmDev.c
 *
 *  Created on: 27.11.2018
 *      Author: Daniel
 */


/* Includes ------------------------------------------------------------------*/
#include <sysinit.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void SYS_init(void) {
	FLASH_init();
	RCC_initHsePll();
//	GPIO_enableClock(LED_GPIO_PORT);					/* Enable the GPIOD Clock for handling USER_LEDS */
//	GPIO_enableClock(USER_BUTTON_GPIO_PORT);			/* Enable the GPIOA Clock for handling USER_BUTTON */
	RCC_enableSysConfClock();							/* Enable the SYSCF Clock for handling USER_BUTTON */
	RCC_enableSpiClock();								/* Enable the SPI Clock for handling tlc5971 */
	RCC_enableDmaClock();								/* Enable the DMA1 and DMA2 Clock for handling SPI and ADC */

	SysTick_Config(SystemCoreClock / 1000);

	NVIC_init();

}
