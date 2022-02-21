/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          :                                                       */
/*Description    : An educational SysTick driver File for STM32F103C MC  */
/* Date          : FEB 2022                                              */
/* Version       : V02-> The first compiled version&CallBackFunc is added*/
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#include "STD_TYPES.h"
#include "MANIPULATOR.h"
#include "STK_interface.h"
#include "STK_config.h"
#include "STK_private.h"


void STK_voidInitSysTickClk (u8 Copy_u8CLK_Option)
{
  /*
  Options:
      STK_CLK_SOURCE_AHB_BUS           --> 1
      STK_CLK_SOURCE_AHB_BUS_DIV_8     --> 0
  */
  MY_STK->CTRL= Copy_u8CLK_Option<<2; //Sets CLK source bit
}

void STK_voidSetBusyWait    (u32 Copy_TicksNum)
{
  MY_STK->VAL  = 0;                 //Clears the timer register
  if (Copy_TicksNum > MAX_SYS_TICKS)
  {
      MY_STK->LOAD = MAX_SYS_TICKS;      //Initializing the value needed
      BIT_H(MY_STK->CTRL,0);             //Enables the timer to start counting
      Copy_TicksNum -= MAX_SYS_TICKS;
      while (!GET_BIT(MY_STK->CTRL,16)); //Waits the flag to be 1
      BIT_H(MY_STK->CTRL,1);             //Disable the timer to reload it
  }

  MY_STK->LOAD = Copy_TicksNum;     //Initializing the value needed
  BIT_H(MY_STK->CTRL,0);            //Enables the timer to start counting
  while (!GET_BIT(MY_STK->CTRL,16)); //Waits the flag to be 1
}



void SysTick_Handler (void)
{
  CallBackFunc ();
}

void STK_voidSetSingleShotTimerIR (u8 Copy_TicksNum)
{
  MY_STK->VAL  = 0;                 //Clears the timer register
  MY_STK->LOAD = Copy_TicksNum;     //Initializing the value needed
  BIT_H(MY_STK->CTRL,1);            //Asserts the SysTick exception request
  BIT_H(MY_STK->CTRL,0);            //Enables the timer to start counting
}
void STK_voidSetMultiShotTimerIR  (u8 Copy_TicksNum)
{
  MY_STK->VAL  = 0;                 //Clears the timer register
  MY_STK->LOAD = Copy_TicksNum;     //Initializing the value needed
  BIT_H(MY_STK->CTRL,1);            //Asserts the SysTick exception request
  BIT_H(MY_STK->CTRL,0);            //Enables the timer to start counting
}

void STK_voidSetCallBackFunc (void (*ptr)(void))
{
  CallBackFunc = ptr;
}


void STK_voidStartSysTick   (void)
{
  BIT_H(MY_STK->CTRL,0);
}
void STK_voidStopSysTick   (void)
{
  BIT_L(MY_STK->CTRL,0);
}
void STK_voidResumeSysTick (void)
{
  BIT_H(MY_STK->CTRL,0);
}


u32 STK_u32GetElapsedTicks   (void)
{
  return (MY_STK->LOAD - MY_STK->VAL);
}
u32 STK_u32GetRemainingTicks (void)
{
  return (MY_STK->VAL);
}

u8 STK_u8ReadFlag( void )
{
	return ( GET_BIT( MY_STK->CTRL , 16 ) );
}
