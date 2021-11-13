/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : RCC_interface.h                                       */
/* Date          : 8 NOV 2021                                            */
/* Version       : V01                                                   */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

void RCC_voidInitClk( void);
void RCC_voidEnPeripheralClk ( u8 Copy_u8PeripheralBus  , u8 Copy_u8Peripheral );
void RCC_voidDisPeripheralClk( u8 Copy_u8PeripheralBus  , u8 Copy_u8Peripheral );

/****************************HSI Calibraton section****************************/
//Note : needed only if HSI is enabled
//Uncomment the following line if calibration is needed
//#define RCC_HSI_CALIBRATION_EN
#ifdef RCC_HSI_CALIBRATION_EN
    s16  RCC_s16GetHSITrimVal(void);
    //Copy_calibrationOffset must be a devidable by 40,000 Hz
    void RCC_voidTrimHSI(s16 Copy_calibrationOffset);
#endif /*RCC_HSI_CALIBRATION_EN end */

/*************************Main clock output on MCO Pin*************************/
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







#endif  /*RCC_INTERFACE_H END */
