/**********************************************************
                       ��������
										 
���ܣ�stm32f103rct6���ƣ�25MHzʱ�ӣ� AD9833���Ҳ���Ƶ�������Χ0-10M(�ɱ༭0-100M)��
			������0-500K�����ǲ���0-1M��ɨƵĬ�����Ҳ� ��
			��ʾ��12864cog
�ӿڣ����ƽӿ������AD9833.h  �����ӿ������key.h
ʱ�䣺2015/11/10
�汾��1.0
���ߣ���������
����������������ԭ�ӣ�����Լ���������δ��������ɣ��������������κ���;

������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
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

char str[30];	//��ʾ����
extern u8 _return;
int main(void)
{
	u16 i=0;

	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//�����жϷ���
	delay_init(72);	//��ʼ����ʱ����
	LED_Init();	//��ʼ��LED�ӿ�
	key_init();
	initial_lcd();
	LCD_Clear();
	delay_ms(300);
	LCD_Refresh_Gram();
	
	//��ʱ��
	Timerx_Init(99,71);
	//welcome_KW();
	//��־���������ɫ
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

