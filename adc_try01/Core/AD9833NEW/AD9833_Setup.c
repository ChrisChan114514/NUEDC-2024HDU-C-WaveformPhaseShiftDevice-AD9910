#include "AD9833_Setup.h"
 
void AD9833_Init(AD9833_Typedef AD9833,uint8_t type,float Freq,float Phase)
{
    // AD9833 Pin configuration
    AD9833.PORT = GPIOC;
    AD9833.DATA = GPIO_PIN_0;
    AD9833.SCK = GPIO_PIN_1;
    AD9833.SS = GPIO_PIN_2;
 
    // Set all AD9833 pin to High
    HAL_GPIO_WritePin(AD9833.PORT, AD9833.DATA, GPIO_PIN_SET);
    HAL_GPIO_WritePin(AD9833.PORT, AD9833.SCK, GPIO_PIN_SET);
    HAL_GPIO_WritePin(AD9833.PORT, AD9833.SS, GPIO_PIN_SET);
 
    // Set default frequecy which is employeed by AD9833
    AD9833_SetWave(type, AD9833);          // Type Of Wave
	AD9833_SetWaveData(Freq, Phase, AD9833); // Frequency & Phase Set
 
    return;
}