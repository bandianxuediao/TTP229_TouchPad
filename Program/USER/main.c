#include "includes.h"
int main(void)
{
	//  u8 key;
	//  u16 i = 0;
	u8 key_value = 0;

	//  u16 Valll = 1;
	delay_init();            //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);      //串口初始化为115200
	HC595_Init();
	PAD_IIC_Init();
	delay_ms(500);
	delay_ms(500);
	/*--Z QP的74HC595*/
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
					printf ("按键%02d按下   num=%04x \r\n", key_value, receive);
					delay_ms(500);
					HC595SendData(0 << (key_value - 1));

				}
			}
		}
	}
}
