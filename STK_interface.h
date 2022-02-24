/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : STK_INTERFACE_H                                       */
/*Describtion    : An educational SysTick driver File for STM32F103C MC  */
/* Date          : FEB 2022                                              */
/* Version       : V2.1-> The interrupt enabling is separated            */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/

#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

#define MAX_SYS_TICKS 0xFFFFFF
#define STK_CLK_SOURCE_AHB_BUS       (1)
#define STK_CLK_SOURCE_AHB_BUS_DIV_8 (0)
/*
NOTE:
	The time of ticks is dependent on AHB_BUS frequency. (AHB or AHB/8)Hz
	Max ticks can this timer receive is 2^(32) -> 0xFFFFFFFF -> 4294967295
*/

/******************************************************************************/
/**************************** Basic STK Functions *****************************/
/******************************************************************************/
/*
Options:
    STK_CLK_SOURCE_AHB_BUS
    STK_CLK_SOURCE_AHB_BUS_DIV_8
*/
void STK_voidInitSysTickClk (u8 Copy_u8CLK_Option);
/*----------------------------------------------------------------------------*/
/*
  Copy_u8CLK_Option is the needed number of ticks that CPU will be busy with
    *On calling STK_voidSetBusyWait(), The CPU  will be busy with it and will not
        go-out before finishing the required ticks.
*/
void STK_voidSetBusyWait    (u32 Copy_TicksNum);
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/******************** Asynchronous SysTick timer functions ********************/
/******************************************************************************/
/*
Note:
	  *The SysTick exception request must be enabled using STK_voidEnInterrupt(void) func
 	  *These functions have no effect with STK_voidSetBusyWait ().
      *Call back func must be set before any call of other Asynchronous functions.
      *In STK_voidSetBusyWait() The CPU  will be busy with it and will not
        go-out before finishing the required ticks.
*/
/*----------------------------------------------------------------------------*/
/*
  Sets the function of SysTick Interrupt handler
*/
void STK_voidSetCallBackFunc (void (*ptr)(void));
/*----------------------------------------------------------------------------*/
/*
  STK_u8ReadFlag( void ) returns 1 if timer counted to 0 since last
  time this was read.
*/
void STK_voidEnInterrupt(void);
void STK_voidDisInterrupt(void);
u8 STK_u8ReadFlag( void );
/*----------------------------------------------------------------------------*/
/*
  Starts an asynchronous timer with Single-shot having an Interrupt on 1 to 0 tick
  (If enabled)
*/
void STK_voidSetSingleShotTimerIR (u32 Copy_u32TicksNum);
/*----------------------------------------------------------------------------*/
/*
  Starts an asynchronous timer with Multi-shot having an Interrupt
  on each 1 to 0 tick (If enabled).
*/
void STK_voidSetMultiShotTimerIR  (u32 Copy_u32TicksNum);
/*----------------------------------------------------------------------------*/
/*
  Stops SysTick timer counting
*/
void STK_voidStopSysTick   (void);
/*----------------------------------------------------------------------------*/
/*
  Resumes SysTick timer counting from the last point it stopped in
*/
void STK_voidResumeSysTick (void);
/*----------------------------------------------------------------------------*/
/*
  Returns the remaining/elapsed ticks in the timer
*/
u32 STK_u32GetElapsedTicks   (void);
u32 STK_u32GetRemainingTicks (void);
/*----------------------------------------------------------------------------*/
/******************************************************************************/
#endif  /*STK_INTERFACE_H*/
