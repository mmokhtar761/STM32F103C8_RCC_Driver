/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : EXTI_PRIVATE_H                                        */
/*Describtion    : An educational EXTI driver File for STM32F103C MC     */
/* Date          :                                                       */
/* Version       : V01.0                                                 */
/* GitHub        :                                                       */
/*************************************************************************/
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

#ifdef EXTI5_LINE||EXTI6_LINE||EXTI7_LINE||EXTI8_LINE||EXTI9_LINE
#define EXTI9_5_LINES_IRQ   9
#endif

#ifdef EXTI10_LINE||EXTI11_LINE||EXTI12_LINE||EXTI13_LINE||EXTI14_LINE||EXTI15_LINE
#define EXTI15_10_LINES_IRQ 15
#endif

#define EXTI_LINES_NUM 19
static void (*EXTI_CallBack[EXTI_LINES_NUM])(void) = NULL;


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


 //void (*ptr)(void)

#endif /*EXTI_PRIVATE_H*/
