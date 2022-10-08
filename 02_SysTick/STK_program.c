/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          :                                                       */
/*Description    : An educational SysTick driver File for STM32F103C MC  */
/* Date          : FEB 2022                                              */
/* Version       : V2.1-> The interrupt enabling is separated            */
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
  MY_STK->CTRL= Copy_u8CLK_Option<<2; //Config CLK source bit
}
/*----------------------------------------------------------------------------*/
void STK_voidSetBusyWait    (u32 Copy_u32TicksNum)
{
  BIT_L(MY_STK->CTRL,0);             //Make-sure the timer is not counting
  MY_STK->VAL  = 0;                  //Clears the timer register
  if (Copy_u32TicksNum > MAX_SYS_TICKS)
  {
      MY_STK->LOAD = MAX_SYS_TICKS;      //Initializing the value needed
      BIT_H(MY_STK->CTRL,0);             //Enables the timer to start counting
      Copy_u32TicksNum -= MAX_SYS_TICKS; //Getting the increase in ticks to be reloaded
      while (!GET_BIT(MY_STK->CTRL,16)); //Waits the flag to be 1
      BIT_L(MY_STK->CTRL,0);             //Disable the timer to reload it
      MY_STK->VAL  = 0;                  //Clears the timer register
  }
  MY_STK->LOAD = Copy_u32TicksNum;   //Initializing the value needed
  BIT_H(MY_STK->CTRL,0);             //Enables the timer to start counting
  while (!GET_BIT(MY_STK->CTRL,16)); //Waits the flag to be 1
  BIT_H(MY_STK->CTRL,0);             //Disable the timer counting
}
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/******************** Asynchronous SysTick timer functions ********************/
/******************************************************************************/
void STK_voidSetCallBackFunc (void (*ptr)(void))
{
  CallBackFunc = ptr;
  Prvt_u8CallBackFnIsSet = 1;
}
/*----------------------------------------------------------------------------*/
void STK_voidEnInterrupt(void)
{
	BIT_H(MY_STK->CTRL,1);             //Asserts the SysTick exception request
}
void STK_voidDisInterrupt(void)
{
	BIT_L(MY_STK->CTRL,1);             //Disable the SysTick exception request
}
u8 STK_u8ReadFlag( void )
{
	   /*Returns 1 if timer counted to since last time this was read*/
	return ( GET_BIT( MY_STK->CTRL , 16 ) );
}
/*----------------------------------------------------------------------------*/
void STK_voidSetSingleShotTimerIR (u32 Copy_u32TicksNum)
{
  MY_STK->VAL  = 0;                 //Clears the timer register
  MY_STK->LOAD = Copy_u32TicksNum;  //Initializing the value needed
  BIT_H(MY_STK->CTRL,0);            //Enables the timer to start counting
  Prvt_u8SingleShotFlag =1;
}
/*----------------------------------------------------------------------------*/
void STK_voidSetMultiShotTimerIR  (u32 Copy_u32TicksNum)
{
  MY_STK->VAL  = 0;                  //Clears the timer register
  MY_STK->LOAD = Copy_u32TicksNum-1; //Initializing the value needed (Multi shot needs n-1 val)
  BIT_H(MY_STK->CTRL,0);             //Enables the timer to start counting
  Prvt_u8SingleShotFlag =0;
}
/*----------------------------------------------------------------------------*/
void STK_voidStopSysTick   (void)
{
  BIT_L(MY_STK->CTRL,0);
}
void STK_voidResumeSysTick (void)
{
  BIT_H(MY_STK->CTRL,0);
}
/*----------------------------------------------------------------------------*/
u32 STK_u32GetElapsedTicks   (void)
{
  return (MY_STK->LOAD - MY_STK->VAL);
}
u32 STK_u32GetRemainingTicks (void)
{
  return (MY_STK->VAL);
}
/*----------------------------------------------------------------------------*/
void SysTick_Handler (void)
{
  /*If only single shot is need, stop the timer*/
  if (Prvt_u8SingleShotFlag) BIT_L(MY_STK->CTRL,0);
  /*Clears the flag of CTRL register by reading it*/
  MY_STK->CTRL=MY_STK->CTRL;
  /*Call the preset function.(only if already set)*/
  if (Prvt_u8CallBackFnIsSet) CallBackFunc ();
}
/******************************************************************************/
