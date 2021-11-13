/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : RCC_private.h                                         */
/* Date          : 8 NOV 2021                                            */
/* Version       : V01                                                   */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H



/****RCC_Registers definitions with offset equals 4 to the RCC_BASE_ADDRESS****/
#define  RCC_BASE_ADDRESS    0x40021000
#define  RCC_ADDRESS_OFFSET  0x4
//CPU CLK-source controlling RCC_Registers
#define  RCC_CR              *((volatile u32 *)0x40021000)
#define  RCC_CFGR            *((volatile u32 *)0x40021004)
//-------------------------------------------------------
#define  RCC_CIR             *((volatile u32 *)0x40021008)
#define  RCC_APB2RSTR        *((volatile u32 *)0x4002100C)
#define  RCC_APB1RSTR        *((volatile u32 *)0x40021010)
//Prepherals-clock EN/!EN RCC_Registers for the 3 buses
#define  RCC_AHBENR          *((volatile u32 *)0x40021014)
#define  RCC_APB2ENR         *((volatile u32 *)0x40021018)
#define  RCC_APB1ENR         *((volatile u32 *)0x4002101C)
//-------------------------------------------------------
#define  RCC_BDCR       		 *((volatile u32 *)0x40021020)
#define  RCC_CSR             *((volatile u32 *)0x40021024)

/**************************Max operatting frequancies**************************/
#define RCC_SYS_MAX_FRQ         72000000  //72-Mega Hz
#define RCC_AHB_MAX_FRQ         72000000  //72-Mega Hz
#define RCC_ABP2_MAX_FRQ        72000000  //72-Mega Hz
#define RCC_ABP1_MAX_FRQ        36000000  //36-Mega Hz
#define RCC_ADC_MAX_FRQ         14000000
#define RCC_HSI_FRQ             8000000   // 8-Mega Hz

#define RCC_HSE_RC_MAX_FRQ      25000000  //25-Mega Hz
#define RCC_HSE_CRYSTAL_MAX_FRQ 16000000  //16-Mega Hz

#define RCC_PLL_HSI_MAX_FRQ     64000000  //64-Mega Hz

/**************************Options for sys clk source**************************/
#define RCC_HSE_CRYSTAL         0
#define RCC_HSE_RC              1
#define RCC_HSI_RC              2
#define RCC_PLL_HSE             3
#define RCC_PLL_HSE_BY_2        4
#define RCC_PLL_HSI_BY_2        5


#define RCC_HSI_TRIM_STEP 40000 //40 KHz
#define RCC_MAX_CALIBRATION_VAL 0x1F

#endif  /*RCC_PRIVATE_H end*/
