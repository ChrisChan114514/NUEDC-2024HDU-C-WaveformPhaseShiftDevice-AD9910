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
https://kvdz.taobao.com/

**********************************************************/

#include "stm32_config.h"
#include "stdio.h"
#include "led.h"
#include "lcd.h"
#include "AD9833.h" 
#include "key.h"
#include "timer.h"
#include "task_manage.h".

char str[30];	//显示缓存
extern u8 _return;
int main(void)
{
	u16 i=0;

	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//设置中断分组
	delay_init(72);	//初始化延时函数
	LED_Init();	//初始化LED接口
	key_init();
	initial_lcd();
	LCD_Clear();
	delay_ms(300);
	LCD_Refresh_Gram();
	
	//定时器
	Timerx_Init(99,71);
	//welcome_KW();
	//标志排针插线颜色
	LCD_Clear();
	
	AD9833_Init();
	AD9833_SetFrequencyQuick(1000,AD9833_OUT_SINUS);

	while(1)
	{
		KeyRead();
		Set_PointFre(Keycode, 0);
		if(_return){_return=0;LCD_Refresh_Gram();}
		KEY_EXIT();
	}	
}

