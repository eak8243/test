/*------------------------------------------------------------------------------------------
 * Project	:	RoboFarming
 * File		  :	systick.h
 * MCU		  :	STM32F100RBT6B
 * Compiler	:	Keil uVision 4 MDK-ARM 4.14
 * Modify	  :	Danet Bamrungatanakit
 * Date		  :	01/02/2012
 *------------------------------------------------------------------------------------------*/

#ifndef _SYSTICK_H
#define _SYSTICK_H

 /* Includes -------------------------------------------------------------------------------*/
/* Private Typedef -------------------------------------------------------------------------*/
/* Private Define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
void SysTick_Initial(void);
void SysTick_Handler(void);

uint8_t SysTick_1msec(void);
uint8_t SysTick_5msec(void);
uint8_t SysTick_10msec(void);
uint8_t SysTick_20msec(void);
uint8_t SysTick_50msec(void);
uint8_t SysTick_100msec(void);
uint8_t SysTick_200msec(void);
uint8_t SysTick_500msec(void);
uint8_t SysTick_1000msec(void);
/* Private functions -----------------------------------------------------------------------*/

#endif
