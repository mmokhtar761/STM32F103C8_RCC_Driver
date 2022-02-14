/*************************************************************************/
/* Author        : Mohamed Mokhtar Abd-Elaziz                            */
/* File          : NVIC_INTERFACE_H                                      */
/*Describtion    : An educational NVIC driver File for STM32F103C MC     */
/* Date          :                                                       */
/* Version       : V01.1                                                 */
/* GitHub        :                                                       */
/*************************************************************************/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H


#define WWDG_IRQ_ID            ((u8)0x00)  /* Window WatchDog Interrupt */
#define PVD_IRQ_ID             ((u8)0x01)  /* PVD through EXTI Line detection Interrupt */
#define TAMPER_IRQ_ID          ((u8)0x02)  /* Tamper Interrupt */
#define RTC_IRQ_ID             ((u8)0x03)  /* RTC global Interrupt */
#define FLASH_IRQ_ID           ((u8)0x04)  /* FLASH global Interrupt */
#define RCC_IRQ_ID             ((u8)0x05)  /* RCC global Interrupt */
#define EXTI0_IRQ_ID           ((u8)0x06)  /* EXTI Line0 Interrupt */
#define EXTI1_IRQ_ID           ((u8)0x07)  /* EXTI Line1 Interrupt */
#define EXTI2_IRQ_ID           ((u8)0x08)  /* EXTI Line2 Interrupt */
#define EXTI3_IRQ_ID           ((u8)0x09)  /* EXTI Line3 Interrupt */
#define EXTI4_IRQ_ID           ((u8)0x0A)  /* EXTI Line4 Interrupt */
#define DMA1_CH1_IRQ_ID        ((u8)0x0B)  /* DMA1 Channel 1 global Interrupt */
#define DMA1_CH2_IRQ_ID        ((u8)0x0C)  /* DMA1 Channel 2 global Interrupt */
#define DMA1_CH3_IRQ_ID        ((u8)0x0D)  /* DMA1 Channel 3 global Interrupt */
#define DMA1_CH4_IRQ_ID        ((u8)0x0E)  /* DMA1 Channel 4 global Interrupt */
#define DMA1_CH5_IRQ_ID        ((u8)0x0F)  /* DMA1 Channel 5 global Interrupt */
#define DMA1_CH6_IRQ_ID        ((u8)0x10)  /* DMA1 Channel 6 global Interrupt */
#define DMA1_CH7_IRQ_ID        ((u8)0x11)  /* DMA1 Channel 7 global Interrupt */
#define ADC1_2_IRQ_ID          ((u8)0x12)  /* ADC1 et ADC2 global Interrupt */
#define USB_HP_CAN_TX_IRQ_ID   ((u8)0x13)  /* USB High Priority or CAN TX Interrupts */
#define USB_LP_CAN_RX0_IRQ_ID  ((u8)0x14)  /* USB Low Priority or CAN RX0 Interrupts */
#define CAN_RX1_IRQ_ID         ((u8)0x15)  /* CAN RX1 Interrupt */
#define CAN_SCE_IRQ_ID         ((u8)0x16)  /* CAN SCE Interrupt */
#define EXTI9_5_IRQ_ID         ((u8)0x17)  /* External Line[9:5] Interrupts */
#define TIM1_BRK_IRQ_ID        ((u8)0x18)  /* TIM1 Break Interrupt */
#define TIM1_UP_IRQ_ID         ((u8)0x19)  /* TIM1 Update Interrupt */
#define TIM1_TRG_COM_IRQ_ID    ((u8)0x1A)  /* TIM1 Trigger and Commutation Interrupt */
#define TIM1_CC_IRQ_ID         ((u8)0x1B)  /* TIM1 Capture Compare Interrupt */
#define TIM2_IRQ_ID            ((u8)0x1C)  /* TIM2 global Interrupt */
#define TIM3_IRQ_ID            ((u8)0x1D)  /* TIM3 global Interrupt */
#define TIM4_IRQ_ID            ((u8)0x1E)  /* TIM4 global Interrupt */
#define I2C1_EV_IRQ_ID         ((u8)0x1F)  /* I2C1 Event Interrupt */
#define I2C1_ER_IRQ_ID         ((u8)0x20)  /* I2C1 Error Interrupt */
#define I2C2_EV_IRQ_ID         ((u8)0x21)  /* I2C2 Event Interrupt */
#define I2C2_ER_IRQ_ID         ((u8)0x22)  /* I2C2 Error Interrupt */
#define SPI1_IRQ_ID            ((u8)0x23)  /* SPI1 global Interrupt */
#define SPI2_IRQ_ID            ((u8)0x24)  /* SPI2 global Interrupt */
#define USART1_IRQ_ID          ((u8)0x25)  /* USART1 global Interrupt */
#define USART2_IRQ_ID          ((u8)0x26)  /* USART2 global Interrupt */
#define USART3_IRQ_ID          ((u8)0x27)  /* USART3 global Interrupt */
#define EXTI15_10_IRQ_ID       ((u8)0x28)  /* External Line[15:10] Interrupts */
#define RTC_ALARM_IRQ_ID       ((u8)0x29)  /* RTC Alarm through EXTI Line Interrupt */
#define USB_WAKE_UP_IRQ_ID     ((u8)0x2A)  /* USB WakeUp from suspend through EXTI Line Interrupt */
#define TIM8_BRK_IRQ_ID        ((u8)0x2B)  /* TIM8 Break Interrupt */
#define TIM8_UP_IRQ_ID         ((u8)0x2C)  /* TIM8 Update Interrupt */
#define TIM8_TRG_COM_IRQ_ID    ((u8)0x2D)  /* TIM8 Trigger and Commutation Interrupt */
#define TIM8_CC_IRQ_ID         ((u8)0x2E)  /* TIM8 Capture Compare Interrupt */
#define ADC3_IRQ_ID            ((u8)0x2F)  /* ADC3 global Interrupt */
#define FSMC_IRQ_ID            ((u8)0x30)  /* FSMC global Interrupt */
#define SDIO_IRQ_ID            ((u8)0x31)  /* SDIO global Interrupt */
#define TIM5_IRQ_ID            ((u8)0x32)  /* TIM5 global Interrupt */
#define SPI3_IRQ_ID            ((u8)0x33)  /* SPI3 global Interrupt */
#define UART4_IRQ_ID           ((u8)0x34)  /* UART4 global Interrupt */
#define UART5_IRQ_ID           ((u8)0x35)  /* UART5 global Interrupt */
#define TIM6_IRQ_ID            ((u8)0x36)  /* TIM6 global Interrupt */
#define TIM7_IRQ_ID            ((u8)0x37)  /* TIM7 global Interrupt */
#define DMA2_CH1_IRQ_ID        ((u8)0x38)  /* DMA2 Channel 1 global Interrupt */
#define DMA2_CH2_IRQ_ID        ((u8)0x39)  /* DMA2 Channel 2 global Interrupt */
#define DMA2_CH3_IRQ_ID        ((u8)0x3A)  /* DMA2 Channel 3 global Interrupt */
#define DMA2_CH4_5_IRQ_ID      ((u8)0x3B)  /* DMA2 Channel 4 and DMA2 Channel 5 global Interrupt */


typedef struct
{
  u8 u8IRQid;
  u8 u8GroupPriority;
  u8 u8supPriority;
} ExPriphIRQ_type;


/*
  This function must be called before any setting for priority
*/
void NVIC_voidinitNVIC (void);
/*
   DIS : disables all external peripherals IRQs
   EN  : restors all last en/disable configurations to external peripherals IRQs
*/
void NVIC_voidEnDisExternalPeripheralIRQ(u8 Copy_u8ENorDIS);
/*
  > This function reseaves a pointer to a variable of type ExPriphIRQ_type contains
  the data about (required IRQ id, group priority, and sup-priority)

  > Sets the group priority and suppriority for this IRQ id
*/
void NVIC_voidConfigIRQpriority (ExPriphIRQ_type * Ptr_ExPriphIRQ);
/*
  Enable spacific IRQ
*/
void NVIC_voidEnExtIRQ  (u8 Copy_u8IRQ_ID);
/*
  Disable spacific IRQ
*/
void NVIC_voidDisExtIRQ (u8 Copy_u8IRQ_ID);

/*
  Sets the pending flag
*/
void NVIC_voidSetPending (u8 Copy_u8IRQ_ID);
/*
  Clears the pending flag
*/
void NVIC_voidClrPending (u8 Copy_u8IRQ_ID);
/*
  Returns TRUE   if Copy_u8IRQ_ID is pending
          FALSE  if Copy_u8IRQ_ID isn't pending
*/
u32  NVIC_u32GetPending (u8 Copy_u8IRQ_ID);
/*
  Returns TRUE   if Copy_u8IRQ_ID is Active
          FALSE  if Copy_u8IRQ_ID isn't Active
*/
u32  NVIC_u32GetActive (u8 Copy_u8IRQ_ID);

#endif  NVIC_INTERFACE_H
