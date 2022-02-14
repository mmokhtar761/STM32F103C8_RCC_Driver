/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          :                                                       */
/*Describtion    : An educational NVIC driver File for STM32F103C MC     */
/* Date          :                                                       */
/* Version       : V01.1                                                 */
/* GitHub        :                                                       */
/*************************************************************************/
#include "MANIPULATORS.h"
#include "STD_TYPES.h"

#include "NVIC_interface.h"
#include "NVIC_config.h"
#include "NVIC_private.h"


void NVIC_voidinitNVIC (void){

  #if SUB_PRIORITY_BITS + GROUP_PRIORITY_BITS != 4
      #error "Priority is described by 4 bits ONLY"
  #endif
  /*
    It is noted that :
       PRIGROUP value = subpriority bits + 3
  */
  NVIC_SCB_AIRCR= ((SUP_PRIORITY_BITS + 3)|(AIRCR_KEY<<8))<<8;
}

void NVIC_voidEnDisExternalPeripheralIRQ(u8 Copy_u8ENorDIS){
  static u32 local_u32lastEnMask[2] = {0xFFFFFFFF,0xFFFFFFFF};
  if      (Copy_u8ENorDIS == EN ){
    MY_NVIC->(NVIC_ISER[0]) = local_u32lastEnMask[0];
    MY_NVIC->(NVIC_ISER[1]) = local_u32lastEnMask[1];
  }elseif (Copy_u8ENorDIS == DIS ){
    local_u32lastEnMask[0] = MY_NVIC->(NVIC_ISER[0]);
    local_u32lastEnMask[0] = MY_NVIC->(NVIC_ISER[1]);
    MY_NVIC->(NVIC_ICER[0]) = 0xFFFFFFFF;
    MY_NVIC->(NVIC_ICER[1]) = 0xFFFFFFFF;
  }
}

void NVIC_voidConfigIRQpriority (ExPriphIRQ_type * Ptr_ExPriphIRQ){
  u8 local_u8tempIPR=0;
  #if     GROUP_PRIORITY_BITS == 0 && SUP_PRIORITY_BITS == 4
  local_u8tempIPR  = (Ptr_ExPriphIRQ->u8supPriority)   &0xF; //Only first 4bits
  #elseif GROUP_PRIORITY_BITS == 4 && SUP_PRIORITY_BITS == 0
  local_u8tempIPR  = (Ptr_ExPriphIRQ->u8GroupPriority) &0xF; //Only first 4bits
  #else
  local_u8tempIPR  = (Ptr_ExPriphIRQ->u8GroupPriority) <<SUP_PRIORITY_BITS;
  local_u8tempIPR +=  Ptr_ExPriphIRQ->u8supPriority;
  #endif
  MY_NVIC->NVIC_IPR[(Ptr_ExPriphIRQ->u8IRQid)] = local_u8tempIPR<<4;
}

void NVIC_voidEnExtIRQ  (u8 Copy_u8IRQ_ID){
  /*
    REG_FIRST_SECOND(Copy_u8IRQ_ID)  Evaluateted to 0 if (id < 32)
                                             and to 1 if (id > 32)
  */
  MY_NVIC->NVIC_ISER[REG_FIRST_SECOND(Copy_u8IRQ_ID)] = 1 << Copy_u8IRQ_ID;
}

void NVIC_voidDisExtIRQ (u8 Copy_u8IRQ_ID){
  /*
    REG_FIRST_SECOND(Copy_u8IRQ_ID)  Evaluateted to 0 if (id < 32)
                                             and to 1 if (id > 32)
  */
  MY_NVIC->NVIC_ICER[REG_FIRST_SECOND(Copy_u8IRQ_ID)] = 1 << Copy_u8IRQ_ID;
}

void NVIC_voidSetPending (u8 Copy_u8IRQ_ID){
  /*
    REG_FIRST_SECOND(Copy_u8IRQ_ID)  Evaluateted to 0 if (id < 32)
                                             and to 1 if (id > 32)
  */
  MY_NVIC->NVIC_ISPR[REG_FIRST_SECOND(Copy_u8IRQ_ID)] = 1 << Copy_u8IRQ_ID;
}

void NVIC_voidClrPending (u8 Copy_u8IRQ_ID){
  /*
    REG_FIRST_SECOND(Copy_u8IRQ_ID)  Evaluateted to 0 if (id < 32)
                                             and to 1 if (id > 32)
  */
  MY_NVIC->NVIC_ICPR[REG_FIRST_SECOND(Copy_u8IRQ_ID)] = 1 << Copy_u8IRQ_ID;
}


u32  NVIC_u32GetPending (u8 Copy_u8IRQ_ID){
/*
  The total expression returns TRUE  (1) if the IRQ is Pending
                           and FALSE (0) if the IRQ is NOT Pending
*/
  return (GET_BIT(MY_NVIC->(NVIC_ISPR[REG_FIRST_SECOND(Copy_u8IRQ_ID)]),Copy_u8IRQ_ID));
}

u32  NVIC_u32GetActive (u8 Copy_u8IRQ_ID){
  /*
    The total expression returns TRUE  (1) if the IRQ is Active
                             and FALSE (0) if the IRQ is NOT Active
  */
  return (GET_BIT(MY_NVIC->(NVIC_IABR[REG_FIRST_SECOND(Copy_u8IRQ_ID)]),Copy_u8IRQ_ID));
}
