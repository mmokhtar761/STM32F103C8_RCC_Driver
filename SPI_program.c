/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          :                                                       */
/*Description    : An educational SPI driver File for STM32F103C MC      */
/* Date          : 4 March 2022                                          */
/* Version       : V02 -> A good implementation & no real tests are done */
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

/*Enable the peripheral*/
BIT_H(MySPI1->CR1,6);
#endif /*SPI1_MODE*/

#if   SPI1_COMMUNICATION_MODE == SPI_FULL_DUPLEX || SPI1_COMMUNICATION_MODE == SPI_DATA_TRASMIT_ONLY
BIT_L(MySPI1->CR1,15); // Clear BIDMODE bit
BIT_L(MySPI1->CR1,10); // Clear RXONLY  bit
/*Enable the peripheral*/
BIT_H(MySPI1->CR1,6);
#elif SPI1_COMMUNICATION_MODE == SPI_DATA_RECEIVE_ONLY
BIT_L(MySPI1->CR1,15); // Clear BIDMODE bit
BIT_H(MySPI1->CR1,10); // Set RXONLY  bit
#elif SPI1_COMMUNICATION_MODE == SPI_BIDIRECTIONAL_DATA_WIRE
BIT_H(MySPI1->CR1,15); // Sets BIDMODE bit
/* Direction choosing is set by BIDIOE bit in CR1 REG */
#endif /*SPI1_COMMUNICATION_MODE*/

return SPI_OK;
}
/*----------------------------------------------------------------------------*/

u16 SPI1_u16SyncXchg  (u16 Local_u16Data)
{
#if   SPI1_MODE == MASTER_MODE

#if   SPI1_COMMUNICATION_MODE == SPI_FULL_DUPLEX
	/*Start communication by writing the data*/
	MySPI1->DR = Local_u16Data;
	while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
	return MySPI1->DR;
#elif  SPI1_COMMUNICATION_MODE == SPI_DATA_TRASMIT_ONLY
	/*Start communication by writing the data*/
	MySPI1->DR = Local_u16Data;
	while (!GET_BIT(MySPI1->SR,1)); //Wait TXE to be set
	return SPI_OK;
#elif  SPI1_COMMUNICATION_MODE == SPI_DATA_RECEIVE_ONLY
	/*Enable the peripheral to start receiving*/
	BIT_H(MySPI1->CR1,6);
	while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
	/*Read the received data*/
	Local_u16Data = MySPI1->DR;
	/*** SPI disabling sequence as in the data sheet ***/
	/*1-Wait for the second to last occurrence of RXNE=1 */
	while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
	while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
	/*2-Wait for one SPI clock cycle (using a software loop) before disabling the SPI*/
	Local_u16Data-=1;
	Local_u16Data+=1;
	/*3-Disable the peripheral to stop receiving*/
	BIT_L(MySPI1->CR1,6);
	return Local_u16Data;
#elif SPI1_COMMUNICATION_MODE == SPI_BIDIRECTIONAL_DATA_WIRE
	/*Enable the peripheral to start*/
	BIT_H(MySPI1->CR1,6);

	/*Set BIDIO to config line to send*/
	BIT_H(MySPI1->CR1,14);
	/*Start communication by writing the data*/
	MySPI1->DR = Local_u16Data;
	while (!GET_BIT(MySPI1->SR,1)); //Wait TXE to be set

	/*Clear BIDIO to config line to receive*/
	BIT_L(MySPI1->CR1,14);
	while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
	/*Read data*/
	Local_u16Data = MySPI1->DR;
	/*** SPI disabling sequence as in the data sheet ***/
	/*1-Wait for the second to last occurrence of RXNE=1 */
	while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
	while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
	/*2-Wait for one SPI clock cycle (using a software loop) before disabling the SPI*/
	Local_u16Data-=1;
	Local_u16Data+=1;
	/*3-Disable the peripheral to stop receiving*/
	BIT_L(MySPI1->CR1,6);
	return Local_u16Data;
#endif /*SPI1_COMMUNICATION_MODE*/


#else /*Slave mode has been selected*/
	/*Write data to be ready for any communication*/
	MySPI1->DR = Local_u16Data;
	return SPI_OK;
#endif /*SPI1_MODE*/
}
/*----------------------------------------------------------------------------*/
void SPI1_u16AsyncXchg  (u16 Local_u16Data)
{
#if   SPI1_MODE == MASTER_MODE

#if   SPI1_COMMUNICATION_MODE == SPI_FULL_DUPLEX || SPI1_COMMUNICATION_MODE == SPI_DATA_TRASMIT_ONLY
	/*Start communication by writing the data*/
	MySPI1->DR = Local_u16Data;
	/*Received data handled in IRQ handler*/
#elif  SPI1_COMMUNICATION_MODE == SPI_DATA_RECEIVE_ONLY
	/*Enable the peripheral to start receiving*/
	BIT_H(MySPI1->CR1,6);
	/*SPI must be disabled in the IRQ */

#elif SPI1_COMMUNICATION_MODE == SPI_BIDIRECTIONAL_DATA_WIRE
	/*Enable the peripheral to start*/
	BIT_H(MySPI1->CR1,6);
	/*Set BIDIO to config line to send*/
	BIT_H(MySPI1->CR1,14);
	/*Start communication by writing the data*/
	MySPI1->DR = Local_u16Data;
	/*Received data handled in IRQ handler & peripheral must be disabled*/
#endif /*SPI1_COMMUNICATION_MODE*/


#else  /*Slave mode is selected*/
	/*Write data to be ready for any communication*/
	MySPI1->DR = Local_u16Data;
#endif /*SPI1_MODE*/
}
/*----------------------------------------------------------------------------*/
#if SPI1_MODE == MASTER_MODE

void SPI1_voidSyncSendArr  (u8* Local_u8ArrData , u16 Local_u16ArrSize)
{
#if   SPI1_COMMUNICATION_MODE != SPI_DATA_RECEIVE_ONLY
	u16 i =0;
#if SPI1_COMMUNICATION_MODE == SPI_BIDIRECTIONAL_DATA_WIRE
	/*Enable the peripheral to start*/
	BIT_H(MySPI1->CR1,6);
	/*Set BIDIOE to configure line to send*/
	BIT_H(MySPI1->CR1,14);
#endif /*SPI1_COMMUNICATION_MODE*/
	for (i=0;i<Local_u16ArrSize;i++)
	{
		/* Write the next data item to be transmitted into the SPI_DR register */
		MySPI1->DR = Local_u8ArrData[i];
		/* Wait until TXE=1 (TX buffer to be empty) */
		while (!GET_BIT(MySPI1->SR,1)); //Wait TXE to be set
	}
	while (GET_BIT(MySPI1->SR,7)); //Wait for busy flag to be cleared
#endif /*SPI1_COMMUNICATION_MODE*/
}
                                /*------------------------------------*/
void SPI1_voidSyncXchgArr (u8* Local_u8ArrData, u16 Local_u16ArrSize)
{
#if   SPI1_COMMUNICATION_MODE == SPI_FULL_DUPLEX
	/*Start communication by writing the first data item*/
	MySPI1->DR = Local_u8ArrData[0];
	for (i=1;i<Local_u16ArrSize;i++)
	{
		/* Wait until TXE=1 (TX buffer to be empty) */
		while (!GET_BIT(MySPI1->SR,1)); //Wait TXE to be set
		/* Write the next data item to be transmitted into the SPI_DR register */
		MySPI1->DR = Local_u8ArrData[i];
		while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
		/*Assign the first received item to the array passed*/
		Local_u8ArrData[i-1] = MySPI1->DR;
	}
#elif  SPI1_COMMUNICATION_MODE == SPI_DATA_TRASMIT_ONLY
	SPI1_voidSyncSendArr  (Local_u8ArrData ,Local_u16ArrSize);
#elif  SPI1_COMMUNICATION_MODE == SPI_DATA_RECEIVE_ONLY
	/*Enable the peripheral to start receiving*/
	BIT_H(MySPI1->CR1,6);

	for (i=1;i<Local_u16ArrSize;i++)
	{
		while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
		/*Read the received data*/
		Local_u8ArrData[i] = MySPI1->DR;
	}
	/*** SPI disabling sequence as in the data sheet ***/
	/*1-Wait for the second to last occurrence of RXNE=1 */
	while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
	while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
	/*2-Wait for one SPI clock cycle (using a software loop) before disabling the SPI*/
	Local_u16Data-=1;
	Local_u16Data+=1;
	/*3-Disable the peripheral to stop receiving*/
	BIT_L(MySPI1->CR1,6);
#elif SPI1_COMMUNICATION_MODE == SPI_BIDIRECTIONAL_DATA_WIRE
	/*Enable the peripheral to start receiving*/
	BIT_H(MySPI1->CR1,6);
	/*Clear BIDIO to config line to receive*/
	BIT_L(MySPI1->CR1,14);
	for (i=1;i<Local_u16ArrSize;i++)
	{
		while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
		/*Read the received data*/
		Local_u8ArrData[i] = MySPI1->DR;
	}
	/*** SPI disabling sequence as in the data sheet ***/
		/*1-Wait for the second to last occurrence of RXNE=1 */
		while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
		while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
		/*2-Wait for one SPI clock cycle (using a software loop) before disabling the SPI*/
		Local_u16Data-=1;
		Local_u16Data+=1;
		/*3-Disable the peripheral to stop receiving*/
		BIT_L(MySPI1->CR1,6);
#endif /*SPI1_COMMUNICATION_MODE*/

}
#endif /*SPI1_MODE Master only functions*/
/*----------------------------------------------------------------------------*/
void SPI1_voidSetCallBackFunc(void(*FnPtr)(u16 Data))
{
	GlFnPtr = FnPtr;
	/*Rising SW flag to secure random addresses accessing*/
	G_u8CallBackSetFlag =1;
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
u8 SPI1_u8GetBusyFlagSate(void)
{
	return GET_BIT(MySPI1->SR,7);
}

/*----------------------------------------------------------------------------*/
void SPI1_IRQHandler()
{
 /*This IRQ is fired due to completion of reception/transmission (if enabled)*/
	       /*Master who starts the communication to exchange the DATA*/
 /*This place means a piece of data has been sent (& RX or TX IRQ is enabled)*/
	/*Check to secure random addresses accessing and pass data to the called fn*/



#if   SPI1_COMMUNICATION_MODE != SPI_DATA_TRASMIT_ONLY
	/*Check to secure random addresses accessing and pass data to the called fn*/
	if(G_u8CallBackSetFlag) GlFnPtr (MySPI1->DR);
#else /*SPI_DATA_TRASMIT_ONLY mode*/
	/* Transmission complete. Send '0' as coded value to the preset callback function*/
	if(G_u8CallBackSetFlag) GlFnPtr ('0');
#endif /*SPI1_COMMUNICATION_MODE*/


 	/* Disable SPI if following modes had been chosen to stop reception */
#if  SPI1_COMMUNICATION_MODE == SPI_BIDIRECTIONAL_DATA_WIRE
	if (GET_BIT(MySPI1->CR1,14)==0) //Check if IRQ is fired by reception
	{
		/*** SPI disabling sequence as in the data sheet ***/
		/*1-Wait for the second to last occurrence of RXNE=1 */
		while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
		while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
		/*2-Wait for one SPI clock cycle (using a software loop) before disabling the SPI*/
		Local_u16Data-=1;
		Local_u16Data+=1;
		/*3-Disable the peripheral to stop receiving*/
		BIT_L(MySPI1->CR1,6);
	}
	else                          //IRQ is fired by transmission
	{
		while (!GET_BIT(MySPI1->SR,1)); //Wait TXE to be set
		while (GET_BIT(MySPI1->SR,7)); //Wait for busy flag to be cleared
		/*Disable the peripheral to stop receiving*/
		BIT_L(MySPI1->CR1,6);
	}

#elif SPI1_COMMUNICATION_MODE == SPI_DATA_RECEIVE_ONLY
	/*** SPI disabling sequence as in the data sheet ***/
		/*1-Wait for the second to last occurrence of RXNE=1 */
		while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
		while (!GET_BIT(MySPI1->SR,0)); //Wait RXNE to be set
		/*2-Wait for one SPI clock cycle (using a software loop) before disabling the SPI*/
		Local_u16Data-=1;
		Local_u16Data+=1;
		/*3-Disable the peripheral to stop receiving*/
		BIT_L(MySPI1->CR1,6);
#endif /*SPI1_COMMUNICATION_MODE*/
}
/*----------------------------------------------------------------------------*/
