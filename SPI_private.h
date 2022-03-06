/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : SPI_PRIVATE_H                                         */
/*Description    : An educational SPI driver File for STM32F103C MC      */
/* Date          : 4 March 2022                                          */
/* Version       : V2.1 -> NSS config in Master mode to be High by SW    */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

#define MASTER_MODE 2
#define SLAVE_MODE  4
/*----------------------------------------------------------------------------*/
/*SPI1_COMMUNICATION_MODE Options definition*/
#define SPI_FULL_DUPLEX             2
#define SPI_DATA_TRASMIT_ONLY       4
#define SPI_DATA_RECEIVE_ONLY       6
#define SPI_BIDIRECTIONAL_DATA_WIRE 8
/*----------------------------------------------------------------------------*/
/*SPI1 Clock Options definition*/
#define SPI_IDLE_LOW          0
#define SPI_IDLE_HIGH         1
#define FIRST_EDGE_CAPTURING  0
#define SECOND_EDGE_CAPTURING 1
/*----------------------------------------------------------------------------*/
#define SPI_HW_MANAGEMENT 0
#define SPI_SW_MANAGEMENT 1
/*----------------------------------------------------------------------------*/
void(*GlFnPtr)(u16 Data);
u8 G_u8CallBackSetFlag = 0;
typedef struct
{
  volu32 CR1;
  volu32 CR2;
  volu32 SR;
  volu32 DR;
  volu32 CRCPR;
  volu32 RXCRCR;
  volu32 TXCRCR;
  volu32 I2SCFGR;
  volu32 I2SPR;
} SPI_RegType;
#define SPI1_BASE_ADDRESS 0x40013000
#define SPI2_BASE_ADDRESS 0x40003800
#define MySPI1    ((SPI_RegType*)SPI1_BASE_ADDRESS) //on ABP2 Bus
#define MySPI2    ((SPI_RegType*)SPI2_BASE_ADDRESS) //on ABP1 Bus
#endif /* SPI_PRIVATE_H*/
