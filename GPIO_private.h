/******************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                                 */
/* File          : GPIO_private.h                                             */
/* Date          : 25 DEC 2021                                                */
/* Version       : V1.1                                                       */
/* GitHub        : https://github.com/mmokhtar761                             */
/******************************************************************************/
#ifndef PRIVATE_CONFIG_H
#define PRIVATE_CONFIG_H


typedef struct {
	volu32 CRL;
	volu32 CRH;
	volu32 IDR;
	volu32 ODR;
	volu32 BSRR;
	volu32 BRR;
	volu32 LCKR;
} GPIO_PORT_Type;

#define GPIO_BASE_ADDRESS (0x40010800)
#define GPIO_PORT_OFFSET  (0x00000400)

#define MY_GPIO  ((GPIO_PORT_Type*)GPIO_BASE_ADDRESS)

/*
#define GPIO_PORTA_BASE_ADDRESS 0x40010800
#define GPIO_PORTB_BASE_ADDRESS 0x40010C00
#define GPIO_PORTC_BASE_ADDRESS 0x40011000
#define GPIO_PORTD_BASE_ADDRESS 0x40011400
#define GPIO_PORTE_BASE_ADDRESS 0x40011800
#define GPIO_PORTF_BASE_ADDRESS 0x40011C00
#define GPIO_PORTG_BASE_ADDRESS 0x40012000

#define GPIO_PORTA  ((GPIO_PORT_Type*)GPIO_PORTA_BASE_ADDRESS)
#define GPIO_PORTB  ((GPIO_PORT_Type*)GPIO_PORTB_BASE_ADDRESS)
#define GPIO_PORTC  ((GPIO_PORT_Type*)GPIO_PORTC_BASE_ADDRESS)
#define GPIO_PORTD  ((GPIO_PORT_Type*)GPIO_PORTD_BASE_ADDRESS)
#define GPIO_PORTE  ((GPIO_PORT_Type*)GPIO_PORTE_BASE_ADDRESS)
#define GPIO_PORTF  ((GPIO_PORT_Type*)GPIO_PORTF_BASE_ADDRESS)
#define GPIO_PORTG  ((GPIO_PORT_Type*)GPIO_PORTG_BASE_ADDRESS)
*/
typedef struct {
	volu32 EVCR;
	volu32 MAPR;
	volu32 EXTICRx[4];
	volu32 MAPR2;
} AFIO_Type;

#define AFIO_BASE_ADDRESS 0x40010000
#define MY_AFIO  ((AFIO_Type*)AFIO_BASE_ADDRESS)

/*As Ports are allocated in momory sequentially */
#define MY_PASSED_GPIO_PORT(Port_ID) (MY_GPIO + Port_ID);
/*As Ports are allocated in momory sequentially
GPIO_PORT_Type *Local_PtrToGPIOPORT = MY_GPIO + Copy_u8Port;*/
#endif  /*PRIVATE_CONFIG_H*/
