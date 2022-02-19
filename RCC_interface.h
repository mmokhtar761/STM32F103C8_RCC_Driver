/******************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                                 */
/* File          : RCC_interface.h                                            */
/* Date          : 8 NOV 2021                                                 */
/* Version       : V05 -> Structure register definition & Some optimizations  */
/* GitHub        : https://github.com/mmokhtar761                             */
/******************************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/******************************************************************************/
/********************** Essential RCC functions section ***********************/
/******************************************************************************/

    /*Initialize Clock configurations as selected  and prompets
                         compilation errors if any limitations is exceeded*/
void RCC_voidInitClk( void);
/*----------------------------------------------------------------------------*/
                           /*EN/!EN Prepherals CLKs*/
void RCC_voidEnPeripheralClk  ( u8 Copy_u8PeripheralBus  , u8 Copy_u8Peripheral );
void RCC_voidDisPeripheralClk ( u8 Copy_u8PeripheralBus  , u8 Copy_u8Peripheral );
/*----------------------------------------------------------------------------*/
                           /*Activate SysClk as HSI*/
void RCC_voidSetHSI8MHzCLK    (void);
/*----------------------------------------------------------------------------*/
   /*Returns the actual active clk configuration
                                    returned values are as descripeds below*/
#define RCC_HSE_CRYSTAL         0
#define RCC_HSE_RC              1
#define RCC_HSI_RC              2
#define RCC_PLL_HSE             3
#define RCC_PLL_HSE_BY_2        4
#define RCC_PLL_HSI_BY_2        5
u8   RCC_u8CheckActiveClkSource (void);
    //to go back to preconfigered clk options, call RCC_voidInitClk()
/*----------------------------------------------------------------------------*/
                            /*Retun Freq unit is Hz*/
u32  RCC_u32GetSysClkFreq     (void);
u32  RCC_u32GetBusClkFreq  (u8 Copy_u8PeripheralBus);
/*----------------------------------------------------------------------------*/
                        /* Choose arguments from below */
//Copy_u8PeripheralBus options
#define RCC_AHB_BUS_ID    2
#define RCC_APB1_BUS_ID   4
#define RCC_APB2_BUS_ID   6

//Copy_u8Peripheral for RCC_AHB_BUS
#define RCC_DMA1_CLK_EN   0
#define RCC_DMA2_CLK_EN   1
#define RCC_SRAM_CLK_EN   2
#define RCC_FLITF_CLK_EN  4
#define RCC_CRCE_CLK_EN   6
#define RCC_FSMC_CLK_EN   8
#define RCC_SDIO_CLK_EN   10
//Copy_u8Peripheral for RCC_APB1_BUS
#define RCC_TIM2_CLK_EN   0
#define RCC_TIM3_CLK_EN   1
#define RCC_TIM4_CLK_EN   2
#define RCC_TIM5_CLK_EN   3
#define RCC_TIM6_CLK_EN   4
#define RCC_TIM7_CLK_EN   5
#define RCC_TIM12_CLK_EN  6
#define RCC_TIM13_CLK_EN  7
#define RCC_TIM14_CLK_EN  8
#define RCC_WWDG_CLK_EN   11
#define RCC_SPI2_CLK_EN   14
#define RCC_SPI3_CLK_EN   15
#define RCC_USART2_CLK_EN 17
#define RCC_USART3_CLK_EN 18
#define RCC_USART4_CLK_EN 19
#define RCC_USART5_CLK_EN 20
#define RCC_I2C1_CLK_EN   21
#define RCC_I2C2_CLK_EN   22
#define RCC_USB_CLK_EN    23
#define RCC_CAN_CLK_EN    25
#define RCC_BKP_CLK_EN    27
#define RCC_PWR_CLK_EN    28
#define RCC_DAC_CLK_EN    29

//Copy_u8Peripheral for RCC_APB2_BUS
#define RCC_AFIO_CLK_EN   0
#define RCC_IOPA_CLK_EN   2
#define RCC_IOPB_CLK_EN   3
#define RCC_IOPC_CLK_EN   4
#define RCC_ADC1_CLK_EN   9
#define RCC_ADC2_CLK_EN   10
#define RCC_TIM1_CLK_EN   11
#define RCC_SPI1_CLK_EN   12
#define RCC_TIM8_CLK_EN   13
#define RCC_USART1_CLK_EN 14
#define RCC_ADC3_CLK_EN   15
#define RCC_TIM9_CLK_EN   19
#define RCC_TIM10_CLK_EN  20
#define RCC_TIM11_CLK_EN  21

/******************************************************************************/
/************************** HSI Calibraton section ****************************/
/******************************************************************************/
//Note : needed only if HSI is enabled
//Uncomment the following line if calibration is needed
//#define RCC_HSI_CALIBRATION_EN
#ifdef RCC_HSI_CALIBRATION_EN
    s16  RCC_s16GetHSITrimVal(void);
    //Copy_calibrationOffset must be a devidable by 40,000 Hz
    void RCC_voidTrimHSI(s16 Copy_calibrationOffset);
#endif /*RCC_HSI_CALIBRATION_EN end */

/******************************************************************************/
/*********************** Main clock output on MCO Pin *************************/
/******************************************************************************/
//Options: Comment the next line if there is no need for MCO pin
//#define RCC_MCO_ENABLE
#ifdef  RCC_MCO_ENABLE
    //Options :
        #define RCC_MCO_SYS_CLK         0b100
        #define RCC_MCO_HSI             0b101
        #define RCC_MCO_HSE             0b110
        #define RCC_MCO_PLL_BY_2        0b111
    //end of Options
    void RCC_voidEnMCO (u8 Copy_u8OutputTypeMCO);
    void RCC_voidDisMCO(void);
#endif  /*RCC_MCO_ENABLE end */

/******************************************************************************/
/*********************Run-Time Clk Manipiulation Functions*********************/
/******************************************************************************/
  /* For run time decisions about Clk source, User can enable the feature */
//Uncomment the following line to enable the compilation of the following Functions :
//#define RCC_RUN_TIME_CLK_SELECT_ENABLE
ifdef RCC_RUN_TIME_CLK_SELECT_ENABLE

                        /*add the wanted prototypes here*/

#endif /*RCC_RUN_TIME_CLK_SELECT_ENABLE*/
/******************************************************************************/

#endif  /*RCC_INTERFACE_H END */
