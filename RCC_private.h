/******************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                                 */
/* File          : RCC_private.h                                              */
/* Date          : 8 NOV 2021                                                 */
/* Version       : V05 -> Structure register definition & Some optimizations  */
/* GitHub        : https://github.com/mmokhtar761                             */
/******************************************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H


/******************************************************************************/
/****RCC_Registers definitions with offset equals 4 to the RCC_BASE_ADDRESS****/
/******************************************************************************/
typedef struct
{
  //CPU CLK-source controlling RCC_Registers
  volu32 RCC_CR;
  volu32 RCC_CFGR;
  //-------------------------------------------------------
  volu32 RCC_CIR;
  volu32 RCC_APB2RSTR;
  volu32 RCC_APB1RSTR;
  //Prepherals-clock EN/!EN RCC_Registers for the 3 buses
  volu32 RCC_AHBENR;
  volu32 RCC_APB2ENR;
  volu32 RCC_APB1ENR;
  //-------------------------------------------------------
  volu32 RCC_BDCR;
  volu32 RCC_CSR;
} RCC_RegType;
#define  RCC_ADDRESS_OFFSET  0x4
#define  RCC_BASE_ADDRESS    0x40021000
#define  MY_RCC            ((RCC_RegType *)RCC_BASE_ADDRESS)
/******************************************************************************/
/************************ Max operatting parameters  **************************/
/******************************************************************************/
#define RCC_SYS_MAX_FRQ         72000000  //72-Mega Hz
#define RCC_AHB_MAX_FRQ         72000000  //72-Mega Hz
#define RCC_ABP2_MAX_FRQ        72000000  //72-Mega Hz
#define RCC_ABP1_MAX_FRQ        36000000  //36-Mega Hz
#define RCC_ADC_MAX_FRQ         14000000  //14-Mega Hz

#define RCC_HSE_RC_MAX_FRQ      25000000  //25-Mega Hz
#define RCC_HSE_CRYSTAL_MAX_FRQ 16000000  //16-Mega Hz

#define RCC_HSI_FRQ             8000000   // 8-Mega Hz
#define RCC_PLL_HSI_MAX_FRQ     64000000  //64-Mega Hz


#define RCC_HSI_TRIM_STEP       40000     //40 KHz
#define RCC_MAX_CALIBRATION_VAL 0x1F
/******************************************************************************/
#endif  /*RCC_PRIVATE_H end*/
