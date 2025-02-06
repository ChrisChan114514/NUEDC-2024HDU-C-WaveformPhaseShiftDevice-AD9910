/**********************************************************
                       康威电子
										 
功能：stm32f103rct6控制，25MHz时钟， AD9833正弦波点频输出，范围0-10M(可编辑0-100M)，
			方波：0-500K，三角波：0-1M，扫频默认正弦波 。
			显示：12864cog
接口：控制接口请参照AD9833.h  按键接口请参照key.h
时间：2015/11/10
版本：1.0
作者：康威电子
其他：程序借鉴正点原子，添加自己的驱动，未经作者许可，不得用于其它任何用途

更多电子需求，请到淘宝店，康威电子竭诚为您服务 ^_^
https://shop110336474.taobao.com/?spm=a230r.7195193.1997079397.2.Ic3MRJ

**********************************************************/
#include "AD9833.h"		// AD9833 definitions.
#include "delay.h"		// AD9833 definitions.

#define FCLK 25000000	//设置晶振频率
#define RealFreDat    268435456.0/FCLK//总的公式为 Fout=（Fclk/2的28次方）*28位寄存器的值

/***************************************************************************//**
 * @brief Initializes the SPI communication peripheral and resets the part.
 *
 * @return 1.
*******************************************************************************/
unsigned char AD9833_Init(void)
{
    AD9833_SPI_Init(0, 1000000, 1, 1);
    AD9833_SetRegisterValue(AD9833_REG_CMD | AD9833_RESET);
	
    return (1);
}

/***************************************************************************//**
 * @brief Sets the Reset bit of the AD9833.
 *
 * @return None.
*******************************************************************************/
void AD9833_Reset(void)
{
    AD9833_SetRegisterValue(AD9833_REG_CMD | AD9833_RESET);
	delay_ms(10);
}

/***************************************************************************//**
 * @brief Clears the Reset bit of the AD9833.
 *
 * @return None.
*******************************************************************************/
void AD9833_ClearReset(void)
{
	AD9833_SetRegisterValue(AD9833_REG_CMD);
}
/***************************************************************************//**
 * @brief Writes the value to a register.
 *
 * @param -  regValue - The value to write to the register.
 *
 * @return  None.    
*******************************************************************************/
void AD9833_SetRegisterValue(unsigned short regValue)
{
	unsigned char data[5] = {0x03, 0x00, 0x00};	
	
	data[1] = (unsigned char)((regValue & 0xFF00) >> 8);
	data[2] = (unsigned char)((regValue & 0x00FF) >> 0);
	ADI_CS_LOW;	    
	AD9833_SPI_Write(data,2);
	ADI_CS_HIGH;
}
void AD9833_SetFrequencyQuick(float fout,unsigned short type)
{

	//AD9833_Setup(AD9833_FSEL0, AD9833_PSEL0, type);
	AD9833_SetFrequency(AD9833_REG_FREQ0, fout,type);// 400 kHz

}

/***************************************************************************//**
 * @brief Writes to the frequency registers.
 *
 * @param -  reg - Frequence register to be written to.
 * @param -  val - The value to be written.
 *
 * @return  None.    
*******************************************************************************/
void AD9833_SetFrequency(unsigned short reg, float fout,unsigned short type)
{
	unsigned short freqHi = reg;
	unsigned short freqLo = reg;
	unsigned long val=RealFreDat*fout;
	freqHi |= (val & 0xFFFC000) >> 14 ;
	freqLo |= (val & 0x3FFF);
	AD9833_SetRegisterValue(AD9833_B28|type);
	AD9833_SetRegisterValue(freqLo);
	AD9833_SetRegisterValue(freqHi);
}
/***************************************************************************//**
 * @brief Writes to the phase registers.
 *
 * @param -  reg - Phase register to be written to.
 * @param -  val - The value to be written.
 *
 * @return  None.    
*******************************************************************************/
void AD9833_SetPhase(unsigned short reg, unsigned short val)
{
	unsigned short phase = reg;
	phase |= val;
	AD9833_SetRegisterValue(phase);
}
/***************************************************************************//**
 * @brief Selects the Frequency,Phase and Waveform type.
 *
 * @param -  freq  - Frequency register used.
 * @param -  phase - Phase register used.
 * @param -  type  - Type of waveform to be output.
 *
 * @return  None.    AD9833_Setup(1000,0,AD9833_OUT_SINUS);
*******************************************************************************/
void AD9833_Setup(unsigned short freq,
				  unsigned short phase,
			 	  unsigned short type)
{
	unsigned short val = 0;
	
	val = freq | phase | type;
	AD9833_SetRegisterValue(val);
}
/***************************************************************************//**
 * @brief Sets the type of waveform to be output.
 *
 * @param -  type - type of waveform to be output.
 *
 * @return  None.    
*******************************************************************************/
void AD9833_SetWave(unsigned short type)
{
	AD9833_SetRegisterValue(type);
}