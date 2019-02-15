/*
 * stmeval_gpio.c
 *
 *  Created on: 26.11.2018
 *      Author: Daniel
 */

/* Includes ------------------------------------------------------------------*/
#include <stmeval_led.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/*------------------------------------------------------------------------------
Initialize the GPIO PIN as a output
*------------------------------------------------------------------------------*/
void STM_EVAL_initLed(GPIO_TypeDef* GPIOx,  uint16_t GPIO_Pin)
{
	/* Configure the GPIO_LED pin as a output, push-pull, pull-up, very high speed */
	GPIO_init(GPIOx, GPIO_Pin, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High);
}
/*------------------------------------------------------------------------------
Initialize the LED
*------------------------------------------------------------------------------*/
void STM_EVAL_initAllLeds(void)
{
	/*	Configure the GPIO_LEDs pins as a output, push-pull, pull-up, very high speed */
	GPIO_init(LED_GPIO_PORT, LED_B_PIN|LED_G_PIN|LED_O_PIN|LED_R_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High);
}

/*------------------------------------------------------------------------------
Turn On Led pin
*------------------------------------------------------------------------------*/
void STM_EVAL_ledOn(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_setPin(GPIOx, GPIO_Pin);
}

/*------------------------------------------------------------------------------
Turn off Led pin
*------------------------------------------------------------------------------*/
void STM_EVAL_ledOff(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_resetPin(GPIOx,GPIO_Pin);
}

/*------------------------------------------------------------------------------
Switch Led pin state to the opposite
*------------------------------------------------------------------------------*/
void STM_EVAL_ledToggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_togglePin(GPIOx, GPIO_Pin);
}

/*------------------------------------------------------------------------------
Initialize the GPIO and the external interrupt
*------------------------------------------------------------------------------*/
void STM_EVAL_initButton(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	/* Configure Button pin as input, no pull resistor */
	GPIO_init(GPIOx, GPIO_Pin, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High);
	/* Connect the Button GPIO portA pin0 to external interrupt line0 */
	SYSCFG->EXTICR[0] &= SYSCFG_EXTICR1_EXTI0_PA;
	/* Configure the corresponding mask bit in the EXTI_IMR register
	 * and Trigger Selection bits of the Interrupt line on falling edge */
	EXTI_init(GPIO_Pin, EXTI_Trigger_Falling);
}

/*------------------------------------------------------------------------------
Initialize the LEDs and USER BUTTON on the evaluation board DISCOVERY
*------------------------------------------------------------------------------*/
void STM_EVAL_initBoard(void)
{
	STM_EVAL_initAllLeds();
	STM_EVAL_initButton(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN);

/* SPI2 */
	/* Configure SPI2 for TLC5971 Led controller on external Keyboard */
	SPI_init(SPI2, SPI_PINSPACK_2, SPI_DATASIZE_8b);
	SPI_DMA_init(SPI2);
	TLC5971_init();
	/* Send packet to turn off led's on external Keyboard */
	TLC5971_sendPacket(SPI2);
	TLC5971_setLuminosity(3840);

/* SPI1 */
	/* Reset PE3 to set low on CS_SPI for LIS3DSH */
	GPIO_init(GPIOE, GPIO_Pin_3, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Medium);
	GPIO_resetPin(GPIOE, GPIO_Pin_3);
	/* Configure Pin4 on PORTA for SPI_CS to control MAX7301 */
	GPIO_init(GPIOA, GPIO_Pin_4, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Medium);
	GPIO_setPin(GPIOA, GPIO_Pin_4);
	/* Configure SPI1 for MAX7301 I/O Expander on external Keyboard */
	SPI_init(SPI1, SPI_PINSPACK_1, SPI_DATASIZE_16b);
//	SPI_DMA_init(SPI1);

/* MAX7301 */
	MAX7301_init();

/* ADC1 */
	ADC_DMA_init(ADC1, ADC_accessAdcMeasure()->raw_data);
	ADC_startConv(ADC1);
	/* Set initial values for st_ADC_measure_t */
	ADC_initAverageStructure();
}

///**
//  * @brief  Returns the selected Button state.
//  * @param  Button: Specifies the Button to be checked.
//  *   This parameter should be: BUTTON_USER
//  * @retval The Button GPIO pin value.
//  */
//uint32_t STM_EVAL_PBGetState(Button_TypeDef Button)
//{
//  return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
//}
