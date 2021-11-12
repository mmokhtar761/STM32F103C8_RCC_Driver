/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : RCC_dependantInterface.h                              */
/* Date          : 8 NOV 2021                                            */
/* Version       : V01                                                   */
/* GitHub        : https://github.com/mmokhtar761                        */
/*************************************************************************/




//#ifndef RCC_DEPENDANT_INTERFACE_H
#define RCC_DEPENDANT_INTERFACE_H

#ifdef CALIBRATION_EN
    s16  RCC_s16GetHSITrimVal(void);
    //Copy_calibrationOffset must be a devidable by 40,000 Hz
    void RCC_voidTrimHSI(s16 Copy_calibrationOffset);
#endif /*CALIBRATION_EN end */


#endif  /*RCC_DEPENDANT_INTERFACE_H END */
