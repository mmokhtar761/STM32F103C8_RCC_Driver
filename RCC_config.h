/******************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                                 */
/* File          : RCC_config.h                                               */
/* Date          : 8 NOV 2021                                                 */
/* Version       : V06 -> Compilled and tested the essential functions        */
/* GitHub        : https://github.com/mmokhtar761                             */
/******************************************************************************/
#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H
/******************************************************************************/
/******************** System Clock Source Configurations **********************/
/******************************************************************************/
/*
Options for RCC_SYS_CLK_SOURCE :
  RCC_HSE_CRYSTAL        (4-16)MHz
  RCC_HSE_RC             (<=25) MHz
  RCC_HSI_RC             8 MHz
  RCC_PLL_HSE
  RCC_PLL_HSE_BY_2
  RCC_PLL_HSI_BY_2
*/
//Pleasw choose one
#define RCC_SYS_CLK_SOURCE RCC_HSE_CRYSTAL
/*----------------------------------------------------------------------------*/
               /*Please, configure the folliwing PLL parameters*/
                                 /*IF NEEDED*/
/*----------------------------------------------------------------------------*/
#if   RCC_SYS_CLK_SOURCE == RCC_PLL_HSE
    //Options 2, 3, 4,.. 8 (Please NOTE, PLL output can't exceed 72MHz)
#   define RCC_PLL_MUL_FACTOR 2
#   define RCC_PLL_IS_ON

#elif RCC_SYS_CLK_SOURCE == RCC_PLL_HSI_BY_2
    //Options 2, 3, 4,.. 16 (Please NOTE, PLL output can't exceed 64MHz)
#   define RCC_PLL_MUL_FACTOR 2
#   define RCC_PLL_IS_ON

#elif RCC_SYS_CLK_SOURCE == RCC_PLL_HSE_BY_2
    //Options 2, 3, 4, 8, 9 (Please NOTE, PLL output can't exceed 72MHz)
#   define RCC_PLL_MUL_FACTOR 2
#   define RCC_PLL_IS_ON

#endif /*RCC_PLL_MUL_FACTOR end */
/*----------------------------------------------------------------------------*/
              /*If external HSE source is used, define its value*/
/*----------------------------------------------------------------------------*/
#if RCC_SYS_CLK_SOURCE!=RCC_HSI_RC && RCC_SYS_CLK_SOURCE!=RCC_PLL_HSI_BY_2
/*
  Options:
    4-16 MHz for RCC_HSE_CRYSTAL
    0-8 MHz  for RCC_HSE_RCC
*/
#define RCC_HSE_FRQ  8000000
#endif /*RCC_HSE_FRQ*/
/******************************************************************************/
/********************** Buses Domain Clock Configuration **********************/
/******************************************************************************/
//NOTE : SYS_CLK Feeds-> AHB Feeds-> (APB1 & APB2)

                      /* First: AHB With Max Freq 72MHz */
//Options 1, 2, 4, 8, 16....512 from the SYS_CLK
#define RCC_AHB_PRESC 1

                     /* Second: APB1 With Max Freq 36MHz */
/*
  NOTE: If RCC_APB1_PRESC != 1, the clk feeded to timers (2,3,4,5,6,7,12,13,14)
    is multiplied by 2
*/
//Options 1, 2, 4, 8, 16  from the AHB_CLK
#define RCC_APB1_PRESC 1

                     /* Third: APB2 With Max Freq 72MHz */
/*
  NOTE: If RCC_APB2_PRESC != 1, the clk feeded to timers (1,8,9,10,11)
    is multiplied by 2
*/
//Options 1, 2, 4, 8, 16  from the AHB_CLK
#define RCC_APB2_PRESC 1

/*ADC clk prescaler (CAN NOT exceed 14MHz)
Options 2, 4, 6, 8       from the APB2_CLK*/
#define RCC_ADC_PRES 2

//Options 1 , 1.5  from the SYS_CLK
#define RCC_USB_PRES 2


/******************************************************************************/
#endif  /*RCC_CONFIG_H end */
