/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          :                                                       */
/*Description    : An educational EXTI driver File for STM32F103C MC     */
/* Date          : 10 FEB-2022                                           */
/* Version       : V1.1 -> essential tests are passed                    */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#include "STD_TYPES.h"
#include "MANIPULATOR.h"
#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

u8 EXTI_u8ConfigLine (u8 Copy_u8EXTI_Line , u8 Copy_u8TriggeringMode)
{
  if (Copy_u8EXTI_Line > 18) return BAD_EXTI_LINE;
  switch (Copy_u8TriggeringMode)
  {
    case RISING_EDGE_TRIGGERING :
      BIT_H(MY_EXTI->EXTI_RTSR , Copy_u8EXTI_Line);
      BIT_L(MY_EXTI->EXTI_FTSR , Copy_u8EXTI_Line); break;
    case FALLING_EDGE_TRIGGERING:
      BIT_H(MY_EXTI->EXTI_FTSR , Copy_u8EXTI_Line);
      BIT_L(MY_EXTI->EXTI_RTSR , Copy_u8EXTI_Line); break;
    case ON_CHANGE_TRIGGERING   :
      BIT_H(MY_EXTI->EXTI_RTSR , Copy_u8EXTI_Line);
      BIT_H(MY_EXTI->EXTI_FTSR , Copy_u8EXTI_Line); break;
    default                     :
      return BAD_TRIGGERING_MODE;
  }
  return EXTI_OK;
}

/*-----------------------------------------------------------------*/

u8 EXTI_u8EnableLineIRQ    (u8 Copy_u8EXTI_Line)
{
  if (Copy_u8EXTI_Line > 18) return BAD_EXTI_LINE;
  BIT_H(MY_EXTI->EXTI_IMR , Copy_u8EXTI_Line);
  return EXTI_OK;
}
u8 EXTI_u8DisableLineIRQ    (u8 Copy_u8EXTI_Line)
{
  if (Copy_u8EXTI_Line > 18) return BAD_EXTI_LINE;
  BIT_L(MY_EXTI->EXTI_IMR , Copy_u8EXTI_Line);
  return EXTI_OK;
}
/*-----------------------------------------------------------------*/
u8 EXTI_u8EnableLineEvent  (u8 Copy_u8EXTI_Line)
{
  if (Copy_u8EXTI_Line > 18) return BAD_EXTI_LINE;
  BIT_H(MY_EXTI->EXTI_EMR , Copy_u8EXTI_Line);
  return EXTI_OK;
}
u8 EXTI_u8DisableLineEvent  (u8 Copy_u8EXTI_Line)
{
  if (Copy_u8EXTI_Line > 18) return BAD_EXTI_LINE;
  BIT_L(MY_EXTI->EXTI_EMR , Copy_u8EXTI_Line);
  return EXTI_OK;
}
/*-----------------------------------------------------------------*/
u8 EXTI_u8SetSoftWareTrig  (u8 Copy_u8EXTI_Line)
{
    BIT_H(MY_EXTI->EXTI_SWIER , Copy_u8EXTI_Line);
    return EXTI_OK;
}
u8 EXTI_u8ClrPendingFlag   (u8 Copy_u8EXTI_Line)
{
  BIT_H(MY_EXTI->EXTI_PR , Copy_u8EXTI_Line);
  return EXTI_OK;
}
void EXTI_voidSetCallBackFn (u8 Copy_u8EXTI_Line , void (*fnPtr)(void))
{
  EXTI_CallBack[Copy_u8EXTI_Line] = fnPtr;
}

/******************************************************************************/
/********************* Handlers definition for EXTI IRQs *********************/
/******************************************************************************/
#ifdef EXTI0_LINE
void EXTI0_IRQHandler(void){
	(EXTI_CallBack[EXTI0_LINE])();
	BIT_H( MY_EXTI->EXTI_PR , EXTI0_LINE );
}
#endif

#ifdef EXTI1_LINE
void EXTI1_IRQHandler(void){
	(EXTI_CallBack[EXTI1_LINE])();
	BIT_H( MY_EXTI->EXTI_PR , EXTI1_LINE );
}
#endif

#ifdef EXTI2_LINE
void EXTI2_IRQHandler(void){
	(EXTI_CallBack[EXTI2_LINE])();
	BIT_H( MY_EXTI->EXTI_PR , EXTI2_LINE );
}
#endif

#ifdef EXTI3_LINE
void EXTI3_IRQHandler(void){
	(EXTI_CallBack[EXTI3_LINE])();
	BIT_H( MY_EXTI->EXTI_PR , EXTI3_LINE );
}
#endif

#ifdef EXTI4_LINE
void EXTI4_IRQHandler(void){
	(EXTI_CallBack[EXTI4_LINE])();
	BIT_H( MY_EXTI->EXTI_PR , EXTI4_LINE );
}
#endif

#ifdef EXTI9_5_LINES_IRQ
void EXTI9_5_IRQHandler(void){
	(EXTI_CallBack[EXTI9_5_LINES_IRQ])();
	BIT_H( MY_EXTI->EXTI_PR , EXTI9_5_LINES_IRQ );
}
#endif

#ifdef EXTI15_10_LINES_IRQ
void EXTI15_10_IRQHandler(void){
	(EXTI_CallBack[EXTI15_10_LINES_IRQ])();
	BIT_H( MY_EXTI->EXTI_PR , EXTI15_10_LINES_IRQ );
}
#endif

#ifdef EXTI16_PVD_LINE
void PVD_IRQHandler(void){
	(EXTI_CallBack[EXTI16_PVD_LINE])();
	BIT_H( MY_EXTI->EXTI_PR , EXTI16_PVD_LINE );
}
#endif

#ifdef EXTI17_RTCAlarm_LINE
void RTCAlarm_IRQHandler(void){
	(EXTI_CallBack[EXTI17_RTCAlarm_LINE])();
	BIT_H( MY_EXTI->EXTI_PR , EXTI17_RTCAlarm_LINE );
}
#endif

#ifdef EXTI18_USBWakeup_LINE
void USBWakeup_IRQHandler(void){
	(EXTI_CallBack[EXTI18_USBWakeup_LINE])();
	BIT_H( MY_EXTI->EXTI_PR , EXTI18_USBWakeup_LINE );
}
#endif
/******************************************************************************/
/***************** End of handlers definition for EXTI IRQs ******************/
/******************************************************************************/
