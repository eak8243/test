/*------------------------------------------------------------------------------------------
 * Project	:	RoboFarming
 * FIle		  :	init.h
 * MCU		  :	STM32F100RBT6B
 * Compiler	:	Keil uVision 4 MDK-ARM 4.14
 * Modify	  :	Danet Bamrungatanakit
 * Date		  :	26/03/2012
 *------------------------------------------------------------------------------------------*/

#ifndef _INIT_H
#define _INIT_H

/* Includes --------------------------------------------------------------------------------*/
/* Private Typedef -------------------------------------------------------------------------*/
/* Private Define --------------------------------------------------------------------------*/
// Set LED Port and Pin
/* Private macro ---------------------------------------------------------------------------*/
// Compute the prescaler value                                       
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
void RCC_Initial(void);  
void GPIO_Initial(void);  
void NVIC_Initial(void);  
void USART_Initial(void);
void TIM_Initial(void);
void EXTI_Initial(void);
void DAC_Initial(void);

/* Private functions -----------------------------------------------------------------------*/

#endif
