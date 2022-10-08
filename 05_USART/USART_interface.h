/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : USART_INTERFACE_H                                     */
/*Description    : An educational USART driver File for STM32F103C MC    */
/* Date          : 11 03 2022                                            */
/* Version       : V01                                                   */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

     /*********************** USART1 on APB2 Bus ***********************/
  /********************** Other USART s on APB1 Bus ***********************/

/*
              BUS_FREQ
BaudRate = --------------
           16 * USARTDIV
*/

/*
Lcl_u8DataWidth Options:
NOTE: data width includes parity bit (if enabled)
*/
#define  USART_8BIT_DATA 0x0000
#define  USART_9BIT_DATA 0x1000
/*
Lcl_u8ParitySel Options:
*/
#define  DIS_PARITY      0x000
#define  EN_EVEN_PARITY  0x400
#define  EN_ODD_PARITY   0x600
/*
 Returns
 --> USART_OK
  or
 --> USART_INVALID_BR
     This means the current BUS_FREQ can't deal the desired BaudRate
 */
/***Lcl_u8DataWidth & Lcl_u8ParitySel MUST BE PASSED AS THE PREVIOUS OPTIONS***/
u8 USART_u8InitUSART1 (f32 Lcl_f32BaudRate , u16 Lcl_u16DataWidth, u16 Lcl_u16ParitySel); /*Works well*/
/*----------------------------------------------------------------------------*/
/*
It is optional to set a callBack function called in IRQ handler when
transmission is complete.(USART_TR_COMPLETE IRQ must be then enabled)
*/
void USART1_voidSetTcCmpltCallBackFn (void(*clBk_OnTxCmplt)(void));
/*----------------------------------------------------------------------------*/
/*If error detected, the corresponding macro will be sent to the set callBack fn
IRQ is enabled*/
#define USART_ERROR_PARITY   1
#define USART_ERROR_OVERRUN  3
//#define USART_ERROR_DMA      6
void USART1_voidSetErrDetetCallBackFn (void(*clBk_OnErrDetect) (u8 USART1_ErrType));
/*----------------------------------------------------------------------------*/
/*
Enables IRQ for the passed choice.
(ONLY IF the corresponding callBack function is already set)
 */
#define USART_RX_REG_NOT_EMPTY 5
#define USART_TR_COMPLETE      6
#define USART_PARITY_ERROR     8

void USART1_voidEnIRQ  (u8 Local_u8Flag);
void USART1_voidDisIRQ (u8 Local_u8Flag);
/*----------------------------------------------------------------------------*/
/*
 TX functions wait the to complete and return the status.
 RX functions assigns the received data to the passed pointer if there is ready one.
    Otherwise return USART_EMPTY_RX_REG.
 */
u8  USART1_u8SyncTx    (u16  Local_u16Data);  /*Works well*/
u8  USART1_u8SyncTxArr (u16 *Local_u16ArrPtr , u16  Local_u16ArrWidth);  /*Works well*/
u8  USART1_u8SyncTxStr (u8  *Local_u8StrPtr  , u16  Local_u16StrWidth); /*Works well*/

u8 USART1_u8SyncRx    (u16 *Local_u16PtrData); /*Works well*/
//u16* SPI1_u16PtrSyncRxArr (u16  Local_u16ArrWidth);
/*----------------------------------------------------------------------------*/

/*
These functions doesn't wait to TX/RX value.
IRQ is generated (if already enabled) to announce any reception.
Received data/ArrPtr is passed to the related callback function ( If IRQ is already enabled).
*/
void  USART1_voidAsyncTx    (u16  Local_u16Data);/*Works well*/
void  USART1_voidAsyncTxArr (u16 *Local_u16ArrPtr , u16  Local_u16ArrWidth);/*Works well*/

/*Pass action function to be called with the received data/dataPtr*/
void  USART1_voidAsyncRx (void(*clBk_OnRxData) (u16 Data));/*Works well*/
void USART1_voidPtrAsyncRxArr (u16 Local_u16ArrWidth ,u16* Local_u16PtrRxArr,void(*clBk_OnRxArr) (u16 *Data));/*Works well*/
/*----------------------------------------------------------------------------*/
/*Returns the actual set baud rate (Depends on configured bus frequency)*/
f32 USART_f32GetBaudRate(void);
/******************************************************************************/
/**************************** Status definition *******************************/
/******************************************************************************/
#define USART_OK               1
#define USART_INVALID_DATA     2
#define USART_VALID_DATA       4
#define USART_NOISE_VALID_DATA 6
#define USART_INVALID_BR       8
#define USART_EMPTY_RX_REG    10
/******************************************************************************/
#endif  /*USART_INTERFACE_H*/
