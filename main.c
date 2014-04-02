/**
  ******************************************************************************
  * @file    SysTick/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "header.h"

/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup SysTick_Example
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t CCR1_Val = 1558/2;
uint16_t CCR2_Val = 1558/2;
uint16_t CCR3_Val = 1558/2;
uint16_t CCR4_Val = 83;
uint16_t PrescalerValue = 0;


#define ANGLE_STEP_RATE 1.0 //i.e the Angle Resolution
#define PI 3.14159
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
void computeSineLookupTable1(int *sineLookupTable1)
{
    float angle;
    int i;
    for(i=0; i<360; i++)
    {
        angle = i * ANGLE_STEP_RATE ;
        *(sineLookupTable1+i) = rint(583 + 582* sin( angle * (PI/180) )); //converting angle to radians
    }
}
void init_gpio()
{
     RCC->AHB1ENR |= 0x00000001; // Enable clock for GPIOA
     RCC->APB1ENR |= 0x20000000; // Enable clock for DAC 
     DAC->CR |= 0x00010001; // DAC control reg, both channels ON 
     GPIOA->MODER |= 0x00000f00; // PA04, PA05 are analog outputs
}
void TIM_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* GPIOC and GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB, ENABLE);
  
  /* GPIOC Configuration: TIM3 CH1 (PC6) and TIM3 CH2 (PC7) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
  
  /* GPIOB Configuration:  TIM3 CH3 (PB0) and TIM3 CH4 (PB1) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 

  /* Connect TIM3 pins to AF2 */  
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3); 
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3); 
}
void PWM_GEN()
{
       PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 28000000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 1558;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM3, ENABLE);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
}
int main(void)
{
//a4 a5
			//int sineLookupTable1[360];
	int i=0;
	int j=0;
     int k=0;
	int state_sag=0;
	int round=0;
     static unsigned int ay[]={583,593,603,613,624,634,644,654,664,674,684,694,704,714,724,734,743,753,763,772,782,792,801,810,820,829,838,847,856,865,874,883,891,900,908,917,925,933,941,949,957,965,972,980,987,995,1002,1009,1016,1022,1029,1035,1042,1048,1054,1060,1065,1071,1077,1082,1087,1092,1097,1102,1106,1110,1115,1119,1123,1126,1130,1133,1137,1140,1142,1145,1148,1150,1152,1154,1156,1158,1159,1161,1162,1163,1164,1164,1165,1165,1165,1165,1165,1164,1164,1163,1162,1161,1159,1158,1156,1154,1152,1150,1148,1145,1142,1140,1137,1133,1130,1126,1123,1119,1115,1110,1106,1102,1097,1092,1087,1082,1077,1071,1065,1060,1054,1048,1042,1035,1029,1022,1016,1009,1002,995,987,980,972,965,957,949,941,933,925,917,908,900,891,883,874,865,856,847,838,829,820,810,801,792,782,772,763,753,743,734,724,714,704,694,684,674,664,654,644,634,624,613,603,593,583,573,563,553,542,532,522,512,502,492,482,472,462,452,442,432,423,413,403,394,384,374,365,356,346,337,328,319,310,301,292,283,275,266,258,249,241,233,225,217,209,201,194,186,179,171,164,157,150,144,137,131,124,118,112,106,101,95,89,84,79,74,69,64,60,56,51,47,43,40,36,33,29,26,24,21,18,16,14,12,10,8,7,5,4,3,2,2,1,1,1,1,1,2,2,3,4,5,7,8,10,12,14,16,18,21,24,26,29,33,36,40,43,47,51,56,60,64,69,74,79,84,89,95,101,106,112,118,124,131,137,144,150,157,164,171,179,186,194,201,209,217,225,233,241,249,258,266,275,283,292,301,310,319,328,337,346,356,365,374,384,394,403,413,423,432,442,452,462,472,482,492,502,512,522,532,542,553,563,573
		 };
     static unsigned int az[]={583,588,593,599,604,609,614,620,625,630,635,640,645,650,656,661,666,671,676,681,686,691,695,700,705,710,715,719,724,728,733,738,742,746,751,755,759,764,768,772,776,780,784,788,791,795,799,802,806,809,813,816,819,823,826,829,832,835,837,840,843,845,848,850,853,855,857,859,861,863,865,867,868,870,871,873,874,875,876,877,878,879,880,881,881,882,882,883,883,883,883,883,883,883,882,882,881,881,880,879,878,877,876,875,874,873,871,870,868,867,865,863,861,859,857,855,853,850,848,845,843,840,837,835,832,829,826,823,819,816,813,809,806,802,799,795,791,788,784,780,776,772,768,764,759,755,751,746,742,738,733,728,724,719,715,710,705,700,695,691,686,681,676,671,666,661,656,650,645,640,635,630,625,620,614,609,604,599,593,588,583,578,573,567,562,557,552,546,541,536,531,526,521,516,510,505,500,495,490,485,480,475,471,466,461,456,451,447,442,438,433,428,424,420,415,411,407,402,398,394,390,386,382,378,375,371,367,364,360,357,353,350,347,343,340,337,334,331,329,326,323,321,318,316,313,311,309,307,305,303,301,299,298,296,295,293,292,291,290,289,288,287,286,285,285,284,284,283,283,283,283,283,283,283,284,284,285,285,286,287,288,289,290,291,292,293,295,296,298,299,301,303,305,307,309,311,313,316,318,321,323,326,329,331,334,337,340,343,347,350,353,357,360,364,367,371,375,378,382,386,390,394,398,402,407,411,415,420,424,428,433,438,442,447,451,456,461,466,471,475,480,485,490,495,500,505,510,516,521,526,531,536,541,546,552,557,562,567,573,578
	};
          


     init_gpio();
     SysTick_Initial();
     TIM_Config();
     PWM_GEN();


	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

  /* Turn on LED4 and LED5 */
	STM_EVAL_LEDOn(LED4);
	STM_EVAL_LEDOn(LED5);

  while (1)
  {		
		//---------------------------------------------------------------------------
          if(SysTick_1msec())//basetime
		{
			STM_EVAL_LEDToggle(LED3);
			if(state_sag==0)
			{
				TIM_OCInitStructure.TIM_Pulse = ay[i];  //PC6
			}
			else if(state_sag==1)
			{
				TIM_OCInitStructure.TIM_Pulse = az[i];  //PC6
			}
               TIM_OC1Init(TIM3, &TIM_OCInitStructure);
               i++;
               

               
			if(state_sag==0)
			{
				TIM_OCInitStructure.TIM_Pulse = ay[j+120];  //PC6
			}
			else if(state_sag==1)
			{
				TIM_OCInitStructure.TIM_Pulse = az[j+120];  //PC6
			}
               TIM_OC2Init(TIM3, &TIM_OCInitStructure);
               j++;
               if(j+120>359)
               {
                    j=-120;
               }
               
			if(state_sag==0)
			{
				TIM_OCInitStructure.TIM_Pulse = ay[k+240];  //PC6
			}
			else if(state_sag==1)
			{
				TIM_OCInitStructure.TIM_Pulse = az[k+240];  //PC6
			}
               TIM_OC3Init(TIM3, &TIM_OCInitStructure);
               k++;
               if(k+240>359)
               {
				k=-240;
               }
			
			if(i>359)
               {
				i=0;
				round++;
				if(round%3==0)
				{
					state_sag=1;
				}
				else
				{
					state_sag=0;
					
				}
				
				if(round==300)
				{
					round=0;
				}
				
               }
               
               
		} 

	}
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/