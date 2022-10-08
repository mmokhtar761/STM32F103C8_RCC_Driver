/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : USART_CONFIG_H                                        */
/*Description    : An educational USART driver File for STM32F103C MC    */
/* Date          : 11 03 2022                                            */
/* Version       : V01                                                   */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef USART_CONFIG_H
#define USART_CONFIG_H

/*
Options:
  USART_SYNCRONOUS
  USART_ASYNCRONOUS
  USART_LIN
*/
#define USART1_MODE  USART_ASYNCRONOUS

#if USART1_MODE == USART_SYNCRONOUS
/*
For correct data transfer, the CLK_POLARITY and CLK_PHASE  must be configured
in the same way in the other device.
*/
/*
Options:
   USART_IDLE_HIGH
   USART_IDLE_LOW
*/
#define USART1_CLK_POLARITY USART_IDLE_LOW
/*
Options:
   FIRST_CLK_CAPTURING
   SECOND_CLK_CAPTURING
*/
#define USART1_CLK_PHASE   SECOND_CLK_CAPTURING
#endif /*USART1_MODE*/
/*----------------------------------------------------------------------------*/
/*
Options:
  --> USART_TX_ONLY
  --> USART_RX_ONLY
  --> USART_FULL_DUPLEX
  --> USART_SINGLE_WIRE_HALF_DUPLEX
    *RX pin is no-longer used
    *TX is always released when no data is transmitted. Thus, it acts as
      a standard IO in idle or in reception. It means that the IO must be configured
      so that TX is configured as floating input (or output high open-drain)
      when not driven by the USART.
*/
#define USART1_COMMUNICATION_MODE USART_FULL_DUPLEX
/*----------------------------------------------------------------------------*/
/*
Options:
  USART_ONE_STOPBIT
  USART_TWO_STOPBIT

  (smartcard configuration only)
  USART_HALF_STOPBIT
  USART_ONEHALF_STOPBIT
*/
#define USART1_STOPBITS_NUM  USART_ONE_STOPBIT
         //BaudRate & Parity & frame size are execution time configs //
/*----------------------------------------------------------------------------*/
/* User must assign these values to be used in calculations*/
#define USART1_APB1_FREQ  8000000
#define USART1_APB2_FREQ  8000000
/*----------------------------------------------------------------------------*/
               /* Hardware flow control config (NOT STANDARD) */
                   /* RTS_1 --> CTS_2 && CTS_1 --> RTS_2 */
                        /* Options: DIS || EN */
/*
--> If the RTS is enabled, then RTS is asserted (tied low) as long as the USART
receiver is ready to receive new data. When the receive register is full, RTS is
deserted, indicating that the transmission is expected to stop at the end of
the current frame.
*/
#define USART_RTS  DIS
/*
--> If the CTS is enabled, then the transmitter checks the CTS input before transmitting
the next frame. If CTS is asserted (tied low), then the next data is transmitted,
 else the transmission does not occur. When CTS is deserted during a transmission,
 the current transmission is completed before the transmitter stops.
*/
#define USART_CTS  DIS
#endif  /*USART_CONFIG_H*/
