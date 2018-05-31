
//Í·ÎÄ¼þ
#include "includes.h"

int main(void)
{
	u16 key_value = 0;
	SYSTICK_Init();
	USART1_Config();
	PAD_IIC_Init();
	HC595_Init();
	printf("\r\n test uart \r\n");
	HC595SendData(0);

	while (1)
	{
		key_value = scan_key();
		delay_ms(100);

		if((key_value == scan_key()) && (key_value != 0))
		{
			delay_ms(100);

			if((key_value == scan_key()) && (key_value != 0))
			{
				printf("\r\n key=%04x\r\n", receive);
				HC595SendData(1 << (key_value - 1));
				delay_ms(500);
				HC595SendData(0);
			}
		}

		key_value = 0;

	}

}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





