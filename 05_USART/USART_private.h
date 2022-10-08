/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : USART_PRIVATE_H                                       */
/*Description    : An educational USART driver File for STM32F103C MC    */
/* Date          : 11 03 2022                                            */
/* Version       : V01                                                   */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H


/*USART1_MODE Options:*/
#define  USART_SYNCRONOUS  2
#define  USART_ASYNCRONOUS 4
#define  USART_LIN         6
/*----------------------------------------------------------------------------*/
/*USART1_COMMUNICATION_MODE Options:*/
#define USART_TX_ONLY                 0x08
#define USART_RX_ONLY                 0x04
#define USART_FULL_DUPLEX             0x0C
#define USART_SINGLE_WIRE_HALF_DUPLEX 0x1C
/*----------------------------------------------------------------------------*/
/*USART1_STOPBITS_NUM Options:*/
#define USART_ONE_STOPBIT     0
#define USART_TWO_STOPBIT     2
//(smart card configuration only)//
#define USART_HALF_STOPBIT    1
#define USART_ONEHALF_STOPBIT 3
/******************************************************************************/
typedef struct
{
  volu32 SR;
  volu32 DR;
  volu32 BRR;
  volu32 CR1;
  volu32 CR2;
  volu32 CR3;
  volu32 GTPR;
} USART_RegType;

#define USART1_BASE_ADDRESS 0x40013800
//#define USART2_BASE_ADDRESS 0x40004400

#define MyUSART1    ((USART_RegType*)USART1_BASE_ADDRESS) //on ABP2 Bus
//#define MyUSART2    ((USART_RegType*)USART2_BASE_ADDRESS) //on ABP1 Bus
/******************************************************************************/
#if USART1_MODE == USART_SYNCRONOUS
/*USART1 Clock Options definition*/
#define USART_IDLE_LOW         0
#define USART_IDLE_HIGH        1
#define FIRST_CLK_CAPTURING    0
#define SECOND_CLK_CAPTURING   1
#endif /*USART1_MODE*/
/*----------------------------------------------------------------------------*/
#define MAX_DIV_MANTISSA 0xFFF
/*----------------------------------------------------------------------------*/
/*PRIVATE ACCESS Flag interrupt EN*/
#define USART_IDLE_LINE        4
#define USART_TX_REG_EMPTY     7
/******************************************************************************/
/*******************************PRIVATE variables******************************/
//If TX-ONLY is chosen, these variables are not needed//
#if USART1_COMMUNICATION_MODE != USART_TX_ONLY
void(*clBk_RxData) (u16 Data);
void(*clBk_RxArr)  (u16 *Data);
//u16 *Glbl_u16RxArrPtr =NULL;
u16 *Glbl_u16RxArrPtr;
u16  Glbl_u16RxArrWidth =0;
u16  Glbl_u16RxArrIndex =0;
u8 IRQ1_SnglRxShotF =0;
u8 IRQ1_MltiRxShotF =0;
//u8 IRQ1_RxHandleF =0;
#endif /*TX-only non-related variables*/

//If RX-ONLY is chosen, these variables are not needed//
#if USART1_COMMUNICATION_MODE != USART_RX_ONLY
void(*clBk_TxCmplt)(void);
u8 TcCmpltCallBackIsSetF = 0;
//u16 *Glbl_u16TxArrPtr =NULL;
u16 *Glbl_u16TxArrPtr;
u16  Glbl_u16TxArrWidth =0;
u16  Glbl_u16TxArrIndex =0;
u8 IRQ1_SnglTxShotF =0;
u8 IRQ1_MltiTxShotF =0;
//u8 IRQ1_TxHandleF =0;
#endif /*RX-only nonrelated variables*/

void(*clBk_ErrDetect) (u8 USART1_ErrType);
u8 ErrCallBackIsSetF = 0;
/******************************************************************************/
#endif /*USART_PRIVATE_H*/
