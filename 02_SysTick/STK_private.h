/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : STK_PRIVATE_H                                         */
/*Describtion    : An educational SysTick driver File for STM32F103C MC  */
/* Date          : FEB 2022                                              */
/* Version       : V2.1-> The interrupt enabling is separated            */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

#define MAX_SYS_TICKS 0xFFFFFF

void (*CallBackFunc)(void);
void SysTick_Handler (void);
u8 Prvt_u8SingleShotFlag  = 1;
u8 Prvt_u8CallBackFnIsSet = 0;
typedef struct
{
  volu32 CTRL;
  volu32 LOAD;
  volu32 VAL;
  volu32 CALIB;
} STK_RegType;

#define STK_BASE_ADDRESS   0xE000E010
#define MY_STK             ((STK_RegType *)STK_BASE_ADDRESS)


#endif /*STK_PRIVATE_H*/
