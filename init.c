/*------------------------------------------------------------------------------------------
 * Project	:	
 * FIle		:	init.c
 * MCU		:	STM32F100RBT6B
 * Compiler	:	Keil uVision 4 MDK-ARM 4.14
 * Modify	     :	Permsub Suksaengjun
 * Date		:	15/03/2012
 *------------------------------------------------------------------------------------------*/

/* Includes --------------------------------------------------------------------------------*/

#include "header.h"

/* Private Typedef -------------------------------------------------------------------------*/
/* Private Define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/ 
void RCC_Initial()
{ 
  /* error status */
  ErrorStatus HSEStartUpStatus;

  //RCC_DeInit();

  RCC_HSEConfig(RCC_HSE_ON);
  //HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS) {
    FLASH_PrefetchBufferCmd(ENABLE);
    FLASH_SetLatency(FLASH_Latency_2);

    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div1);

    RCC_PLLConfig(RCC_PLLSource_HSE,8,336,2,7);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08);
  }
     
}
void DAC_Initial()
{
      GPIO_InitTypeDef GPIO_InitStructure;
     RCC_APB1PeriphClockLPModeCmd(RCC_APB1Periph_DAC,ENABLE);
     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA, ENABLE);
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
     
}

void GPIO_Initial()
{

}

void NVIC_Initial()
{         
}


void USART_Initial()
{
}
 
void TIM_Initial()
{

}                                                     

void EXTI_Initial()
{

}    
