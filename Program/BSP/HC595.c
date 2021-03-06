#include "includes.h"


/*--ZQP的74HC595的初始化*/
void HC595_Init(void)
{
	GPIO_InitTypeDef GPIO_InitS;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitS.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitS.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitS.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HC595_PORT, &GPIO_InitS);

	GPIO_SetBits(HC595_PORT, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
}


void HC595SendData(u16 SendVal)
{
	uint8_t i;
	S_CLK_Pin13_SHCP_OUT = 0;
	S_CLK_Pin13_SHCP_OUT = 0;

	for (i = 0; i < 16; i++)
	{
		/*--step1、串行输入引脚，所谓串行就是使数据在一根信号线上按顺序一位一位地传输*/
		if (((SendVal << i) & 0x8000) != 0 )
			MOSIO_Pin14_DS_OUT = 1;
		else
			MOSIO_Pin14_DS_OUT = 0;

		/*--step2、SHCP发生一次上升沿的时候，74HC595才会从DS引脚上取得当前的数据*/
		S_CLK_Pin13_SHCP_OUT = 0;
		delay_us(10);
		S_CLK_Pin13_SHCP_OUT = 1;
	}

	/*--step3、当移位寄存器的8位数据全部传输完毕后，制造一次锁存器时钟引脚的上升沿（先拉低电平再拉高电平）*/
	R_CLK_Pin12_STCP_OUT = 0;
	delay_us(10);
	R_CLK_Pin12_STCP_OUT = 1;
	delay_us(10);
	S_CLK_Pin13_SHCP_OUT = 0;

	R_CLK_Pin12_STCP_OUT = 0;
	MOSIO_Pin14_DS_OUT = 0;
}
























