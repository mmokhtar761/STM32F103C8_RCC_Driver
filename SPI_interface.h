/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : SPI_INTERFACE_H                                       */
/*Description    : An educational SPI driver File for STM32F103C MC      */
/* Date          : 4 March 2022                                          */
/* Version       : V02 -> A good implementation & no real tests are done */
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
The function enables SPI in all configuration modes except:
 SPI_DATA_RECEIVE_ONLY & SPI_BIDIRECTIONAL_DATA_WIRE
*/
/*----------------------------------------------------------------------------*/
u8 SPI1_u8InitSPI1(u8 Copy_u8APB2FreqDivFactor ,u8 Copy_u8FrameSize , u8 Copy_u8DtaOrder);
/******************************************************************************/
              /* This function exchange 1 frame on SPI1*/
/*
-->> Master mode:
Waits to return the received value
If only receiving is needed, pass any value to it.
If SPI_DATA_TRASMIT_ONLY has been chosen, returns SPI_OK.
If SPI_BIDIRECTIONAL_DATA_WIRE has been chosen, a frame is send then another received
-->> Slave mode:
Master who starts the communication to exchange the passed value.
Writes data to be ready for any communication
IRQ is generated (if already enabled) to announce any reception.
Returns SPI_OK.
*/
u16 SPI1_u16SyncXchg  (u16 Local_u16Data);
/*----------------------------------------------------------------------------*/
/*
-->> Master mode:
Doesn't waits to return the received value
If only receiving is needed, pass any value to it.
IRQ is generated (if already enabled) to announce any reception.
Received data is passed to the callback function ( If IRQ is already enabled).
-->> Slave mode:
Almost does the same as SPI1_u16SyncXchg () function.
*/
void SPI1_u16AsyncXchg  (u16 Local_u16Data);
/******************************************************************************/
          /* This function sends/exchange an array of 8bit data on SPI1*/

/*
-->> Master mode:
Waits to send each element of the passed array.
If configured as SPI_DATA_RECEIVE_ONLY, this function does no thing
-->> Slave mode:
NOT ENABLED IN THIS MODE
*/
void SPI1_voidSyncSendArr  (u8* Local_u8ArrData, u16 Local_u16ArrSize);
                                /*------------------------------------*/
/*
-->> Master mode:
Waits to send each element of the passed array and stores the received
data in same array.
If SPI_DATA_RECEIVE_ONLY mode has been chosen, only receiving happens.
If SPI_BIDIRECTIONAL_DATA_WIRE mode has been chosen, This function only receives
-->> Slave mode:
NOT ENABLED IN THIS MODE. It is recommended to comment this line
*/
void SPI1_voidSyncXchgArr  (u8* Local_u8ArrData, u16 Local_u16ArrSize);
/*----------------------------------------------------------------------------*/
/*
*Enable IRQ to fire interrupt in Master/Slave mode on every reception/transmission
completion.(This is essential in slave mode to read the received data asynchronously)
*CallBack function must be set first.
*Its recommended not to let RX & TX to be enable in the same time.
*In SPI_DATA_TRASMIT_ONLY mode '0' char value is passed to IRQ call back function.
*/

void SPI1_voidSetCallBackFunc(void(*FnPtr)(u16 Data));

void SPI1_u8DisTxIRQ (void);
void SPI1_u8DisRxIRQ (void);

void SPI1_u8EnTxIRQ  (void);
void SPI1_u8EnRxIRQ  (void);
/*----------------------------------------------------------------------------*/
u8 SPI1_u8GetBusyFlagSate(void);
/*----------------------------------------------------------------------------*/

/******** Error section ********/
#define SPI_OK             0
#define SPI_BAD_FRAME_SIZE 1
#endif  /*SPI_INTERFACE_H*/
