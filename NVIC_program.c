/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          :                                                       */
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
  local_u8tempIPR  = Ptr_ExPriphIRQ->u8supPriority;
  #elseif GROUP_PRIORITY_BITS == 4 && SUP_PRIORITY_BITS == 0
  local_u8tempIPR  = Ptr_ExPriphIRQ->u8GroupPriority;
  #else
  local_u8tempIPR  = (Ptr_ExPriphIRQ->u8GroupPriority) <<SUP_PRIORITY_BITS;
  local_u8tempIPR +=  Ptr_ExPriphIRQ->u8supPriority;
  #endif
  MY_NVIC->NVIC_IPR[(Ptr_ExPriphIRQ->u8IRQid)] = local_u8tempIPR<<4;
}

void NVIC_voidEnExtIRQ  (u8 Copy_u8IRQ_ID){
  if      (Copy_u8IRQ_ID < 31){
    MY_NVIC->NVIC_ISER[0] = 1 << Copy_u8IRQ_ID;
  }
  else if (Copy_u8IRQ_ID < 64){
    MY_NVIC->NVIC_ISER[1] = 1 << Copy_u8IRQ_ID;
  }
}

void NVIC_voidDisExtIRQ (u8 Copy_u8IRQ_ID){
  if      (Copy_u8IRQ_ID < 31){
    MY_NVIC->NVIC_ICER[0] = 1 << Copy_u8IRQ_ID;
  }
  else if (Copy_u8IRQ_ID < 64){
    MY_NVIC->NVIC_ICER[1] = 1 << Copy_u8IRQ_ID;
  }
}

void NVIC_voidSetPending (u8 Copy_u8IRQ_ID){
  if      (Copy_u8IRQ_ID < 31){
    MY_NVIC->NVIC_ISPR[0] = 1 << Copy_u8IRQ_ID;
  }
  else if (Copy_u8IRQ_ID < 64){
    MY_NVIC->NVIC_ISPR[1] = 1 << Copy_u8IRQ_ID;
  }
}

void NVIC_voidClrPending (u8 Copy_u8IRQ_ID){
  if      (Copy_u8IRQ_ID < 31){
    MY_NVIC->NVIC_ICPR[0] = 1 << Copy_u8IRQ_ID;
  }
  else if (Copy_u8IRQ_ID < 64){
    MY_NVIC->NVIC_ICPR[1] = 1 << Copy_u8IRQ_ID;
  }
}


u32  NVIC_u32GetPending (u8 Copy_u8IRQ_ID){
  if      (Copy_u8IRQ_ID < 31){
    return (GET_BIT(MY_NVIC->(NVIC_ISPR[0]),Copy_u8IRQ_ID) == TRUE);
  }
  else if (Copy_u8IRQ_ID < 64){
    return (GET_BIT(MY_NVIC->(NVIC_ISPR[1]),Copy_u8IRQ_ID) == TRUE);
  }
}
u32  NVIC_u32GetActive (u8 Copy_u8IRQ_ID){
  if      (Copy_u8IRQ_ID < 31){
    return (GET_BIT(MY_NVIC->(NVIC_IABR[0]),Copy_u8IRQ_ID) == TRUE);
  }
  else if (Copy_u8IRQ_ID < 64){
    return (GET_BIT(MY_NVIC->(NVIC_IABR[1]),Copy_u8IRQ_ID) == TRUE);
  }
}
