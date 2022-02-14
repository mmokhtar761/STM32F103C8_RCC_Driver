/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : NVIC_CONFIG_H                                         */
/*Describtion    : An educational NVIC driver File for STM32F103C MC     */
/* Date          :                                                       */
/* Version       : V01.1                                                 */
/* GitHub        :                                                       */
/*************************************************************************/
#ifndef NVIC_CONFIG_H
#define NVIC_CONFIG_H

/*
  >Priority is described by 4 bits in STM32F
  >Priorty levels increases as bits increases
  >Ex: n bits give 2power(n) levels
*/
#define GROUP_PRIORITY_BITS 2
#define SUB_PRIORITY_BITS   2


#endif  NVIC_CONFIG_H
