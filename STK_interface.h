/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : STK_INTERFACE_H                                       */
/*Describtion    : An educational SysTick driver File for STM32F103C MC  */
/* Date          : FEB 2022                                              */
/* Version       : V02-> The first compiled version&CallBackFunc is added*/
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

//#define STOP_SYS_TICK   BIT_L(MY_STK->STK_CTRL,0)
//#define RESUME_SYS_TICK BIT_H(MY_STK->STK_CTRL,0)
#define STK_CLK_SOURCE_AHB_BUS       (1)
#define STK_CLK_SOURCE_AHB_BUS_DIV_8 (0)

/*
Options:
    STK_CLK_SOURCE_AHB_BUS
    STK_CLK_SOURCE_AHB_BUS_DIV_8
*/
void STK_voidInitSysTickClk (u8 Copy_u8CLK_Option);
/*
  Copy_u8CLK_Option is the needed number of ticks that CPU will be busy with
*/
void STK_voidSetBusyWait    (u32 Copy_TicksNum);


/**********************Asyncronous SysTick timer functions*********************/
/*
Note: *These functions have no effect with STK_voidSetBusyWait ().
      *In STK_voidSetBusyWait() The CPU  will be busy with it and will not
        go-out before finishing the required ticks.
      *Call back func must be set before any call of other Asyncronous functions.
*/


/*
  Starts an asyncronous timer with Single-shot having an Interrupt on 1 to 0 tick
*/
void STK_voidSetSingleShotTimerIR (u8 Copy_TicksNum);
/*
  Starts an asyncronous timer with Multi-shot having an Interrupt
  on each 1 to 0 tick.
*/
void STK_voidSetMultiShotTimerIR  (u8 Copy_TicksNum);
/*
  Sets the function of SysTick Interrupt handler
*/
void STK_voidSetCallBackFunc (void (*ptr)(void));
/*
  Starts SysTick timer countiong
*/
void STK_voidStartSysTick   (void);
/*
  Stops SysTick timer countiong
*/
void STK_voidStopSysTick   (void);
/*
  Resumes SysTick timer countiong
*/
void STK_voidResumeSysTick (void);

/*
  Returns the remaining/elapsed ticks in the timer
*/
u32 STK_u32GetElapsedTicks   (void);
u32 STK_u32GetRemainingTicks (void);

u8 STK_u8ReadFlag( void );

/******************************************************************************/
#endif  /*STK_INTERFACE_H*/
