/*************************************************************************************
 Title	:   Analog Devices AD9833 DDS Wave Generator Library for STM32 Using HAL Libraries
 Author:    Bardia Alikhan Afshar <bardia.a.afshar@gmail.com>  
 Software:  IAR Embedded Workbench for ARM
 Hardware:  Any STM32 device
*************************************************************************************/
#ifndef _AD_9833_H
#define _AD_9833_H
#include <math.h>
#include "stm32f4xx_hal.h"
 
// ------------------------- Defines -------------------------
#define FMCLK 25000000        // Master Clock On AD9833
#define ASM_NOP() HAL_Delay(1)  // Assembly NOPE (Little Delay)
 
typedef struct
{
    GPIO_TypeDef * PORT;
    uint16_t DATA;
    uint16_t SCK;
    uint16_t SS;
}AD9833_Typedef;
 
 
enum WaveType{SIN, SQR, TRI}; // Wave Selection Enum
 
// ------------------ Functions  ---------------------
void AD9833_SetWave(uint16_t Wave,AD9833_Typedef AD9833);                           // Sets Output Wave Type
void AD9833_SetWaveData(float Frequency,float Phase,AD9833_Typedef AD9833);         // Sets Wave Frequency & Phase
#endif