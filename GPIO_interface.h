/******************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                                 */
/* File          : GPIO_interface.h                                           */
/* Date          : 25 DEC 2021                                                */
/* Version       : V01                                                        */
/* GitHub        : https://github.com/mmokhtar761                             */
/******************************************************************************/
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H


/*
NOTE: During and just after reset, the alternate functions are not active
 	  	and the I/O ports are configured in Input Floating mode
*/

//Pins configuration modes
#define GPO_PUSH_PULL_10_MHZ  0b0001
#define GPO_PUSH_PULL_02_MHZ  0b0010
#define GPO_PUSH_PULL_50_MHZ  0b0011

#define GPO_OPEN_DRIAN_10_MHZ 0b0101
#define GPO_OPEN_DRIAN_02_MHZ 0b0110
#define GPO_OPEN_DRIAN_50_MHZ 0b0111


#define AFO_PUSH_PULL_10_MHZ  0b1001
#define AFO_PUSH_PULL_02_MHZ  0b1010
#define AFO_PUSH_PULL_50_MHZ  0b1011


#define AFO_OPEN_DRIAN_10_MHZ 0b1101
#define AFO_OPEN_DRIAN_02_MHZ 0b1110
#define AFO_OPEN_DRIAN_50_MHZ 0b1111

#define I_ANALOG              0b0000
#define I_FLOATING            0b0100
#define I_PULL_DOWN           0b10000
#define I_PULL_UP             0b10001
/*----------------------------------------------------------------------------*/
//Options for port
#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2
#define GPIO_PORTD 3
#define GPIO_PORTE 4
#define GPIO_PORTF 5
#define GPIO_PORTG 6
/*----------------------------------------------------------------------------*/
//Options for Copy_u8HalfSide
#define GPIO_LOW_HALF  0
#define GPIO_HIGH_HALF 1
/*----------------------------------------------------------------------------*/
//Options for Copy_u8PinValue
#define HIGH 1
#define LOW  0
/******************************************************************************/
u8 GPIO_u8ConfigPin      (u8 Copy_u8Port , u8 Copy_u8PinNumber , u8 Copy_u8Mode);
u8 GPIO_u8ConfigHalfPort (u8 Copy_u8Port , u8 Copy_u8HalfSide  , u8 Copy_u8Mode);
u8 GPIO_u8ConfigPort     (u8 Copy_u8Port , u8 Copy_u8Mode);
/*----------------------------------------------------------------------------*/
u8 GPIO_u8SetPinValue      (u8 Copy_u8Port , u8 Copy_u8PinNumber , u8 Copy_u8PinValue);
u8 GPIO_u8SetHalfPortValue (u8 Copy_u8Port , u8 Copy_u8HalfSide  , u16 Copy_u16HalfPortValue);
u8 GPIO_u8SetPortValue     (u8 Copy_u8Port , u32 Copy_u32PortValue);
/*----------------------------------------------------------------------------*/
u8  GPIO_u8GetPinValue      (u8 Copy_u8Port , u8 Copy_u8PinNumber);
u16 GPIO_u8GetHalfPortValue (u8 Copy_u8Port , u8 Copy_u8HalfSide);
u32 GPIO_u8GetPortValue     (u8 Copy_u8Port);
/******************************************************************************/
#define GPIO_OK               0
#define GPIO_ERROR_WRONG_PORT 2
#define GPIO_ERROR_WRONG_PIN  4
/******************************************************************************/
#endif  /*GPIO_INTERFACE_H*/
