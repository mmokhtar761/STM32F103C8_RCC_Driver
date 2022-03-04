/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          :                                                       */
/*Description    : An educational SPI driver File for STM32F103C MC      */
/* Date          : 4 March 2022                                          */
/* Version       : V01                                                   */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#include "STD_TYPES.h"
#include "MANIPULATOR.h"
#include "SPI_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"

u8 SPI1_u8InitSPI1(u8 Copy_u8APB2FreqDivFactor ,u8 Copy_u8FrameSize , u8 Copy_u8DtaOrder)
{
/*Make sure  the peripheral is disabled*/
BIT_L(MySPI1->CR1,6);
#if   SPI1_MODE == MASTER_MODE
                        /*Master mode configurations*/
/*
1- Select the BR[2:0] bits to define the serial clock baud rate
*/
MAN_NIBBLE(MySPI1->CR1,3,Copy_u8APB2FreqDivFactor);
/*
2- Select the CPOL and CPHA bits to define one of the four relationships
between the data transfer and the serial clock.
*/
MAN_BIT(MySPI1->CR1,0,SPI1_CLK_PHASE);
MAN_BIT(MySPI1->CR1,1,SPI1_CLK_POLARITY);
/*
3- Set the DFF bit to define 8- or 16-bit data frame format
*/
if      (Copy_u8FrameSize ==  8) BIT_L(MySPI1->CR1,11);
else if (Copy_u8FrameSize == 16) BIT_H(MySPI1->CR1,11);
else return SPI_BAD_FRAME_SIZE;
/*
4- Configure the LSBFIRST bit in the SPI_CR1 register to define the frame format
*/
MAN_BIT(MySPI1->CR1,7,Copy_u8DtaOrder);
/*
4- Config the peripheral in master mode.
*/
BIT_H(MySPI1->CR1,2);

/* Continue here NSS config*/

#elif SPI1_MODE == SLAVE_MODE
                        /*Slave mode configurations*/
/*
1- Set the DFF bit to define 8- or 16-bit data frame format
*/
if      (Copy_u8FrameSize ==  8) BIT_L(MySPI1->CR1,11);
else if (Copy_u8FrameSize == 16) BIT_H(MySPI1->CR1,11);
else return SPI_BAD_FRAME_SIZE;
/*
2- Select the CPOL and CPHA bits to define one of the four relationships between the
  data transfer and the serial clock (see Figure 240 PAGE 705 in register description manual).
*/
MAN_BIT(MySPI1->CR1,0,SPI1_CLK_PHASE);
MAN_BIT(MySPI1->CR1,1,SPI1_CLK_POLARITY);
/*
3- The frame format (MSB-first or LSB-first depending on the value of the LSBFIRST bit in
the SPI_CR1 register)
*/
MAN_BIT(MySPI1->CR1,7,Copy_u8DtaOrder);
/*
4- Config the peripheral in slave mode.
*/
BIT_L(MySPI1->CR1,2);
/*
5- ConfIg NSS pin to act as a classical NSS input: the slave is selected when NSS
 is low and de-selected when NSS high.
*/
BIT_L(MySPI1->CR1,9); // Clear SSM  bit
BIT_L(MySPI1->CR2,2); // Clear SSOE bit

#endif /*SPI1_MODE*/

#if   SPI1_COMMUNICATION_MODE == SPI_FULL_DUPLEX || SPI1_COMMUNICATION_MODE == SPI_DATA_TRASMIT_ONLY
BIT_L(MySPI1->CR1,15); // Clear BIDMODE bit
BIT_L(MySPI1->CR1,10); // Clear RXONLY  bit
#elif SPI1_COMMUNICATION_MODE == SPI_DATA_RECEIVE_ONLY
BIT_L(MySPI1->CR1,15); // Clear BIDMODE bit
BIT_H(MySPI1->CR1,10); // Set RXONLY  bit
#elif SPI1_COMMUNICATION_MODE == SPI_BIDIRECTIONAL_DATA_WIRE
BIT_H(MySPI1->CR1,15); // Sets BIDMODE bit
/* Direction choosing is set by BIDIOE bit in CR1 REG */
#endif /*SPI1_COMMUNICATION_MODE*/

/*Enable the peripheral*/
BIT_H(MySPI1->CR1,6);
return SPI_OK;
}
/*----------------------------------------------------------------------------*/

u16 SPI1_u16SyncXchg  (u16 Local_u16Data)
{
	MySPI1->DR = Local_u16Data;
	while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
	return MySPI1->DR;
}
/*----------------------------------------------------------------------------*/
void SPI1_u16AsyncXchg  (u16 Local_u16Data)
{
	MySPI1->DR = Local_u16Data;
}
/*----------------------------------------------------------------------------*/
void SPI1_voidSyncSendArr  (u8* Local_u8ArrData , u16 Local_u16ArrSize)
{
	u16 i =0;
	for (i=0;i<Local_u16ArrSize;i++)
	{
		/* Write the next data item to be transmitted into the SPI_DR register */
		MySPI1->DR = Local_u8ArrData[i];
		/* Wait until TXE=1 (TX buffer to be empty) */
		while (!GET_BIT(MySPI1->SR,1)); //Wait TXE to be set
	}
	while (GET_BIT(MySPI1->SR,7)); //Wait for busy flag to be cleared
}
/*----------------------------------------------------------------------------*/
void SPI1_u8DisTxIRQ (void)
{
	BIT_L(MySPI1->CR2,7);
}
void SPI1_u8DisRxIRQ (void)
{
	BIT_L(MySPI1->CR2,6);
}
void SPI1_u8EnTxIRQ  (void)
{
	BIT_H(MySPI1->CR2,7);
}
void SPI1_u8EnRxIRQ  (void)
{
	BIT_H(MySPI1->CR2,6);
}
/*----------------------------------------------------------------------------*/
void SPI1_voidSetCallBackFunc(void(*RxPtr)(u16 Data))
{
	RxFnPtr = RxPtr;
	G_u8CallBackSetFlag =1;
}
/*----------------------------------------------------------------------------*/
void SPI1_IRQHandler()
{
	if(G_u8CallBackSetFlag) RxFnPtr (MySPI1->DR);
}
/*----------------------------------------------------------------------------*/
