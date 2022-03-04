/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : SPI_INTERFACE_H                                       */
/*Description    : An educational SPI driver File for STM32F103C MC      */
/* Date          : 4 March 2022                                          */
/* Version       : V01                                                   */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

/*********************** SPI1 on APB2 Bus ***********************/
/******************* SPI2 & SPI3 on APB1 Bus ***********************/
/*
NOTE: APB2FreqDivFactor has no effect if the SPI has been configured in Slave Mode
*/
/*APB2FreqDivFactor Options*/
#define SPI_APB2_DIV_BY_2   0
#define SPI_APB2_DIV_BY_4   1
#define SPI_APB2_DIV_BY_8   2
#define SPI_APB2_DIV_BY_16  3
#define SPI_APB2_DIV_BY_32  4
#define SPI_APB2_DIV_BY_64  5
#define SPI_APB2_DIV_BY_128 6
#define SPI_APB2_DIV_BY_256 7
/*----------------------------------------------------------------------------*/
/*FrameSize can be (8 or 16) bit */
/*----------------------------------------------------------------------------*/
/*DtaOrder Options:*/
#define  SPI_MSB_FIRST  0
#define  SPI_LSB_FIRST  1
/*
DtaOrder must be the same as the Master/Slave device
*/
/*----------------------------------------------------------------------------*/
u8 SPI1_u8InitSPI1(u8 Copy_u8APB2FreqDivFactor ,u8 Copy_u8FrameSize , u8 Copy_u8DtaOrder);
/******************************************************************************/
/******************************************************************************/
/*
   Only in master mode:
This function exchange 1 frame on SPI1 and waits to return the received value
If only receiving is needed, pass any value to it.
*/
u16 SPI1_u16SyncXchg  (u16 Local_u16Data);
/*----------------------------------------------------------------------------*/
/*
   Only in master mode:
This function exchange 1 frame on SPI1 and receives on interrupt to pass it to
callback function ( If IRQ is already enabled)
*/
void SPI1_u16AsyncXchg  (u16 Local_u16Data);
/******************************************************************************/
/*
   Only in master mode:
This function exchange An array of u8 data on SPI1 and waits to accomplish this
*/
void SPI1_voidSyncSendArr  (u8* Local_u8ArrData, u16 Local_u16ArrSize);
/*----------------------------------------------------------------------------*/
/*
Enable IRQ to fire interrupt in Master/Slave mode on every reception/transmission
complete.(This is essential in slave mode to read the received data asynchronously)
CallBach func must be set first
*/
void SPI1_u8DisTxIRQ (void);
void SPI1_u8DisRxIRQ (void);

void SPI1_u8EnTxIRQ  (void);
void SPI1_u8EnRxIRQ  (void);
/*----------------------------------------------------------------------------*/
void SPI1_voidSetCallBackFunc(void(*RxPtr)(u16 Data));

/******** Error section ********/
#define SPI_OK             0
#define SPI_BAD_FRAME_SIZE 1
#endif  /*SPI_INTERFACE_H*/
