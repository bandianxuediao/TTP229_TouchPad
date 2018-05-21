#include "includes.h"
int main(void)
{
	//  u8 key;
	//  u16 i = 0;
	u8 key_value = 0;

	//  u16 Valll = 1;
	delay_init();            //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);      //���ڳ�ʼ��Ϊ115200
	HC595_Init();
	PAD_IIC_Init();
	delay_ms(500);
	delay_ms(500);
	/*--Z QP��74HC595*/
	HC595SendData(0);

	while(1)
	{
		key_value = scan_key();
		delay_ms(10);

		if((key_value == scan_key()) && (key_value != 0))
		{
			delay_ms(10);

			if((key_value == scan_key()) && (key_value != 0))
			{
				delay_ms(10);

				if((key_value == scan_key()) && (key_value != 0))
				{


					HC595SendData(1 << (key_value - 1));
					printf ("����%02d����   num=%04x \r\n", key_value, receive);
					delay_ms(500);
					HC595SendData(0 << (key_value - 1));

				}
			}
		}
	}
}
