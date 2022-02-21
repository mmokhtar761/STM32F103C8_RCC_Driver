/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : STK_PRIVATE_H                                         */
/*Describtion    : An educational SysTick driver File for STM32F103C MC  */
/* Date          : FEB 2022                                              */
/* Version       : V02-> The first compiled version&CallBackFunc is added*/
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

#define MAX_SYS_TICKS 0xFFFFF

void (*CallBackFunc)(void);
void SysTick_Handler (void);
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
