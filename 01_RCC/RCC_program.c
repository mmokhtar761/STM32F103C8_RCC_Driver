/******************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                                 */
/* File          : RCC_program.c                                              */
/* Date          : 8 NOV 2021                                                 */
/* Version       : V06 -> Compilled and tested the essential functions        */
/* GitHub        : https://github.com/mmokhtar761                             */
/******************************************************************************/
#include "MANIPULATOR.h"
#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"
//#include "RCC_dependantInterface.h"

/******************************************************************************/
/********************** Essential RCC functions section ***********************/
/******************************************************************************/
void RCC_voidInitClk(void)
{
	                     /**Handling the SysClk**/

  #if   RCC_SYS_CLK_SOURCE == RCC_HSI_RC
			BIT_H(MY_RCC->RCC_CR,0); //HSI ON
			//Wait 5 cycles or HSIRDY Flag to be set by hardware
			do{
				i++;
			}while (i<5 || !GET_BIT(MY_RCC->RCC_CR,1));
			i = 0;
			//Choose HSI as SysClk by clearing the first 2 bits of MY_RCC->RCC_CFGR
			MY_RCC->RCC_CFGR = (MY_RCC->RCC_CFGR& ~0x3);
  #elif RCC_SYS_CLK_SOURCE == RCC_HSE_RC
			#if RCC_HSE_FRQ > 25000000
				#error "RCC_HSE_RC_MAX_FRQ is> 25000000"
			#endif
			BIT_L(MY_RCC->RCC_CR,16); //makesure HSE is Disabled before En the bypass
			BIT_H(MY_RCC->RCC_CR,18); //HSE bypass is ON
			BIT_H(MY_RCC->RCC_CR,16); //HSE ON
			//Wait 5 cycles or HSERDY Flag to be set by hardware
			do{
				i++;
			}while (i<5|| !GET_BIT(MY_RCC->RCC_CR,17));
			i = 0;
			//Choose HSE as SysClk
	  	MY_RCC->RCC_CFGR = (MY_RCC->RCC_CFGR& ~0x3) +1;
  #elif RCC_SYS_CLK_SOURCE == RCC_HSE_CRYSTAL
			#if RCC_HSE_FRQ > 16000000
				#error "RCC_HSE_CRYSTAL_MAX_FRQ is> 16000000"
			#endif
			BIT_L(MY_RCC->RCC_CR,18); //HSE bypass is OFF
			BIT_H(MY_RCC->RCC_CR,16); //HSE ON
			//Wait 5 cycles or HSERDY Flag to be set by hardware
			do{
				i++;
			}while (i<5|| !GET_BIT(MY_RCC->RCC_CR,17));
			i = 0;
			//Choose HSE as SysClk
			MY_RCC->RCC_CFGR = (MY_RCC->RCC_CFGR& ~0x3) +1;
  #elif RCC_SYS_CLK_SOURCE == RCC_PLL_HSE
			#if RCC_HSE_FRQ > 16000000
				#error "RCC_HSE_TO_PLL_MAX_FRQ is> 16000000"
			#endif
			//First These must be set before En PLL
			BIT_L(MY_RCC->RCC_CFGR,17); //HSE not devided
			BIT_H(MY_RCC->RCC_CFGR,16); //HSE selected for PLL entery
			BIT_L(MY_RCC->RCC_CR,18);   //HSE bypass is OFF
			BIT_H(MY_RCC->RCC_CR,16);   //HSE ON
			#if RCC_PLL_MUL_FACTOR*RCC_HSE_FRQ > RCC_SYS_MAX_FRQ
				#error "SYS_CLK_EXCEEDS_THA_MAX_72MHz"
			#elif RCC_PLL_MUL_FACTOR*RCC_HSE_FRQ/(RCC_AHB_PRESC*RCC_APB1_PRESC) > RCC_ABP1_MAX_FRQ
				#error "ABP1_CLK_EXCEEDS_THA_MAX_36MHz"
			#elif RCC_PLL_MUL_FACTOR*RCC_HSE_FRQ/(RCC_AHB_PRESC*RCC_APB2_PRESC*RCC_ADC_PRES) > RCC_ADC_MAX_FRQ
				#error "RCC_ADC_CLK_EXCEEDS_THA_MAX_14MHz"
			#endif /*RCC_PLL_MUL_FACTOR*RCC_HSI_FRQ/2 */
  #elif RCC_SYS_CLK_SOURCE == RCC_PLL_HSE_BY_2
			#if RCC_HSE_FRQ > 16000000
				#error "RCC_HSE/2_TO_PLL_MAX_FRQ is >  16000000"
			#endif
			//First These must be set before En PLL
			BIT_H(MY_RCC->RCC_CFGR,17); //HSE is devided by 2
			BIT_H(MY_RCC->RCC_CFGR,16); //HSE/2 selected for PLL entery
			BIT_L(MY_RCC->RCC_CR,18);   //HSE bypass is OFF
			BIT_H(MY_RCC->RCC_CR,16);   //HSE ON
			#if RCC_PLL_MUL_FACTOR*RCC_HSE_FRQ/2 > RCC_SYS_MAX_FRQ
				#error "SYS_CLK_EXCEEDS_THA_MAX_72MHz"
			#elif RCC_PLL_MUL_FACTOR*RCC_HSE_FRQ/(2*RCC_AHB_PRESC*RCC_APB1_PRESC) > RCC_ABP1_MAX_FRQ
				#error "AHP1_CLK_EXCEEDS_THA_MAX_36MHz"
			#elif RCC_PLL_MUL_FACTOR*RCC_HSE_FRQ/(2*RCC_AHB_PRESC*RCC_APB2_PRESC*RCC_ADC_PRES) > RCC_ADC_MAX_FRQ
				#error "RCC_ADC_CLK_EXCEEDS_THA_MAX_14MHz"
			#endif /*RCC_PLL_MUL_FACTOR*RCC_HSI_FRQ/2 */
  #elif RCC_SYS_CLK_SOURCE == RCC_PLL_HSI_BY_2
			//First These must be set before En PLL
			BIT_L(MY_RCC->RCC_CFGR,16); //HSI/2 selected for PLL entery
			BIT_H(MY_RCC->RCC_CR,0); //HSI ON
			#if   RCC_PLL_MUL_FACTOR*RCC_HSI_FRQ/(2*RCC_AHB_PRESC*RCC_APB1_PRESC) > RCC_ABP1_MAX_FRQ
				#error "AHP1_CLK_EXCEEDS_THA_MAX_36MHz"
			#elif RCC_PLL_MUL_FACTOR*RCC_HSI_FRQ/(2*RCC_AHB_PRESC*RCC_APB2_PRESC*RCC_ADC_PRES) > RCC_ADC_MAX_FRQ
				#error "RCC_ADC_CLK_EXCEEDS_THA_MAX_14MHz"
			#endif /*RCC_PLL_MUL_FACTOR*RCC_HSI_FRQ/2 */
  #endif /*RCC_SYS_CLK_SOURCE*/

	//PLL multiplication factor bits can be only written whan PLL is disabled
	#ifdef RCC_PLL_IS_ON
			BIT_L(MY_RCC->RCC_CR,24); //makesure PLL is Disabled before PLL MUL FACTOR assignment
			MAN_NIBBLE(MY_RCC->RCC_CFGR,18,(RCC_PLL_MUL_FACTOR-2)); //PLL MUL FACTOR assignment
			BIT_H(MY_RCC->RCC_CR,24); //PLL ON
			//Wait 5 cycles or PLLRDY Flag to be set by hardware
			do{
				i++;
			}while (i<5|| !GET_BIT(MY_RCC->RCC_CR,25));
			//Choose PLL as SysClk
			MY_RCC->RCC_CFGR = (MY_RCC->RCC_CFGR& ~0x3) +2;
	#endif /*RCC_PLL_IS_ON*/

	                   /** Handling Buses Domain Clock***/
	//First: AHB With Max Freq 72MHz
	//Options 1, 2, 4, 8, 16....512 from the SYS_CLK
	#if   RCC_AHB_PRESC == 1
		BIT_L(MY_RCC->RCC_CFGR,7);
	#elif RCC_AHB_PRESC == 2
	 	MAN_NIBBLE(MY_RCC->RCC_CFGR,4,0b1000) ;
	#elif RCC_AHB_PRESC == 4
		MAN_NIBBLE(MY_RCC->RCC_CFGR,4,0b1001) ;
	#elif RCC_AHB_PRESC == 8
		MAN_NIBBLE(MY_RCC->RCC_CFGR,4,0b1010) ;
	#elif RCC_AHB_PRESC == 16
		MAN_NIBBLE(MY_RCC->RCC_CFGR,4,0b1011) ;
	#elif RCC_AHB_PRESC == 64
		MAN_NIBBLE(MY_RCC->RCC_CFGR,4,0b1100) ;
	#elif RCC_AHB_PRESC == 128
	  MAN_NIBBLE(MY_RCC->RCC_CFGR,4,0b1101) ;
	#elif RCC_AHB_PRESC == 256
		MAN_NIBBLE(MY_RCC->RCC_CFGR,4,0b1110) ;
  #elif RCC_AHB_PRESC == 512
	  MAN_NIBBLE(MY_RCC->RCC_CFGR,4,0b1111) ;
	#endif

	//Second: APB1 With Max Freq 36MHz
	//If RCC_APB1_PRESC != 1, the clk feeded to timers is multiplied by 2
	//Options 1, 2, 4, 8, 16  from the AHB_CLK
	#if   RCC_APB1_PRESC == 1
		BIT_L(MY_RCC->RCC_CFGR,10);
	#elif RCC_APB1_PRESC == 2
	 	BIT_L(MY_RCC->RCC_CFGR,8);
		BIT_L(MY_RCC->RCC_CFGR,9);
		BIT_H(MY_RCC->RCC_CFGR,10);
	#elif RCC_APB1_PRESC == 4
		BIT_H(MY_RCC->RCC_CFGR,8);
		BIT_L(MY_RCC->RCC_CFGR,9);
		BIT_H(MY_RCC->RCC_CFGR,10);
	#elif RCC_APB1_PRESC == 8
		BIT_L(MY_RCC->RCC_CFGR,8);
		BIT_H(MY_RCC->RCC_CFGR,9);
		BIT_H(MY_RCC->RCC_CFGR,10);
	#elif RCC_APB1_PRESC == 16
		BIT_H(MY_RCC->RCC_CFGR,8);
		BIT_H(MY_RCC->RCC_CFGR,9);
		BIT_H(MY_RCC->RCC_CFGR,10);
	#endif /*RCC_APB1_PRESC*/

		//Third: APB2 With Max Freq 72MHz
		//Options 1, 2, 4, 8, 16  from the AHB_CLK
	#if   RCC_APB2_PRESC == 1  //PPRE2
		BIT_L(MY_RCC->RCC_CFGR,13);
	#elif RCC_APB2_PRESC == 2
		BIT_H(MY_RCC->RCC_CFGR,11);
		BIT_L(MY_RCC->RCC_CFGR,12);
		BIT_L(MY_RCC->RCC_CFGR,13);
	#elif RCC_APB2_PRESC == 4
		BIT_H(MY_RCC->RCC_CFGR,11);
		BIT_L(MY_RCC->RCC_CFGR,12);
		BIT_H(MY_RCC->RCC_CFGR,13);
	#elif RCC_APB2_PRESC == 8
		BIT_L(MY_RCC->RCC_CFGR,11);
		BIT_H(MY_RCC->RCC_CFGR,12);
		BIT_H(MY_RCC->RCC_CFGR,13);
	#elif RCC_APB2_PRESC == 16
		BIT_H(MY_RCC->RCC_CFGR,11);
		BIT_H(MY_RCC->RCC_CFGR,12);
		BIT_H(MY_RCC->RCC_CFGR,13);
	#endif   /*RCC_APB2_PRESC*/
	/*ADC clk prescaler (CAN NOT exceed 14MHz)
	Options 2, 4, 6, 8       from the APB2_CLK*/

	#if   RCC_ADC_PRES == 2
  	BIT_L(MY_RCC->RCC_CFGR,14);
		BIT_L(MY_RCC->RCC_CFGR,15);
	#elif RCC_ADC_PRES == 4
		BIT_H(MY_RCC->RCC_CFGR,14);
		BIT_L(MY_RCC->RCC_CFGR,15);
	#elif RCC_ADC_PRES == 6
		BIT_L(MY_RCC->RCC_CFGR,14);
		BIT_H(MY_RCC->RCC_CFGR,15);
	#elif RCC_ADC_PRES == 8
		BIT_H(MY_RCC->RCC_CFGR,14);
		BIT_H(MY_RCC->RCC_CFGR,15);
	#endif
}
/*----------------------------------------------------------------------------*/
void RCC_voidEnPeripheralClk ( u8 Copy_u8PeripheralBus  , u8 Copy_u8Peripheral )
{
	if      (Copy_u8PeripheralBus==RCC_AHB_BUS_ID)
	{
		BIT_H(MY_RCC->RCC_AHBENR,Copy_u8Peripheral);
	}
	else if (Copy_u8PeripheralBus==RCC_APB1_BUS_ID)
	{
		BIT_H(MY_RCC->RCC_APB1ENR,Copy_u8Peripheral);
	}
	else if (Copy_u8PeripheralBus==RCC_APB2_BUS_ID)
	{
		BIT_H(MY_RCC->RCC_APB2ENR,Copy_u8Peripheral);
	}
}
/*----------------------------------------------------------------------------*/
void RCC_voidDisPeripheralClk( u8 Copy_u8PeripheralBus  , u8 Copy_u8Peripheral )
{
	if      (Copy_u8PeripheralBus==RCC_AHB_BUS_ID)
	{
		BIT_L(MY_RCC->RCC_AHBENR,Copy_u8Peripheral);
	}
	else if (Copy_u8PeripheralBus==RCC_APB1_BUS_ID)
	{
		BIT_L(MY_RCC->RCC_APB1ENR,Copy_u8Peripheral);
	}
	else if (Copy_u8PeripheralBus==RCC_APB2_BUS_ID)
	{
		BIT_L(MY_RCC->RCC_APB2ENR,Copy_u8Peripheral);
	}

}
/*----------------------------------------------------------------------------*/
void RCC_voidSetHSI8MHzCLK()         //Activate SysClk as HSI
{
	BIT_H(MY_RCC->RCC_CR,0); //HSI ON
	//Wait 5 cycles or HSIRDY Flag to be set by hardware
	do{
		i++;
	}while (i<5|| !GET_BIT(MY_RCC->RCC_CR,17));
	//Choose HSI as SysClk
	MY_RCC->RCC_CFGR = (MY_RCC->RCC_CFGR& ~0x3);
	BIT_L(MY_RCC->RCC_CR,24); //PLL OFF
	BIT_L(MY_RCC->RCC_CR,16); //HSE OFF
}
/*----------------------------------------------------------------------------*/

u8 RCC_u8CheckActiveSysClkSource (void)  //Returns the active clk type
{
	u8 SWS =(MY_RCC->RCC_CFGR>2) & 0x3; //Reads bits [2,3]
	if (SWS==0)                        return RCC_HSI_RC;
	if (SWS==1 &&  GET_BIT(MY_RCC->RCC_CR,18)) return RCC_HSE_RC;
	if (SWS==1 && !GET_BIT(MY_RCC->RCC_CR,18)) return RCC_HSE_CRYSTAL;
	if (SWS==2 &&  GET_BIT(MY_RCC->RCC_CFGR,16)) { //Checks if HSE is the input of PLL
		if (GET_BIT(MY_RCC->RCC_CFGR,17)) return RCC_PLL_HSE_BY_2;
		else 							  			return RCC_PLL_HSE;
	}
	if (SWS==2 &&  !GET_BIT(MY_RCC->RCC_CFGR,16)) return RCC_PLL_HSI_BY_2;
	return 0; //ERROR//

}
/*----------------------------------------------------------------------------*/
u32  RCC_u32GetSysClkFreq     (void)
{
	u8 Local_u8SysFreqSource = RCC_u8CheckActiveSysClkSource();
	switch( Local_u8SysFreqSource )
	{
		case RCC_HSI_RC:
				return RCC_HSI_FRQ;
				break;
		case RCC_HSE_RC:
				return RCC_HSE_FRQ;
				break;
		case RCC_HSE_CRYSTAL:
				return RCC_HSE_FRQ;
				break;
#ifdef RCC_PLL_IS_ON

		case RCC_PLL_HSE:
				return RCC_HSE_FRQ * RCC_PLL_MUL_FACTOR;
				break;
		case RCC_PLL_HSE_BY_2:
				return RCC_HSE_FRQ/2 * RCC_PLL_MUL_FACTOR;
				break;
		case RCC_PLL_HSI_BY_2:
				return RCC_HSI_FRQ/2 * RCC_PLL_MUL_FACTOR;
				break;
#endif
			}
	return 0; //ERROR//


}
/*----------------------------------------------------------------------------*/
u32  RCC_u32GetBusClkFreq (u8 Copy_u8PeripheralBus)
{
	u32 Local_u32SysFreq = RCC_u32GetSysClkFreq();

	if      (Copy_u8PeripheralBus==RCC_AHB_BUS_ID)
	{
		return  Local_u32SysFreq * RCC_AHB_PRESC;
	}
	else if (Copy_u8PeripheralBus==RCC_APB1_BUS_ID)
	{
		return  Local_u32SysFreq * RCC_AHB_PRESC * RCC_APB1_PRESC;
	}
	else if (Copy_u8PeripheralBus==RCC_APB2_BUS_ID)
	{
		return  Local_u32SysFreq * RCC_AHB_PRESC * RCC_APB2_PRESC;
	}
	return 0; //ERROR//

}

/******************************************************************************/
/************************** HSI Calibraton section ****************************/
/******************************************************************************/
#ifdef RCC_CALIBRATION_EN
		s16  RCC_s16GetHSITrimVal(void)
		{
			return (s16)(GET_BYTE(MY_RCC->RCC_CR,3)&0x1F);
		}

    void RCC_voidTrimHSI(s16 Copy_calibrationOffset)
		{
			s16 absolCalibrationVal;
			Copy_calibrationOffset /= RCC_HSI_TRIM_STEP;
			absolCalibrationVal  =RCC_s16GetHSITrimVal(void) + Copy_calibrationOffset;
			if (absolCalibrationVal>=0 && absolCalibrationVal<RCC_MAX_CALIBRATION_VAL)
			{
				MAN_BYTE(MY_RCC->RCC_CR,3,((u32)absolCalibrationVal));//Accessing HSITRIM bits
			}elseif(absolCalibrationVal<0)
			{
				CLR_BYTE(MY_RCC->RCC_CR,3);
			}elseif(absolCalibrationVal>RCC_MAX_CALIBRATION_VAL)
			{
				MAN_BYTE(MY_RCC->RCC_CR,3,RCC_MAX_CALIBRATION_VAL);//Accessing HSITRIM bits
			}
		}
#endif /*CALIBRATION_EN end */

/******************************************************************************/
/*********************** Main clock output on MCO Pin *************************/
/******************************************************************************/
#ifdef RCC_MCO_ENABLE
		void RCC_voidEnMCO (u8 Copy_u8OutputTypeMCO)
		{
			MAN_NIBBLE(MY_RCC->RCC_CFGR,24,RCC_MCO_SELECT);
		}
		void RCC_voidDisMCO(void)
		{
			BIT_L(MY_RCC->RCC_CFGR,26);
		}
#endif /*RCC_MCO_ENABLE*/

/******************************************************************************/
/*********************Run-Time Clk Manipiulation Functions*********************/
/******************************************************************************/
#ifdef RCC_RUN_TIME_CLK_SELECT_ENABLE

       /* Define the wanted funcytions here*/

#endif /*RCC_RUN_TIME_CLK_SELECT_ENABLE*/
