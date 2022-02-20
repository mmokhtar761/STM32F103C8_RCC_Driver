/******************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                                 */
/* File          : GPIO_program.c                                             */
/* Date          : 25 DEC 2021                                                */
/* Version       : V01                                                        */
/* GitHub        : https://github.com/mmokhtar761                             */
/******************************************************************************/


/******************************************************************************/
/************************** Configuration Functions ***************************/
/******************************************************************************/
u8 GPIO_u8ConfigPin (u8 Copy_u8Port , u8 Copy_u8PinNumber , u8 Copy_u8Mode)
{
  if (Copy_u8Port <= 6)
  {
    /*In case of I_PULL_UP & I_PULL_DOWN additional operations are needed*/
    if     (Copy_u8Mode== I_PULL_UP )
    {
      /*Assign pull up value to ODR reg */
      MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_BSRR = 1 < Copy_u8PinNumber;
      /*Ignoring the pull up bit*/
      Copy_u8Mode = Copy_u8Mode >> 1;
    }
    else if (Copy_u8Mode== I_PULL_DOWN)
    {
      /*Assign pull down value to ODR reg */
      MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_BRR  = 1 < Copy_u8PinNumber;
      /*Ignoring the pull down bit*/
      Copy_u8Mode = Copy_u8Mode >> 1;
    }

    if      (Copy_u8PinNumber < 8)
    {
      MAN_NIBBLE(MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_CRL,Copy_u8PinNumber*4,Copy_u8Mode);
    }
    else if (Copy_u8PinNumber < 16)
    {
      Copy_u8PinNumber-=8;
      MAN_NIBBLE(MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_CRH,Copy_u8PinNumber*4,Copy_u8Mode);
    }
    else return GPIO_ERROR_WRONG_PIN;
  }
  else return GPIO_ERROR_WRONG_PORT;
}
/*----------------------------------------------------------------------------*/
u8 GPIO_u8ConfigHalfPort (u8 Copy_u8Port , u8 Copy_u8HalfSide  , u8 Copy_u8Mode)
{
  u32 Local_u32HalfPortMode=0;
  u8 i =0;
  if (Copy_u8Port <= 6)
  {
    /*In case of I_PULL_UP & I_PULL_DOWN additional operations are needed*/
    if     (Copy_u8Mode== I_PULL_UP )
    {
      /*Assign pull up value to ODR reg */
      //MAN_BYTE(MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_ODR,Copy_u8HalfSide*8,0xFF)
      MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_BSRR = 0xFF << Copy_u8HalfSide * 8;
      /*Ignoring the pull up bit*/
      Copy_u8Mode = Copy_u8Mode >> 1;
    }
    else if (Copy_u8Mode== I_PULL_DOWN)
    {
      /*Assign pull down value to ODR reg */
      MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_BRR  = 0xFF << Copy_u8HalfSide * 8;
      /*Ignoring the pull down bit*/
      Copy_u8Mode = Copy_u8Mode >> 1;
    }
    for (i=0;i<16;i+=4) Local_u32HalfPortMode += (Copy_u8Mode << i);
    if      ( Copy_u8HalfSide)MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_CRH = Local_u32PortMode;
    else if (!Copy_u8HalfSide)MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_CRL = Local_u32PortMode;
  }
  else return GPIO_ERROR_WRONG_PORT;
}
/*----------------------------------------------------------------------------*/
u8 GPIO_u8ConfigPort (u8 Copy_u8Port , u8 Copy_u8Mode)
{
  u32 Local_u32PortMode=0;
  u8 i =0;
  if (Copy_u8Port <= 6)
  {
    /*In case of I_PULL_UP & I_PULL_DOWN additional operations are needed*/
    if     (Copy_u8Mode== I_PULL_UP )
    {
      /*Assign pull up value to ODR reg */
      MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_BSRR = 0xFFFF;
      /*Ignoring the pull up bit*/
      Copy_u8Mode = Copy_u8Mode >> 1;
    }
    else if (Copy_u8Mode== I_PULL_DOWN)
    {
      /*Assign pull down value to ODR reg */
      MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_BRR  = 0xFFFF;
      /*Ignoring the pull down bit*/
      Copy_u8Mode = Copy_u8Mode >> 1;
    }
    for (i=0;i<32;i+=4) Local_u32PortMode += (Copy_u8Mode << i);
    MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_CRL = Local_u32PortMode;
    MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_CRH = Local_u32PortMode;
  }
  else return GPIO_ERROR_WRONG_PORT;
}

/******************************************************************************/
/************************** Setting-value functions ***************************/
/******************************************************************************/
u8 GPIO_u8SetPinValue      (u8 Copy_u8Port , u8 Copy_u8PinNumber , u8 Copy_u8PinValue)
{
  if (Copy_u8Port>6) return GPIO_ERROR_WRONG_PORT;
  if (Copy_u8PinNumber<16)
  {
    if (Copy_u8PinValue == 0) Copy_u8PinNumber+=16
    MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_BSRR = 1 << Copy_u8PinNumber;
    return GPIO_OK;
  }
  else return GPIO_ERROR_WRONG_PIN;
}
/*----------------------------------------------------------------------------*/
u8 GPIO_u8SetHalfPortValue (u8 Copy_u8Port , u8 Copy_u8HalfSide  , u16 Copy_u16HalfPortValue)
{


  if      (Copy_u8Port>6) return GPIO_ERROR_WRONG_PORT;
  if      (Copy_u16HalfPortValue == 0xFF )
  {
    MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_BSRR = 0xFF << (Copy_u8HalfSide*8);
  }
  else if (Copy_u16HalfPortValue == 0x00)
  {
    MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_BRR  = 0xFF << (Copy_u8HalfSide*8);
  }
  else
  {
    MAN_BYTE(MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_ODR,0,Copy_u16HalfPortValue);
  }
  return GPIO_OK;
}
/*----------------------------------------------------------------------------*/
u8 GPIO_u8SetPortValue     (u8 Copy_u8Port , u32 Copy_u32PortValue)
{


  if      (Copy_u8Port>6) return GPIO_ERROR_WRONG_PORT;
  if      (Copy_u32PortValue == 0xFFFF )
  {
    MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_BSRR = 0xFFFF;
  }
  else if (Copy_u32PortValue == 0x00)
  {
    MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_BRR  = 0xFFFF;
  }
  else
  {
    MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_ODR = Copy_u32PortValue;
  }
  return GPIO_OK;
}
/******************************************************************************/
/************************** Getting-value functions ***************************/
/******************************************************************************/
u8  GPIO_u8GetPinValue      (u8 Copy_u8Port , u8 Copy_u8PinNumber)
{
  return GET_BIT(MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_IDR,Copy_u8PinNumber);
}
/*----------------------------------------------------------------------------*/
u16 GPIO_u8GetHalfPortValue (u8 Copy_u8Port , u8 Copy_u8HalfSide)
{
  return GET_BYTE(MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_IDR,Copy_u8HalfSide*8);
}
/*----------------------------------------------------------------------------*/
u32 GPIO_u8GetPortValue     (u8 Copy_u8Port)
{
  return MY_PASSED_GPIO_PORT(Copy_u8Port)->GPIO_IDR;
}
