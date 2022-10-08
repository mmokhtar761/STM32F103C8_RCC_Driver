/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : NVIC_PRIVATE_H                                        */
/*Description    : An educational NVIC driver File for STM32F103C MC     */
/* Date          : FEB 2022                                              */
/* Version       : V01.2                                                 */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H


/*********************External peripherals IRQ control REGs*********************/
typedef struct
{
  volu32 NVIC_ISER[2]; //IRQ set-enable registers ID 0-63
  u32   RESERVED0[30];
  volu32 NVIC_ICER[2]; //IRQ clear-enable registers ID 0-63
  u32   RESERVED1[30];
  volu32 NVIC_ISPR[2]; //IRQ set-pending registers ID 0-63
  u32   RESERVED2[30];
  volu32 NVIC_ICPR[2]; //IRQ clear-pending registers ID 0-63
  u32   RESERVED3[30];
  volu32 NVIC_IABR[2]; //IRQ active bit registers ID 0-63
  u32   RESERVED4[62];
  volu32 NVIC_IPR[59]; //IRQ priority registers
} NVIC_RegType;

#define NVIC_BASE_ADDRESS  0xE000E100
#define MY_NVIC            ((NVIC_RegType *)0xE000E100)

#define NVIC_SCB_AIRCR     *((volu32*)0xE000ED0C)
#define AIRCR_KEY          0x5FA


/*
  Evaluated to 0 if (id < 32)
          and to 1 if (id > 32)
*/
#define REG_FIRST_SECOND(id) (id/32)
/******************************************************************************/
u8 prvtu8Index=0;


#endif /* NVIC_PRIVATE_H*/
