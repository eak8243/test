/*------------------------------------------------------------------------------------------
 * Project	:	RoboFarming
 * File		  :	sistivk.c
 * MCU		  :	STM32F100RBT6B
 * Compiler	:	Keil uVision 4 MDK-ARM 4.14
 * Modify	  :	
 * Date		  :	01/02/2012
 *------------------------------------------------------------------------------------------*/

 /* Includes --------------------------------------------------------------------------------*/
#include "header.h"

/* Private Typedef -------------------------------------------------------------------------*/
/* Private Define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
extern uint32_t timecnt;

static uint8_t _5msec;
static uint8_t _20msec;
static uint8_t _10msec;
static uint8_t _50msec;
static uint8_t _100msec;			
static uint8_t _200msec;
static uint8_t _500msec;
static uint8_t _1sec;
static uint8_t _1minute ;

static uint8_t base1msec=0;
static uint8_t base5msec=0;
static uint8_t base20msec=0;
static uint8_t base10msec=0;
static uint8_t base50msec=0;
static uint8_t base100msec=0;
static uint8_t base200msec=0;
static uint8_t base500msec=0;
static uint8_t base1000msec=0;
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/
void SysTick_Initial(void)
{
	//config: 1 KHz 
	if (SysTick_Config(SystemCoreClock / 18000))
// 	if (SysTick_Config(168000))   //168M/1000
  	{ 
  		//- have some error
    	while (1);
  	}
  	
	//note: set for overflow not same time   
	_5msec=0;
	_10msec=1;
	_20msec=2;
	_50msec=1;
	_100msec=2;
	_200msec=0;
	_500msec=1;
	_1sec=1;
	_1minute=0;
}

/* Export for main routine ---------------------------------------------------------------*/
uint8_t SysTick_1msec(void)
{
	if(base1msec)
	{
		base1msec--;
		return 1;	
	}	
	return 0;
}

uint8_t SysTick_5msec(void)
{
	if(base5msec)
	{
		base5msec--;
		return 1;	
	}	
	return 0;
} 

uint8_t SysTick_10msec(void)
{
	if(base10msec)
	{
		base10msec--;
		return 1;	
	}	
	return 0;
}

uint8_t SysTick_20msec(void)
{
	if(base20msec)
	{
		base20msec--;
		return 1;	
	} 	
	return 0;
}

uint8_t SysTick_50msec(void)
{
	if(base50msec)
	{
		base50msec--;
		return 1;	
	}	
	return 0;
}

uint8_t SysTick_100msec(void)
{
	if(base100msec)
	{
		base100msec--;
		return 1;	
	} 	
	return 0;
}  

uint8_t SysTick_200msec(void)
{
	if(base200msec)
	{
		base200msec--;
		return 1;	
	}	
	return 0;
}

uint8_t SysTick_500msec(void)
{
	if(base500msec)
	{
		base500msec--;
		return 1;	
	}  	
	return 0;
}
   
uint8_t SysTick_1000msec(void)
{
	if(base1000msec)
	{
		base1000msec--;
		return 1;	
	}	
	return 0;
}

/* Interrupt service routine--------------------------------------------------------------------------*/
// Interrupt call every 1 msec
void SysTick_Handler(void)
{  
  //  1 msec zone
	base1msec++;	
  	
	if(++_5msec>=5)
  	{
    	// 5 msec zone 
      _5msec = 0;
    	base5msec++;     	  	
  	}
    	
  if(++_10msec>=10 )
  {
    // 10 msec zone
    _10msec = 0;
    base10msec++;      

  	if(++_20msec>=2)
    {
      // 20 msec zone 
      _20msec = 0;
      base20msec++;             
    }
		
    if(++_50msec>=5)
    {
      // 50 msec zone 
      _50msec = 0;
      base50msec++;    
    }
		
    if(++_100msec >= 10)
    {
      // 100 msec zone
      _100msec = 0;
     	base100msec++;
				
    		if(++_200msec>=2)
      	{
	  			// 200 msec zone 
          _200msec = 0;
     			base200msec++;
      	}
	
      	if(++_500msec >= 5)    
      	{
				  // 500 msec zone
          _500msec = 0;
				  base500msec++;
          
				  if(++_1sec >= 2)
				  {
			  	  // 1000 msec
            _1sec = 0;   		   
   		      base1000msec++;

			  	  if (++_1minute >= 60)
			  	  {
						  // 1 min
              _1minute =0;
			  	  }
  			  }
    		}
  	}
	}	
}
