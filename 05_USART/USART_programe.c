/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          :                                                       */
/*Description    : An educational USART driver File for STM32F103C MC    */
/* Date          : 11 03 2022                                            */
/* Version       : V01                                                   */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#include "STD_TYPES.h"
#include "MANIPULATOR.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

u8 USART_u8InitUSART1(f32 Lcl_f32BaudRate , u16 Lcl_u16DataWidth, u16 Lcl_u16ParitySel)
{
  f32 DIV_f32Val =0;
  u16 DIV_u16Mntsa = 0;
  u8  DIV_u8Fraction = 0;
  /*Make sure all USART1  is disabled*/
  MyUSART1->CR1 =0;
                    /******* BaudRate config section *******/
                    /*
                                     BUS_FREQ
                        USARTDIV = --------------
                                  16 * BaudRate
                                                          */
  /*USARTDIV evaluation*/
  DIV_f32Val = (f32)(USART1_APB2_FREQ/16)/Lcl_f32BaudRate;
  /*USARTDIV (whole part) evaluation*/
  DIV_u16Mntsa = (u16)DIV_f32Val;
  /*USARTDIV (Fraction part * 16) evaluation*/
  DIV_f32Val = (DIV_f32Val - (f32)DIV_u16Mntsa)*(f32)16;
  /*Rounding the fraction*/
  if (DIV_f32Val - (u32)DIV_f32Val >= 0.5)
  {
    DIV_u8Fraction = (u32)DIV_f32Val + 1;
  }
  else
  {
    DIV_u8Fraction = (u32)DIV_f32Val;
  }
  /*Check for overFlow for 4 bits fraction*/
  if (DIV_u8Fraction > 0xF)
  {
    DIV_u16Mntsa++;
    DIV_u8Fraction = 0;
  }
  /*Check for MAX_DIV_MANTISSA*/
  if (DIV_u16Mntsa > MAX_DIV_MANTISSA || (DIV_u16Mntsa+DIV_u8Fraction) == 0)
  {
    return USART_INVALID_BR;
  }
  /*Assign these values to the BRR register*/
  MyUSART1->BRR  = (DIV_u16Mntsa << 4) | DIV_u8Fraction;
                   /***************************************/
/*Hardware flow control config*/
#if USART_RTS == EN
  BIT_H(MyUSART1->CR3,8);
#endif /*USART_RTS*/
#if USART_CTS == EN
  BIT_H(MyUSART1->CR3,9);
#endif /*USART_CTS*/

  /*EN HALF duplex SINGLE WIRE if have been chosen*/
#if  USART1_COMMUNICATION_MODE == USART_SINGLE_WIRE_HALF_DUPLEX
  BIT_H(MyUSART1->CR3,3);
#endif /*USART1_COMMUNICATION_MODE*/

#if  USART1_MODE == USART_SYNCRONOUS
  /*These  bits should not be written while the transmitter is enabled*/
  /*EN clock*/
  BIT_H(MyUSART1->CR2,11);
  /*Config phase & polarity*/
  MAN_BIT(MyUSART1->CR2,10,USART1_CLK_POLARITY);
  MAN_BIT(MyUSART1->CR2,09,USART1_CLK_PHASE);
#elif USART1_MODE == USART_LIN
  BIT_H(MyUSART1->CR2,14);
                          /*LIN is to be continued..*/
#endif /*USART1_MODE*/
  /*Config stop bits*/
  //Clearing stop bits selection position
  MyUSART1->CR2 &= ~(0b11<<12);
  //Assign the configured values
  MyUSART1->CR2 |= USART1_STOPBITS_NUM;
  /*Enable UART1 first (As data sheet stated)*/
  BIT_H( MyUSART1->CR1,13);
     /**Variables option-definitions are designed to be handled like this**/
  /*Config DataWidth & Parity & EN/DIS (RX&TX) and save uart enabled*/
  MyUSART1->CR1 = Lcl_u16DataWidth|Lcl_u16ParitySel|(USART1_COMMUNICATION_MODE & 0xF)|0x2000;

  return USART_OK;
}
/*----------------------------------------------------------------------------*/
void USART1_voidSetTcCmpltCallBackFn (void(*clBk_OnTxCmplt)(void))
{
  clBk_TxCmplt = clBk_OnTxCmplt;
  TcCmpltCallBackIsSetF = 1;
}
void USART1_voidSetErrDetetCallBackFn (void(*clBk_OnErrDetect) (u8 USART1_ErrType))
{
  clBk_ErrDetect = clBk_OnErrDetect;
  ErrCallBackIsSetF = 1;
}
/*----------------------------------------------------------------------------*/
void USART1_voidEnIRQ(u8 Local_u8Flag)
{
  BIT_H(MyUSART1->CR1,Local_u8Flag);
}
void USART1_voidDisIRQ(u8 Local_u8Flag)
{
  BIT_L(MyUSART1->CR1,Local_u8Flag);
}
/*----------------------------------------------------------------------------*/
//If RX-ONLY is chosen, these functions are not needed//
#if USART1_COMMUNICATION_MODE != USART_RX_ONLY
u8  USART1_u8SyncTx     (u16  Local_u16Data)
{
	  MyUSART1->DR = Local_u16Data;

  /* Wait TC flag to indicate transmission completed
                     &
   to let it cleared with next DR write */
  while (!GET_BIT(MyUSART1->SR,6));
  /*In future i will develop a timeout function to prevent infinite loop*/
  return USART_OK;
}
u8   USART1_u8SyncTxArr      (u16 *Local_u16ArrPtr , u16  Local_u16ArrWidth)
{
  u16 i=0;
  for (;i<Local_u16ArrWidth;i++)
  {
    MyUSART1->DR = Local_u16ArrPtr[i];
    /* Wait TXE flag to indicate TX REG is empty*/
    while (!GET_BIT(MyUSART1->SR,7));
  }
  /* Wait TC flag to indicate transmission completed
                     &
    to let it cleared with next DR write */
  while (!GET_BIT(MyUSART1->SR,6));
  return USART_OK;
}
u8  USART1_u8SyncTxStr (u8  *Local_u8StrPtr  , u16  Local_u16StrWidth)
{
	u16 i=0;
	for (;i<Local_u16StrWidth;i++)
	{
	  MyUSART1->DR = Local_u8StrPtr[i];
	  /* Wait TXE flag to indicate TX REG is empty*/
	  while (!GET_BIT(MyUSART1->SR,7));
	}
	/* Wait TC flag to indicate transmission completed
	                     &
	  to let it cleared with next DR write */
	while (!GET_BIT(MyUSART1->SR,6));
    return USART_OK;
}

#endif /*RX-only non-related functions*/

//If TX-ONLY is chosen, these functions are not needed//
#if USART1_COMMUNICATION_MODE != USART_TX_ONLY
u8 USART1_u8SyncRx    (u16 *Local_u16PtrData)
{
  /*Check if RXNE is set (Receive register in not empty)*/
  if   (GET_BIT(MyUSART1->SR,5))
	  {
	  *Local_u16PtrData = MyUSART1->DR;
	  return USART_OK;
	  }
  else return USART_EMPTY_RX_REG;
}
#endif /*TX-only non-related function*/


/*----------------------------------------------------------------------------*/
//If RX-ONLY is chosen these functions are not needed//
#if USART1_COMMUNICATION_MODE != USART_RX_ONLY
void  USART1_voidAsyncTx (u16  Local_u16Data)
{
  /*Writing data to be transmitted*/
  MyUSART1->DR = Local_u16Data;
  /*If user wants to take action on transmit completion, he/she needs to enable it*/
}
void  USART1_voidAsyncTxArr    (u16 *Local_u16ArrPtr , u16  Local_u16ArrWidth)
{
  Glbl_u16TxArrPtr = Local_u16ArrPtr;
  Glbl_u16TxArrWidth = Local_u16ArrWidth;
  /*Tx the first element*/
  MyUSART1->DR = Local_u16ArrPtr[0];
  Glbl_u16TxArrIndex =1;
  /*Rise multi interrupt flag to send data in IRQ handler*/
  IRQ1_MltiTxShotF =1;
  /*Enable IRQ of empty TX register*/
  USART1_voidEnIRQ  (USART_TX_REG_EMPTY);

}
#endif /*RX-only non-related functions*/

//If TX-ONLY is chosen these functions are not needed//
#if USART1_COMMUNICATION_MODE != USART_TX_ONLY
void  USART1_voidAsyncRx (void(*clBk_OnRxData) (u16 Data))
{
  /*Check if already there is a ready data to be read*/
  if   (GET_BIT(MyUSART1->SR,5)) clBk_OnRxData(MyUSART1->DR);
  else
  {
    clBk_RxData = clBk_OnRxData;
    /*Announce the IRQ to get a single Frame on the next Rx not empty IRQ*/
    IRQ1_SnglRxShotF = 1;
    /*Enable IRQ for Rx IS NOT EMPTY*/
    USART1_voidEnIRQ  (USART_RX_REG_NOT_EMPTY);
  }
}
void USART1_voidPtrAsyncRxArr (u16 Local_u16ArrWidth ,u16* Local_u16PtrRxArr,void(*clBk_OnRxArr) (u16 *Data))
{
  /*Assign the passed array ptr to store data in*/
  Glbl_u16RxArrPtr = Local_u16PtrRxArr;
  /*The width of the needed array of data to be received */
  Glbl_u16RxArrWidth = Local_u16ArrWidth;
  /*Assign the required callBack on RX complete*/
  clBk_RxArr =clBk_OnRxArr;
  /*Check if already there is a ready frame to be read*/
  if   (GET_BIT(MyUSART1->SR,5))
  {
    Glbl_u16RxArrPtr[0] = MyUSART1->DR;
    Glbl_u16RxArrIndex = 1;
  }
  /*Wait it in interrupt*/
  else
  {
    Glbl_u16RxArrIndex = 0;
  }
  /*Announce the IRQ to get a multiShot of data (Array) on the following Rx not empty IRQ*/
  IRQ1_MltiRxShotF =1;
  /*Enable IRQ for Rx IS NOT EMPTY*/
  USART1_voidEnIRQ  (USART_RX_REG_NOT_EMPTY);
}
#endif /*TX-only non-related function*/
/*----------------------------------------------------------------------------*/
f32 USART_f32GetBaudRate(void)
{
  u16 temp = MyUSART1->BRR;
  return ((temp>>4) + (temp&0xF)/(f32)16);
}
/*----------------------------------------------------------------------------*/

void USART1_IRQHandler (void)

{
  /*Poling for flags and corresponding enable bit*/
  if (GET_BIT(MyUSART1->SR,5) && GET_BIT(MyUSART1->CR1,USART_RX_REG_NOT_EMPTY) )
  {
    /*Polling for receiving array or a single frame*/
    if (IRQ1_SnglRxShotF)
    {
      /*single shot is needed*/
      /*Clear single shot flag*/
      IRQ1_SnglRxShotF =0;
      /*Call the required func and pass data*/
      clBk_RxData( MyUSART1->DR);
      /*Disable RXNE IRQ*/
      USART1_voidDisIRQ  (USART_RX_REG_NOT_EMPTY);
    }
    else if (IRQ1_MltiRxShotF && Glbl_u16RxArrIndex < Glbl_u16RxArrWidth)
    {
      /*Store the received data in the global array*/
      Glbl_u16RxArrPtr[Glbl_u16RxArrIndex++] = MyUSART1->DR;
    }
    else
    {
      /*Array completed*/
      IRQ1_MltiRxShotF = 0;
      Glbl_u16RxArrWidth = 0;
      Glbl_u16RxArrIndex  = 0;
      /*Call the passed fnc and give it the array pointer tyo handle it*/
      clBk_RxArr (Glbl_u16RxArrPtr);
      /*Disable RXNE IRQ*/
      USART1_voidDisIRQ  (USART_RX_REG_NOT_EMPTY);
      //Glbl_u16RxArrPtr =NULL;
    }
  }
  if (GET_BIT(MyUSART1->SR,6) && GET_BIT(MyUSART1->CR1,USART_TR_COMPLETE))
  {
    if (TcCmpltCallBackIsSetF) clBk_TxCmplt();
  }
  if (GET_BIT(MyUSART1->SR,7) && GET_BIT(MyUSART1->CR1,USART_TX_REG_EMPTY))
  {
    /**/
    if(IRQ1_MltiTxShotF && Glbl_u16TxArrIndex < Glbl_u16TxArrWidth)
    {
      MyUSART1->DR = Glbl_u16TxArrPtr[Glbl_u16TxArrIndex++];
    }
    else
    {
      /*Array completed*/
      IRQ1_MltiTxShotF =0;
      //Glbl_u16TxArrPtr =NULL;
      Glbl_u16TxArrWidth =0;
      Glbl_u16TxArrIndex =0;
      /*Disable IRQ of empty TX register*/
      USART1_voidDisIRQ  (USART_TX_REG_EMPTY);
    }
  }
  if (GET_BIT(MyUSART1->SR,0) && GET_BIT(MyUSART1->CR1,USART_PARITY_ERROR))
  {
    if (ErrCallBackIsSetF) clBk_ErrDetect(USART_ERROR_PARITY);
  }
  /*This is OVERRUN interrupt*/
  if (GET_BIT(MyUSART1->SR,3) && GET_BIT(MyUSART1->CR1,USART_RX_REG_NOT_EMPTY) )
  {
    if (ErrCallBackIsSetF) clBk_ErrDetect(USART_ERROR_OVERRUN);
  }
  /*if (GET_BIT(MyUSART1->SR,4) && GET_BIT(MyUSART1->CR1,USART_IDLE_LINE))
  {

  }*/
}
