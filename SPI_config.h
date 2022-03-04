/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : SPI_CONFIG_H                                          */
/*Description    : An educational SPI driver File for STM32F103C MC      */
/* Date          : 4 March 2022                                          */
/* Version       : V01                                                   */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

/*
Options:
   MASTER_MODE
   SLAVE_MODE
*/
#define SPI1_MODE MASTER_MODE
/*
Options:
  * SPI_FULL_DUPLEX       -> The usual mode used with SPI

  * SPI_DATA_TRASMIT_ONLY -> The data are transmitted on the transmit pin
    and the receive pin can be used as a general-purpose IO.

  * SPI_DATA_RECEIVE_ONLY -> This option frees the transmit IO pin, so it
    can be used for other purposes. In this mode, if master is chosen,
    the communication starts immediately and stops when the SPE bit is cleared
    and the current reception stops. There is no need to read the BSY flag
    in this mode. It is always set when an SPI communication is ongoing.

  * SPI_BIDIRECTIONAL_DATA_WIRE -> MOSI in master or MISO in slave mode is
    used for data communication.
    The transfer direction (Input/Output) is selected by software.
*/
#define SPI1_COMMUNICATION_MODE SPI_FULL_DUPLEX
/*----------------------------------------------------------------------------*/
/*
For correct data transfer, the CLK_POLARITY and CLK_PHASE  must be configured
in the same way in the slave device and the master device.
*/
/*
Options:
   SPI_IDLE_HIGH
   SPI_IDLE_LOW
*/
#define SPI1_CLK_POLARITY SPI_IDLE_LOW
/*
Options:
   FIRST_EDGE_CAPTURING
   SECOND_EDGE_CAPTURING
*/
#define SPI1_CLK_PHASE SECOND_EDGE_CAPTURING
/*----------------------------------------------------------------------------*/
#if SPI1_MODE == MASTER_MODE
/*
Config the NSS pin to be controlled by software (SSI bit value) or by hardware
If configured as SW controlled.
Options:
   SPI_HW_MANAGEMENT
   SPI_SW_MANAGEMENT
NOTE: In case of multiSlave, It is NOT recommended at all to use SW management.
*/
#define SPI1_NSS_PIN_MANAGEMENT SPI_SW_MANAGEMENT
#endif  /*SPI1_MODE*/

#endif  /*SPI_CONFIG_H*/
