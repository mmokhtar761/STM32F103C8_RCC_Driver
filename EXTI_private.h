/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : EXTI_PRIVATE_H                                        */
/*Description    : An educational EXTI driver File for STM32F103C MC     */
/* Date          : 10 FEB-2022                                           */
/* Version       : V1.1 -> essential tests are passed                    */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

#if defined(EXTI5_LINE)||defined(EXTI6_LINE)||defined(EXTI7_LINE)||defined(EXTI8_LINE)||defined(EXTI9_LINE)
#define EXTI9_5_LINES_IRQ   9
#endif

#if defined(EXTI10_LINE)||defined(EXTI11_LINE)||defined(EXTI12_LINE)||defined(EXTI13_LINE)||defined(EXTI14_LINE)||defined(EXTI15_LINE)
#define EXTI15_10_LINES_IRQ 15
#endif

#define EXTI_LINES_NUM 19

static void (*EXTI_CallBack[EXTI_LINES_NUM])(void);

typedef struct
{
  volu32 EXTI_IMR;
  volu32 EXTI_EMR;
  volu32 EXTI_RTSR;
  volu32 EXTI_FTSR;
  volu32 EXTI_SWIER;
  volu32 EXTI_PR;
} EXTI_RegType;

#define EXTI_BASE_ADDRESS   0x40010400
#define MY_EXTI             ((EXTI_RegType *)EXTI_BASE_ADDRESS)

#endif /*EXTI_PRIVATE_H*/
