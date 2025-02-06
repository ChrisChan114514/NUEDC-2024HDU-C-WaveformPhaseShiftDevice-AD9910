#include "ad9833.h"

#include "spi.h"


//#define CS_9833_0() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET) //片选拉高拉低函数
//#define CS_9833_1() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET)
////AD9833 驱动
///******************************************************************************
//*  函数名：AD9833_Init
//*  功能说明：初始化AD9833相关GPIO
//*  形  参：无
//*  返回值：无
//*******************************************************************************
//*/
//void AD9833_GPIOinit(void)
//{
//	CS_9833_1();
//}
///******************************************************************************
//*  函数名：AD9833_Write
//*  功能说明：向AD9833发送一个16bit数
//*  形  参：TxData 要发送的数
//*  返回值：无
//*******************************************************************************
//*/
//void AD9833_Write(unsigned short TxData)  //写入寄存器
//{
//	unsigned char data[2];
//	data[0]=(unsigned char)((TxData>>8)&0xff);
//	data[1]=(unsigned char)(TxData&0xff);
//	CS_9833_0();
//	HAL_SPI_Transmit(&hspi2,data,2,0x02);
//	CS_9833_1();
//	
//}
///******************************************************************************
//*  函数名：AD9833_CtrlSet
//*  功能说明：设置AD9833输出形式
//*  形  参：Reset:0为有输出，1为无输出
//           SleepMode:3关闭内部时钟和DAC,0不关闭
//           optionbit|modebit:
//                     00正弦波、01三角波、10方波、11保留
//*  返回值：无
//*******************************************************************************
//*/
//void AD9833_CtrlSet(unsigned char Reset,unsigned char SleepMode,unsigned char optionbit,unsigned char modebit)
//{
//	unsigned short regtmep=0;
//	regtmep=regtmep|(((unsigned short)Reset&0x01)<<8); //寄存器位数处理
//	regtmep=regtmep|((SleepMode&0x03)<<6);
//	regtmep=regtmep|((optionbit&0x01)<<5);
//	regtmep=regtmep|((modebit&0x01)<<1);
//	
//	AD9833_Write(regtmep);
//}
///******************************************************************************
//*  函数名：AD9833_FreqSet
//*  功能说明：设置AD9833输出频率
//*  形  参：Freq: 频率值（0.1HZ~12.5MHZ）,为晶振值的一半
//*  返回值：无
//*******************************************************************************
//*/
//void AD9833_Freq(double Freq)
//{
//	int frequence_LSB,frequence_MSB;
//	double frequence_mid,frequence_DATA;
//	long int frequence_hex;
//	//频率换算
//	frequence_mid=268435456/25;
//	frequence_DATA=Freq;
//	frequence_DATA=frequence_DATA/1000000;
//	frequence_DATA=frequence_DATA*frequence_mid;
//	frequence_hex=frequence_DATA;
//	frequence_LSB=frequence_hex; //频率低位
//	frequence_LSB=frequence_DATA; //32bit
//	frequence_LSB=frequence_LSB&0x3fff; //14bit
//	frequence_MSB=frequence_LSB>>14;    //频率高位
//	frequence_MSB=frequence_MSB&0x3fff; //14bit
//	
//	//使用频率寄存器
//	frequence_LSB=frequence_LSB|0x4000;
//	frequence_MSB=frequence_MSB|0x4000;
//	
//	AD9833_Write(0x2100);
//	AD9833_Write(frequence_LSB);
//	AD9833_Write(frequence_MSB);
//}  

void AD9833_GPIOinit(void)

{

	CS_9833_1(); //首先拉高片选，不使能，防止输入错误数据

}



/*

*******************************************************

向AD9833发送一个16bit的数据

*******************************************************

*/

void AD9833_Write(unsigned short TxData) //TxData是2字节

{

	unsigned char data[2] ; //一个char一个字节，数组为2个字节

	data[0] = (unsigned char)((TxData>>8) &0xff); //data[0]存储高位

	data[1] = (unsigned char)(TxData&0xff); //data[1]存储低位

	CS_9833_0(); //拉低片选，准备写入

	HAL_SPI_Transmit (&hspi2 , data, 2, 0x02) ; //用HAL库的SPI发送函数发送数据

	CS_9833_1(); //发送完毕，拉高片选

}

  

/*

*******************************************************

Reset: 0为有输出，1为没输出，此位只控制有无输出，不复位寄存器

SleeppMode: 3为关闭内部DAC和时钟，0为不关闭

optionbit|modebit: 00正弦01三角10方波11保留

*******************************************************

*/

void AD9833_CtrlSet(unsigned char Reset,unsigned char SleeppMode,unsigned char optionbit,unsigned char modebit)

{

	unsigned short regtemp = 0; //对输出模式的一些选择

	regtemp = regtemp|(((unsigned short)Reset&0x01)<<8); //以下就是把每个位对应到相应的寄存器上，不过好像少了个DIV2,DIV2默认为0了？

	regtemp = regtemp|((SleeppMode&0x03)<<6);

	regtemp = regtemp|((optionbit&0x01)<<5);

	regtemp = regtemp|((modebit&0x01)<<1);

	AD9833_Write(regtemp); //写入数据，不过不需要先声明将要写入吗？

}

  

/*

*******************************************************

设置频率，设置完后暂不输出，用CtrlSet函数设置输出

频率值：0.1Hz-12.5MHz（最大值为25M晶振时钟的一半）

单位：Hz;例如，输出1M，则输入1000000

*******************************************************

*/

void AD9833_FreqSet(double Freq) //Freq是用户输入的以Hz为单位的频率

{

	int frequence_LSB,frequence_MSB; //LSB和MSB分别对应频率寄存器里的LSB和MSB

	double frequence_mid,frequence_DATA; //mid是一个中间值，用于将输入频率转换为AD9833可以接受的格式；DATA为输入进去的频率的十进制

	long int frequence_hex; //hex为输入进去的频率的16进制

	  

	frequence_mid = 268435456/25; //f_{out}=dds输出频率；F_{cw}=f_{DATA}；f_{ref}=25M；2^28=268435456；1000000=1M

	frequence_DATA = Freq; //公式：f_{out}=(F_{cw})*(f_{ref})/(2^28)=(f_{DATA})*25M/(2^28)

	frequence_DATA = frequence_DATA/1000000; //这里的f_{DATA}(化作以M为单位)=(Freq/1000000)*[(2^28)/(25)]，;f_{DATA}作为f_{cw}输入进公式，刚好得到f_{out}=Freq，且以Hz为单位

	frequence_DATA = frequence_DATA*frequence_mid;

	frequence_hex = frequence_DATA;

	frequence_LSB = frequence_hex;

	frequence_LSB = frequence_LSB&0x3fff; //以下就是一些与或操作，用来输入寄存器

	frequence_MSB = frequence_hex>>14;

	frequence_MSB = frequence_MSB&0x3fff;

	  

	frequence_LSB = frequence_LSB|0x4000;

	frequence_MSB = frequence_MSB|0x4000; //4000==0100 0000 0000 0000,把前两位变成01，代表freq0寄存器

	  

	AD9833_Write(0x2100); //2100==0010 0001 0000 0000;bit8为1->不reset;0010->连续写LSB、MSB标志

	AD9833_Write(frequence_LSB);

	AD9833_Write(frequence_MSB);

  

}
