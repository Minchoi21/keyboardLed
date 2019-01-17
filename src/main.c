/**
  ******************************************************************************
  * @file    main.c
  * @author  Daniel Wa¿ydr¹g
  * @version V1.0
  * @date    22-Nowember-2018
  * @brief   Default main function.
  ******************************************************************************
*/


/* Includes ------------------------------------------------------------------*/
#include <sysinit.h>
#include "stm32f4xx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay (uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */

int main(void)
{
	SYS_init();
	STM_EVAL_initBoard();
	for(;;)
	{
	}
}


/**
  * @brief  Delay Function.
  * @param  nCount:specifies the Delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {

  }
}


/* Set interrupt handlers */
/* Handle PA0 interrupt */
void EXTI0_IRQHandler(void) {

    /* Make sure that interrupt flag is set */
    if ((EXTI->PR & (1<<0)) != RESET) {
    	/* Make sure the Button is really pressed */
    	if (!(GPIOA->IDR & (1<<0)) )
    	{
    		STM_EVAL_ledToggle(GPIOD, GPIO_Pin_15);
    	}
    	/* Clear interrupt flag */
    	NVIC_ClearPendingIRQ(EXTI0_IRQn);
    	/* Clear the EXTI pending bits */
    	EXTI->PR |= ( 1<<0 );
    }
}


void SysTick_Handler(void){
	static uint32_t time = SYS_TICK_DELAY, time2 = SYS_TICK_DELAY_2;
	static uint8_t pos = 0, led = 2;
	static uint16_t tab_val[4] = { 128, 255, 3840, 65535};

	if(!time){
		time = SYS_TICK_DELAY;
//		STM_EVAL_ledToggle(GPIOD, GPIO_Pin_12);
		STM_EVAL_ledToggle(GPIOD, GPIO_Pin_13);
//		STM_EVAL_ledToggle(GPIOD, GPIO_Pin_14);

	}
	if(!time2){
		time2 = SYS_TICK_DELAY_2;

		if(pos >= 4) pos = 0;
//		TLC5971_set_luminosity(tab_val[pos++]);
		if(led >= (TLC5971_ALL_NUM_LED)) led = 2;
		TLC5971_set_led_all();
		TLC5971_clr_led(1<<led++);
		TLC5971_send_packet(SPI2);
	}
	time--;
	time2--;
}
