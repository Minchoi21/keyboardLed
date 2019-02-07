/**
  ******************************************************************************
  * @file    main.c
  * @author  Daniel Wa�ydr�g
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
	static uint8_t led;
	static uint16_t button_keyboard;
	SYS_init();
	STM_EVAL_initBoard();
	for(;;)
	{
		if(SysTick_time1_flag) {
			SysTick_time1_flag = FALSE;
				STM_EVAL_ledToggle(GPIOD, GPIO_Pin_13);
		}

		if(SysTick_time3_flag) {
			SysTick_time3_flag = FALSE;

			button_keyboard = MAX7301_readData();

			if(SysTick_time2_flag) {
				SysTick_time2_flag = FALSE;
				if(led >= (TLC5971_ALL_NUM_LED-2)) led = 0x00;
				led++;
			}
			TLC5971_setLuminosity(126);
			TLC5971_clrLedAll();
			TLC5971_setLed(1<<led);
			TLC5971_setLed(button_keyboard);
			TLC5971_sendPacket(SPI2);
		}
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

/* Triggered with 1kHz frequency */
void SysTick_Handler(void){
	static uint32_t SysTick_time_1 = SYS_TICK_DELAY_1;
	static uint32_t SysTick_time_2 = SYS_TICK_DELAY_2;
	static uint32_t SysTick_time_3 = SYS_TICK_DELAY_3;


	if(!SysTick_time_1){
		SysTick_time_1 = SYS_TICK_DELAY_1;
		SysTick_time1_flag = TRUE;
	}
	if(!SysTick_time_2){
		SysTick_time_2 = SYS_TICK_DELAY_2;
		SysTick_time2_flag = TRUE;
	}
	if(!SysTick_time_3){
		SysTick_time_3 = SYS_TICK_DELAY_3;
		SysTick_time3_flag = TRUE;
	}
	SysTick_time_1--;
	SysTick_time_2--;
	SysTick_time_3--;
}
