/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : RCC_config.h                                         */
/* Date          : 8 NOV 2021                                            */
/* Version       : V01                                                   */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H
/**********************System Clock Source Configurations**********************/
/* Options for RCC_SYS_CLK_SOURCE :
  RCC_HSE_CRYSTAL         (4-16)MHz
  RCC_HSE_RC              (<=25) MHz
  RCC_HSI_RC              8 MHz
  RCC_PLL_HSE
  RCC_PLL_HSE_BY_2
  RCC_PLL_HSI_BY_2
*/
#define RCC_SYS_CLK_SOURCE RCC_HSE_CRYSTAL

#if   RCC_SYS_CLK_SOURCE == RCC_PLL_HSE
    //Options 2, 3, 4,.. 8 (PLL output can't exceed 72MHz)
#   define RCC_PLL_MUL_FACTOR 2
#   define RCC_PLL_IS_ON

#elif RCC_SYS_CLK_SOURCE == RCC_PLL_HSI_BY_2
    //Options 2, 3, 4,.. 16 (PLL output can't exceed 64MHz)
#   define RCC_PLL_MUL_FACTOR 2
#   define RCC_PLL_IS_ON

#elif RCC_SYS_CLK_SOURCE == RCC_PLL_HSE_BY_2
    //Options 2, 3, 4, 8, 9 (PLL output can't exceed 72MHz)
#   define RCC_PLL_MUL_FACTOR 2
#   define RCC_PLL_IS_ON

#endif /*RCC_PLL_MUL_FACTOR end */

#if RCC_SYS_CLK_SOURCE!=RCC_HSI_RC && RCC_SYS_CLK_SOURCE!=RCC_PLL_HSI_BY_2
/*Options :
    4-16 MHz for RCC_HSE_CRYSTAL
    0-8 MHz  for RCC_HSE_RCC   */
#define RCC_HSE_FRQ  4000000
#endif

//Uncomment this line if calibration is needed
//#define CALIBRATION_EN


/***********************Buses Domain Clock Configuration***********************/
//NOTE : SYS_CLK Feeds-> AHB Feeds-> (APB1 & APB2)

//First: AHB With Max Freq 72MHz
//Options 1, 2, 4, 8, 16....512 from the SYS_CLK
#define RCC_AHB_PRESC 1

//Second: APB1 With Max Freq 36MHz
//If RCC_APB1_PRESC != 1, the clk feeded to timers is multiplied by 2
//Options 1, 2, 4, 8, 16  from the AHB_CLK
#define RCC_APB1_PRESC 1

//Third: APB2 With Max Freq 72MHz
//Options 1, 2, 4, 8, 16  from the AHB_CLK
#define RCC_APB2_PRESC 1
/*ADC clk prescaler (CAN NOT exceed 14MHz)
Options 2, 4, 6, 8       from the APB2_CLK*/
#define RCC_ADC_PRES 2

/*************************Main clock output on MCO Pin*************************/
//Options: Comment the next line if there is no need for MCO pin
//#define RCC_MCO_ENABLE
#ifdef  RCC_MCO_ENABLE
    /*Options :
        RCC_MCO_SYS_CLK
        RCC_MCO_HSI
        RCC_MCO_HSE
        RCC_MCO_PLL_BY_2
    */
#   define RCC_MCO_SELECT RCC_MCO_SYS_CLK
#endif  /*RCC_MCO_ENABLE end */

/*********************Run-Time Clk Manipiulation Functions*********************/
/* For run time decisions about Clk source, User can enable these feature.    */
//#define RCC_RUN_TIME_CLK_SELECT_ENABLE
/*Uncomment this line to enable the compilation of the following Functions :
    int RCC_intCheckActiveClkSource ()
    void RCC_voidSetHSI8MHzCLK()
    .
    .
    .
    .


*/


/******************************************************************************/
#endif  /*RCC_CONFIG_H end */
