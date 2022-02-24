/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : EXTI_INTERFACE_H                                      */
/*Description    : An educational EXTI driver File for STM32F103C MC     */
/* Date          : 10 FEB-2022                                           */
/* Version       : V1.1 -> essential tests are passed                    */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H
/******************* Procedure for using external pins IRQ ********************/
            /* Enable GPIO and AFIO clocks through RCC controller */
             /** Config the required GPIO pin as floating input **/
   /*** Map the external required pins to the lines through AFIO_EXTICRx ***/
      /**** Config the required line through EXTI_u8ConfigLine() fn ****/
              /***** Enable NVIC IRQn for the required line *****/
               /****** Set the required call back function *****/
           /******* Enable Interrupt mask in EXTI controller *******/
/******************************************************************************/
/*Triggering mode options*/
#define RISING_EDGE_TRIGGERING    1
#define FALLING_EDGE_TRIGGERING   3
#define ON_CHANGE_TRIGGERING      5
/* Please comment the def line if it isn't needed*/
#define EXTI0_LINE            0
//#define EXTI1_LINE            1
//#define EXTI2_LINE            2
//#define EXTI3_LINE            3
//#define EXTI4_LINE            4

//#define EXTI5_LINE            5
//#define EXTI6_LINE            6
//#define EXTI7_LINE            7
//#define EXTI8_LINE            8
//#define EXTI9_LINE            9

//#define EXTI10_LINE           10
//#define EXTI11_LINE           11
//#define EXTI12_LINE           12
//#define EXTI13_LINE           13
//#define EXTI14_LINE           14
//#define EXTI15_LINE           15

//#define EXTI16_PVD_LINE       16
//#define EXTI17_RTCAlarm_LINE  17
//#define EXTI18_USBWakeup_LINE 18

/** NOTE: lines from 5-9 and from 10-15 each have only one IRQn Handler **/


/*
Sets the required called function in the IRQ handler
NOTE:
  lines 5-9  only have one handler
  line 10-15 only have one handler
  The last passed function is the active one for them
*/
void EXTI_voidSetCallBackFn (u8 Copy_u8EXTI_Line , void (*fnPtr)(void));

u8 EXTI_u8ConfigLine       (u8 Copy_u8EXTI_Line , u8 Copy_u8TriggeringMode);

u8 EXTI_u8EnableLineIRQ     (u8 Copy_u8EXTI_Line);
u8 EXTI_u8DisableLineIRQ    (u8 Copy_u8EXTI_Line);

u8 EXTI_u8EnableLineEvent   (u8 Copy_u8EXTI_Line);
u8 EXTI_u8DisableLineEvent  (u8 Copy_u8EXTI_Line);


u8 EXTI_u8SetSoftWareTrig  (u8 Copy_u8EXTI_Line);
u8 EXTI_u8ClrPendingFlag   (u8 Copy_u8EXTI_Line);


/******************************************************************************/

/*ERRORS*/
#define EXTI_OK             0
#define BAD_EXTI_LINE       2
#define BAD_TRIGGERING_MODE 4
#endif  /*EXTI_INTERFACE_H*/
