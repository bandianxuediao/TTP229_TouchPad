/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：主要是完成对eeprom的写操作和读操作
 * 库版本  ：V3.50
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2017-04-20
 * 调试方式：J-Link-OB
**********************************************************************************/

//头文件
#include "includes.h"



void I2C_Test(void);


/**
  * @file   main
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	u8 i = 0;
	u16 key_value = 0;
	SYSTICK_Init();
	USART1_Config();
	LED_GPIO_Config();
	PAD_IIC_Init();
	HC595_Init();
	//I2C_Configuration();
	printf("\r\n 1241234234123 \r\n");
	HC595SendData(0);

	//I2C_Test();
	while (1)
	{
		key_value = scan_key();
		delay_ms(100);

		if((key_value == scan_key()) && (key_value != 0))
		{
			delay_ms(100);

			if((key_value == scan_key()) && (key_value != 0))
			{
				if(key_value)
				{
					printf("\r\n key=%04x\r\n", receive);
					//          LEDXToggle(LED2);
					//          LEDXToggle(LED3);

					HC595SendData(1 << (key_value - 1));
					delay_ms(500);
					HC595SendData(0);
				}
			}
		}

		key_value = 0;

	}

}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





